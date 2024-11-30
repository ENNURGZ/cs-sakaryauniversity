#define BLYNK_TEMPLATE_ID "TMPL6TQgqtYsf"
#define BLYNK_TEMPLATE_NAME "dv"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <BlynkSimpleEsp8266.h>
#include <Blynk.h>
char auth[] = "Cb18GVnoUnOJ-62taf9bHNz6pTaq8ere"; // Blynk key
#define BLYNK_AUTH_TOKEN "Cb18GVnoUnOJ-62taf9bHNz6pTaq8ere"

const char* WLAN_SSID = "Ennur"; // Kablosuz Ağ Adı
const char* WLAN_PASSWORD = "Ennur1515"; // Kablosuz Ağ Şifresi

const char* thingSpeakHost = "api.thingspeak.com";
const char* writeAPIKey = "7QBBVVWW3PTF88U4"; // ThingSpeak api key
unsigned long channelID = 2388365;
const char* writeAPIKey2 = "7OPPNZGA0PRF711B"; // ThingSpeak api key
unsigned long channelID2 = 2388400;
unsigned int field_no = 1;

WiFiClient client;

void setup() {
  pinMode(D0, INPUT);
  Serial.begin(115200);

  WiFi_Setup();
  ThingSpeak.begin(client);
  Blynk.begin(auth, WLAN_SSID, WLAN_PASSWORD);
}

void WiFi_Setup() {
  delay(10);
  Serial.println(); Serial.print(WLAN_SSID);
  Serial.print(" Kablosuz Agina Baglaniyor");
  WiFi.begin(WLAN_SSID, WLAN_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(); Serial.print(WLAN_SSID);
  Serial.println("Kablosuz Agina Baglandi");
  Serial.println("IP adresi: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Blynk.run();
  WidgetLED led1(V0);
  WidgetLED led2(V1);

  if (digitalRead(D0) == false) {
    analogWrite (D1, 500);
    led1.on();
  } else {
    analogWrite (D1, 0);
    led1.off();
  }

  delay(1000);
  if (analogRead(A0) >= 100) {
    analogWrite (D2, 500);
    led2.on();
  } else {
    analogWrite (D2, 0);
    led2.off();
  }

  if (client.connect (thingSpeakHost, 80)) {
    ThingSpeak.writeField(channelID, field_no, digitalRead(D0), writeAPIKey);
    ThingSpeak.writeField(channelID2, field_no, analogRead(A0), writeAPIKey2);
    Serial.println("\n");
  }
}