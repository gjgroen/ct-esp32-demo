// Vervang door SSID van WiFi-netwerk
#define ssid "wifissid"

// Vervang door wachtwoord van WiFi-netwerk
#define wifipassword "password"

// Vervang door ip-adres van MQTT-server (bijvoorbeeld van Home Assistant)
#define mqtt_server "192.168.0.120"

// Vervang door poortnummer van de MQTT-server (standaard 1883)
#define mqtt_poort 1883

// Vervang door gebruikersnaam voor toegang tot MQTT-server
#define mqtt_user "esp32"

// Vervang door password voor hierboven opgegeven mqtt_user
#define mqtt_password "mqttpwd"

// Vervang door beschrijvende client id voor aanmelden bij MQTT-server
#define mqtt_clientid "ESP32Gebruiker"

// Geef aan in welke topic de temperatuur gepubliceerd moet worden
#define mqtt_topicTemp "esp32/temperatuur"

// Geef de topic voor de aanwezigheidsinformatie aan, bijvoorbeeld locatie/gebruiker
#define mqtt_topicAanwezigheid "locatie/gebruiker"

// Pin waarop de LED is aangesloten
#define LED_PIN 15

// Pin waarop de LM35 is aangesloten
#define ANALOG_IN A2

// Definieer parameters voor bluetooth-scanner
#define scanTime 15 // Tijd voor enkele scan in seconden
#define activeScan true // Active scan gebruikt meer stroom maar geeft sneller resultaten

// Bluetooth MAC-adres van het apparaat voor aanwezigheidsdetectie, bijvooorbeeld d2:38:ce:c8:c9:ca
#define knownAddress "d2:38:ce:c8:c9:ca"
