#include <Wire.h>    // include support for the I2C functionality
const int TCS34725=0x29;                      // I2C address
int buzz = 8;                                 // Piezo Buzzer
int led = 2;                                  // LED on breakout board
int button = 3; 
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
  Wire.begin();                         // initialize the I2C functionality
  pinMode(led,OUTPUT);                  // control the LED on breakout board
  digitalWrite(led,LOW);                // initially it is off
  pinMode(button,INPUT_PULLUP);         // button pin
  color_begin();
}
void loop() {
  if (digitalRead(button)==LOW) {  // wait until button is pressed
    int b1,b2,d;
    float clea,red,green,blue;
    digitalWrite(led, HIGH);
    delay(50);
    b1=I2Cread(TCS34725,0x14);         // raw data, clear
    b2=I2Cread(TCS34725,0x15);
    clea=b2*256+b1;                    // combine bytes to 16-bit word
    b1=I2Cread(TCS34725,0x16);         // raw data, red
    b2=I2Cread(TCS34725,0x17);
    red=b2*256+b1;
    b1=I2Cread(TCS34725,0x18);         // raw data, green
    b2=I2Cread(TCS34725,0x19);
    green=b2*256+b1;
    b1=I2Cread(TCS34725,0x1A);         // raw data, blue
    b2=I2Cread(TCS34725,0x1B);
    blue=b2*256+b1;
    if (clea < 1000) {                 // convert brightness to duration
      d=500;                           // 0.5 seconds
    } else if (clea > 1000) {
      d=1500;                          // 1.5 seconds
    }
    digitalWrite(led, LOW);
    if (red/clea > 0.6) {   
      tone(buzz, 262, d);
    } else if (green/clea > 0.3) {
      tone(buzz, 587, d);
    } else if (blue/clea > 0.24) {
      tone(buzz, 880, d);
    } else {
      tone(buzz, 130, d);
    } 
    delay(d); // wait for the tone to end
  }
}
