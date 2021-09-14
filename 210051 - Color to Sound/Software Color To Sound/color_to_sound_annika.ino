#include <Wire.h>    // include support for the I2C functionality
const int TCS34725=0x29;                      // I2C address
int buzz = 8;                                 // Piezo Buzzer
int led = 2;                                  // LED on breakout board
void I2Cwrite(int addr, int reg, int val) {   // I2C write
  Wire.beginTransmission(addr);               // address
  Wire.write(0xFF & (0x80 | reg));            // register with command bit set
  Wire.write(val);                            // write value
  Wire.endTransmission(true);
}
int I2Cread(int addr, int reg) {              //I2C read
  Wire.beginTransmission(addr);
  Wire.write(0xFF & (0x80 | reg));            // start register address
  Wire.endTransmission(false);
  Wire.requestFrom(addr,1);                   // request one byte
  return Wire.read();                         // read and return
}
void color_begin() {                          // we need to turn the device ON
  delay(10);                                  // wait
  I2Cwrite(TCS34725,0x00,0x01);               // first PON
  delay(3);                                   // see note 2 on page 20
  I2Cwrite(TCS34725,0x00,0x03);               // then AEN
}
void setup() {
  Serial.begin(9600);                   // baud rate
  while (!Serial) {;}                   // wait for serial to come up
  Wire.begin();                         // initialize the I2C functionality
  pinMode(led,OUTPUT);                  // control the LED on breakout board
  digitalWrite(led,LOW);                // initially it is off
  color_begin();
}
void loop() {
  if (Serial.available()) {  // wait until someone asks
    int b1,b2,b3,b4,b5,b6,b7,b8,clea,red,green,blue,d;
    char line[30];
    b1=I2Cread(TCS34725,0x14);         // raw data, clear
    b2=I2Cread(TCS34725,0x15);
    clea=b2*256+b1;                    // combine bytes to 16-bit word
    b3=I2Cread(TCS34725,0x16);         // raw data, red
    b4=I2Cread(TCS34725,0x17);
    red=b4*256+b3;
    b5=I2Cread(TCS34725,0x18);         // raw data, green
    b6=I2Cread(TCS34725,0x19);
    green=b6*256+b5;
    b7=I2Cread(TCS34725,0x1A);         // raw data, blue
    b8=I2Cread(TCS34725,0x1B);
    blue=b8*256+b7;
    if (clea < 1000) {                 // convert brightness to duration
      d=500;                           // 0.5 seconds
    } else if (clea > 1000) {
      d=1500;                          // 1.5 seconds
    }
    Serial.readStringUntil('\n').toCharArray(line,30);
    if (strstr(line,"color?")==line) {
      Serial.print(clea); Serial.print(" "); 
      Serial.print(red); Serial.print(" "); 
      Serial.print(green); Serial.print(" "); 
      Serial.println(blue);
    } else if (strstr(line,"tone_red")==line) {
      tone(buzz, 262, d);
    } else if (strstr(line,"tone_green")==line) {
      tone(buzz, 587, d);
    } else if (strstr(line,"tone_blue")==line) {
      tone(buzz, 880, d);
    } else if (strstr(line,"tone_yellow")==line) {
      tone(buzz, 392, d);
    } else if (strstr(line,"no_color")==line) {
      tone(buzz, 130, d);
    } else if (strstr(line,"led_on")==line) {
      digitalWrite(led,HIGH);
    } else if (strstr(line,"led_off")==line) {
      digitalWrite(led,LOW);
    } else {
      Serial.println("unknown command");
    }
    delay(d); // wait for the tone to end
  }
}
