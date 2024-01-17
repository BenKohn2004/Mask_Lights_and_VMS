# Mask Lights and VMS

The goal of this project is to demonstrate how to use the output of the [Virtual Scoring Machine](https://www.virtualscoringmachine.com/) (VSM) to activate LED lights in a fencing mask.

A [W5500](https://www.aliexpress.us/item/2251832715286410.html) ethernet module was used to read the UDP internet protocol output by VSM using the [reading arduino code](VSM_Parser_and_Transmitter.ino) and then transmit the information through a [Wemos D1 Mini](https://www.aliexpress.us/item/3256805831695231.html) to a receiving Wemos using [ESP-NOW](https://randomnerdtutorials.com/esp-now-esp8266-nodemcu-arduino-ide/) using the [recieving arduino code](VSM_Receiver.ino). The receiving Wemos then using a battery, along with a [battery](https://www.aliexpress.us/item/3256805177143261.html) [charging](https://www.aliexpress.us/item/2255799917197675.html) circuit, would light the LEDs. I used individually addressable LEDs and the lights can be changed to display either the Red or Green lights based on a momentary pushbutton.

One downside of using the Wemos D1 Mini, is that the Chip Select Pin, D8, GPIO15 will cause the Wemos boot to fail if pulled High, which will occur if the W5500 is connected during boot. A poor work around is to disconnect the 3.3V power when starting up the Wemos and then reconnecting the 3.3V to the W5500. The Wemos will then take a couple of minutes to connect with the UDP stream from the VMS computer. A better solution would be to use an [ESP32](https://www.aliexpress.us/item/3256805801999922.html) board that doesn't suffer this limitation.

# Future Considerations

Using an ESP32 chip would simplify the UDP decoder and the ESP32 chip is cheap enough and small enough that it might as well be used throughout the project.

The battery size should also be increased. This project used a 380mAh battery, which, though it worked is not as practical for prolonged use.

Testing should also be done to find the best LEDs for the mask. Either a high LED concentration or even an LED matrix may work well. IP65 protected LED strips may be a good idea to protect against abrasion, moisture and corrosion. Also a runner or holder for the LEDs can be designed and 3D printed to fasten the LEDs to the interior of the mask.

A printed circuit board would assembly and make the mask attachment smaller and easier to use.
