#include <SPI.h>
#include <MFRC522.h>

#include "Keyboard.h"
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

//int RXLED = 17;
//int TXLED = 30;
void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication
  
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  
  Keyboard.begin();

  pinMode(17, OUTPUT);  // RXLED
  pinMode(9, OUTPUT);  // RXLED
  digitalWrite(9,LOW);
  pinMode(30, OUTPUT);  // TXLED

  lampu(200,10,30);

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  
  lampu(200,3,17);
  Keyboard.press(KEY_TAB);
  Keyboard.releaseAll();
  Keyboard.println(content.substring(1));
  
  delay(1000);
} 

void lampu(int delay_, int jumlah, int pin){
    for(int i = 1 ; i <= jumlah ; i++){
          digitalWrite(pin, HIGH);
          delay(delay_);
          digitalWrite(pin, LOW);
          delay(delay_);
    }
}
