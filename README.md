# Mask_Lights_and_VMS

The goal of this project is demonstrate how to use the output of the [Virtual Scoring Machine](https://www.virtualscoringmachine.com/) (VSM) to activate LED lights in a fencing mask.

A [W5500](https://www.aliexpress.us/item/2251832715286410.html) ethernet module was used to read the UDP internet protocol output by VSM and then transmit the information through a [Wemos D1 Mini](https://www.aliexpress.us/item/3256805831695231.html) to a receiving Wemos using [ESP-NOW](https://randomnerdtutorials.com/esp-now-esp8266-nodemcu-arduino-ide/). The receiving Wemos then using a battery, along with a [battery](https://www.aliexpress.us/item/3256805177143261.html) [charging](https://www.aliexpress.us/item/2255799917197675.html) circuit, would light the LEDs. I used individually addressable LEDs and the lights can be changed to display either the Red or Green lights based on a momentary pushbutton.

One downside of using the Wemos D1 Mini, is that the Chip Select Pin, D8, GPIO15 will cause the Wemos boot to fail if pulled High, which will occur if the W5500 is connected during boot. A poor work around is to disconnect the 3.3V power when starting up the Wemos and then reconnecting the 3.3V to the W5500. The Wemos will then take a few minutes to connect with UDP stream from the VMS computer. A better solution would be to use an [ESP32](https://www.aliexpress.us/item/3256805801999922.html) board that doesn't suffer this limitation.

