// https://kelasrobot.com/cara-mudah-mengirim-pesan-dari-nodemcu-ke-telegram-telegrambot-part1/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#define BUTTON D1


char ssid[] = "ndasmu_cok"; 
char password[] = "Akusayangkamu12345";
#define BOTtoken "626224631:AAFYBGTNy7MBirSTEdSLqOWQh39FBKxYCyE"
String chatid = "-340388579";
int switchState, buffer_ = 1;

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  Serial.begin(115200);
  WifiStatus();
  pinMode(BUTTON,INPUT_PULLUP);

  delay(3000);
  bot.sendMessage(chatid, "== Bot Terkoneksi ==\n> ");
  Serial.println("\n\nSudah Siap Di Gunakan\n");
}

void loop() {
  switchState = digitalRead(BUTTON);

  if (switchState == 1){
    Serial.print("Pintu TERBUKA .... Nilai Sensor => ");
    Serial.println(switchState);

    if(buffer_ == 0){
      Serial.print("\n\t\t VALUE BERUBAH ");
      String data =  "[+] Pintu TERBUKA \n>  ";
      bot.sendMessage(chatid,data);
      Serial.println("\t\t Notif Telegram Terkirim\n ");
    }

    buffer_ = 1;
    delay(1000);
    
  }else if(switchState == 0){
   Serial.print("Pintu tertutup .... Nilai Sensor => ");
    Serial.println(switchState);

    if(buffer_ == 1){
      Serial.print("\n\t\t VALUE BERUBAH ");
      String data =  "[-] Pintu TERTUTUP \n>  ";
      bot.sendMessage(chatid,data);
      Serial.println("\t\t Notif Telegram Terkirim\n ");
    }

    buffer_ = 0;
    delay(1000);
    
  }
}

void WifiStatus() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
