
/* From the IDF documentation at https://github.com/espressif/esp-idf/components/esp_hw_support/include/esp_chip_info.h 
 *  
 *typedef enum {
    CHIP_ESP32  = 1, //!< ESP32
    CHIP_ESP32S2 = 2, //!< ESP32-S2
    CHIP_ESP32S3 = 4, //!< ESP32-S3
    CHIP_ESP32C3 = 5, //!< ESP32-C3
    CHIP_ESP32H2 = 6, //!< ESP32-H2
} esp_chip_model_t;

// Chip feature flags, used in esp_chip_info_t 
#define CHIP_FEATURE_EMB_FLASH      BIT(0)      //!< Chip has embedded flash memory
#define CHIP_FEATURE_WIFI_BGN       BIT(1)      //!< Chip has 2.4GHz WiFi
#define CHIP_FEATURE_BLE            BIT(4)      //!< Chip has Bluetooth LE
#define CHIP_FEATURE_BT             BIT(5)      //!< Chip has Bluetooth Classic
#define CHIP_FEATURE_IEEE802154     BIT(6)      //!< Chip has IEEE 802.15.4

typedef struct {
    esp_chip_model_t model;  //!< chip model, one of esp_chip_model_t
    uint32_t features;       //!< bit mask of CHIP_FEATURE_x feature flags
    uint8_t cores;           //!< number of CPU cores
    uint8_t revision;        //!< chip revision number
} esp_chip_info_t;

*/

void setup() {
  TaskHandle_t xHandle = NULL;
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  Serial.println("esp_chip_info()");
  Serial.println("-------------------------------------------------------------");
  esp_chip_info_t info;
  esp_chip_info(&info);
  Serial.print("Chip Model: ");
  switch(info.model){
  
    case 1:{
      Serial.println("ESP32");
    }break;

    case 2:{
      Serial.println("ESP32-S2");
    }break;

    case 4:{
      Serial.println("ESP32-S3");
    }break;

    case 5:{
      Serial.println("ESP32-C3");
    }break;

    case 6:{
      Serial.println("ESP32-H2");
    } break;

    default:{
      Serial.print("Unknown Chipmodel");
      Serial.println(info.model);
    }
    
  }
   Serial.print("Featues :");
   if(info.features&CHIP_FEATURE_EMB_FLASH){
    Serial.print(" Embedded Flash ");
   }
   if(info.features&CHIP_FEATURE_WIFI_BGN){
    Serial.print(" WiFi(BGN) ");
   }
   if(info.features&CHIP_FEATURE_BLE){
    Serial.print(" BLE ");
   }
 
  if(info.features&CHIP_FEATURE_BT){
    Serial.print(" BT CLassic ");
  }

  if(info.features&CHIP_FEATURE_IEEE802154){
    Serial.print(" IEEE802.155.4 ");
  }
  Serial.println("");
   Serial.print("Cores: ");
  Serial.println(info.cores);
  Serial.print("Chip Revision: ");
  Serial.println(info.revision);
  Serial.println("-------------------------------------------------------------");
  Serial.println();

}
