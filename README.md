# Omschrijving
Dit is een project met de ESP32-microcontroller behorende bij een artikel in Computer!Totaal. Er wordt een temperatuurmeting gedaan met een analoge LM35 temperatuursensor. Ook wordt de aanwezigheid van een BLE (Bluetooth Low Energy) detecteerd. De volgende gegevens worden doorgegeven aan een MQTT-broker:
* De aanwezigheid van een Bluetooth-apparaat met status `home` of `not_home`
* De gemeten temperatuur

In het artikel gebruiken we de MQTT-broker Mosquitto die als add-on voor Home Assistant beschikbaar is. We gebruiken zelf een Xiamoi Mi Band 3 maar elke andere Bluetooth-tag werkt doorgaans ook. Het belangrijkste is dat het MAC-adres een vaste waarde heeft, op een smartphone is dat zelden het geval (om je privacy te beschermen).

# Configuratie
In [Settings.h](Settings.h) vind je alle instellingen voor het programma. Pas dit aan naar je eigen situatie.

![Alt text](project.jpg?raw=true "Title")
