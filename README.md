# Omschrijving
Dit is een project met de ESP32-microcontroller behorende bij een artikel in Computer!Totaal. Er wordt een temperatuurmeting gedaan met een analoge LM35 temperatuursensor. Ook wordt de aanwezigheid van een BLE (Bluetooth Low Energy) detecteerd. De volgende gegevens worden doorgegeven aan een MQTT-broker:
* De aanwezigheid van een Bluetooth-apparaat met status `home` of `not_home`
* De gemeten temperatuur

In het artikel gebruiken we de MQTT-broker Mosquitto die als add-on voor Home Assistant beschikbaar is. We gebruiken zelf een Xiamoi Mi Band 3 maar elke andere Bluetooth-tag werkt doorgaans ook. Het belangrijkste is dat het MAC-adres een vaste waarde heeft, op een smartphone is dat zelden het geval (om je privacy te beschermen). Bij de Mi Band 3 is het daarvoor overigens wel nodig de optie `Detecteerbaar` op `Aan` te zetten in de Mi-app!

# Configuratie
In [Settings.h](Settings.h) vind je alle instellingen voor het programma. Pas dit aan naar je eigen situatie.

## Partitie-indeling
Het is in veel gevallen nodig de partitie-indeling voor het ESP32-bordje aan te passen, omdat alle bibliotheken anders niet passen! In Arduino ga je hiervoor naar File / Preferences en volg je de link naar preferences.txt door er op te klikken. Sluit Arduino. Blader nu naar packages\esp32\hardware\esp32\1.0.1. Verander in boards.txt voor jouw bordje de waarde bij maximale uploadgrootte. In ons voorbeeld met de Adafruit ESP32 Feather passen we de waarde featheresp32.upload.maximum_size=1310720 aan naar 1638400. Bewerk daarna het bestand default.csv (tip: bewaar het origineel als default.csv.org) uit de map tools/partitions met een teksteditor en verander dit naar het volgende:
```
# Name,   Type, SubType, Offset,  Size, Flags
nvs,      data, nvs,     0x9000,  0x5000,
otadata,  data, ota,     0xe000,  0x2000,
app0,     app,  ota_0,   0x10000, 0x190000,
app1,     app,  ota_1,   0x1A0000,0x190000,
eeprom,   data, 0x99,    0x330000,0x1000,
spiffs,   data, spiffs,  0x331000,0x0CF000,
```

![Alt text](project.jpg?raw=true "Title")

---

# Meer informatie
Voor meer informatie verwijzen we graag naar het oorspronkelijke artikel in Computer!Totaal over aanwezigheidsdectie met Bluetooth Low Energy in combinatie met Home Assistant en een MQTT-broker.
