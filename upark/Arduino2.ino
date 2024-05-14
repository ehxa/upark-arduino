#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN_1 10
#define RST_PIN_1 9
#define SS_PIN_2 8
#define RST_PIN_2 7

MFRC522 mfrc522_1(SS_PIN_1, RST_PIN_1); 
MFRC522 mfrc522_2(SS_PIN_2, RST_PIN_2); 

String getUIDString(MFRC522 &mfrc522) {
  String uidString = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      uidString += "0"; 
    }
    uidString += String(mfrc522.uid.uidByte[i], HEX);
  }
  return uidString;
}

void setup() {
  Serial.begin(9600);
  SPI.begin(); 
  mfrc522_1.PCD_Init();
  mfrc522_2.PCD_Init();
}

void loop() {
  if (mfrc522_1.PICC_IsNewCardPresent()) {
    if (mfrc522_1.PICC_ReadCardSerial()) {
      String uidString1 = getUIDString(mfrc522_1);
      if (uidString1.equals("a59d713a")){
        Serial.println("E-W01");
      }
      if (uidString1.equals("34dea0bb")){
        Serial.println("S-W01");
      }
      if (uidString1.equals("73a4ad85")){
        Serial.println("I-N01");
      }
      mfrc522_1.PICC_HaltA(); 
    }
  }

  if (mfrc522_2.PICC_IsNewCardPresent()) {
    if (mfrc522_2.PICC_ReadCardSerial()) {
      String uidString2 = getUIDString(mfrc522_2);
      if (uidString2.equals("a59d713a")){
        Serial.println("I-C01");
      }
      if (uidString2.equals("34dea0bb")){
        Serial.println("I-E01");
      }
      if (uidString2.equals("73a4ad85")){
        Serial.println("I-S01");
      }
      mfrc522_2.PICC_HaltA(); 
    }
  }
}
