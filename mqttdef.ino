#include <WiFi.h>
#include <PubSubClient.h>
#include "BLEDevice.h"
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "Settings.h"

WiFiClient espClient;
PubSubClient client(espClient);

// Variabelen bluetooth-scanner
BLEScan* pBLEScan;
static BLEAddress *pServerAddress;
bool deviceFound = false; // apparaat gevonden?
int deviceRSSI = 0; // signaalsterkte

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice Device) {
    // Achterhaal mac-adres van bluetooth-apparaat
    pServerAddress = new BLEAddress(Device.getAddress());

    // Kijk of dit het gevraagde adres is
    if (strcmp(pServerAddress->toString().c_str(), knownAddress) == 0) {
      deviceRSSI = Device.getRSSI();
      deviceFound = true;

      Device.getScan()->stop();
      delay(100);      
    }
  }
};

void setup() {
  // De pin met led is voor output
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_poort);
  
  // Bluetooth instellen
  BLEDevice::init("Mijn ESP32");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(activeScan); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value  
}

void setup_wifi() {
  delay(100);
  // Verbinding met wifi-netwerk opzetten
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, wifipassword);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi verbonden");
  Serial.println("IP-adres: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop tot verbinding is opgezet
  while (!client.connected()) {
    Serial.print("Opzetten MQTT-verbinding...");
    if (client.connect(mqtt_clientid, mqtt_user, mqtt_password)) {
      Serial.println("verbonden");
    } else {
      Serial.print("mislukt, rc=");
      Serial.print(client.state());
      Serial.println(" probeer opnieuw na 5 seconden");
      delay(5000);
    }
  }
}
void loop() {
  // Verbinden met mqtt-server
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Start bluetooth-scan
  deviceFound = false;
  //Serial.println("Zet deviceFound op false");
  BLEScanResults foundDevices = pBLEScan->start(scanTime);

  Serial.print("Aantal apparaten gevonden: ");
  Serial.println(foundDevices.getCount());
    
  // Temperatuur LM35 inlezen en converteren naar char array
  double tempC = (analogRead(ANALOG_IN) / 2048.0) * 330;
  char tempString[8];
  dtostrf(tempC, 2, 1, tempString);

  // Temperatuur publiceren
  Serial.print("Publiceer temperatuur: ");
  Serial.println(tempString);
  client.publish(mqtt_topicTemp, tempString);

  // Status gevonden apparaat publiceren
  if (deviceFound) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Publiceer: apparaat zichtbaar");
    client.publish(mqtt_topicAanwezigheid, "home");
    Serial.print("RSSI: ");
    Serial.println(deviceRSSI);
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Publiceer: apparaat niet zichtbaar");
    client.publish(mqtt_topicAanwezigheid, "not_home");
  }

  // Maak buffer leeg om geheugen vrij te maken
  pBLEScan->clearResults();
  delay(100);
}
