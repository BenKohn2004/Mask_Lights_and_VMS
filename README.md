# Mask Lights and VSM

A demonstration of the Mask Lights on [Youtube](https://youtu.be/llAjzOXssoA?si=W8I_Yx8YUjLXj7pW). Yes, I know it is a saber mask. It is what I installed the lights in for the proof of concept.

The goal of this project is to demonstrate how to use the output of the [Virtual Scoring Machine](https://www.virtualscoringmachine.com/) (VSM) to activate LED lights in a fencing mask. Though I chose to use the output from the VSM, this code borrows heavily from my projects parsing the data from the Favero machine and this project can reasonably be modified to use the output from a Favero.

A [W5500](https://www.aliexpress.us/item/2251832715286410.html) ethernet module was used to read the UDP internet protocol output by VSM using the [parse and transmit arduino code](VSM_Parser_and_Transmitter.ino) and then transmit the information through a [Wemos D1 Mini](https://www.aliexpress.us/item/3256805831695231.html) to a receiving Wemos using [ESP-NOW](https://randomnerdtutorials.com/esp-now-esp8266-nodemcu-arduino-ide/) with the [recieving arduino code](VSM_Receiver.ino). The receiving Wemos then using a battery, along with a [battery](https://www.aliexpress.us/item/3256805177143261.html) [charging](https://www.aliexpress.us/item/2255799917197675.html) circuit, would light the LEDs. The circuit would be contained in a 3D printed [enclosure](https://cad.onshape.com/documents/e3f7a63834521caf10d04e51/w/f984a904ae005ded8926723e/e/6f94e1e5a87ab69b3e5f6609?renderMode=0&uiState=65a7ed92b8541a012c2a0323) and held in place using [velcro cable ties](https://www.aliexpress.us/item/3256805287600600.html). I used [individually addressable LEDs](https://www.aliexpress.us/item/2251801850504415.html) and the lights can be changed to display either the Red or Green lights based on a momentary pushbutton.

One downside of using the Wemos D1 Mini, is that the Chip Select Pin, D8, GPIO15 will cause the Wemos boot to fail if pulled High, which will occur if the W5500 is connected during boot. A poor work around is to disconnect the 3.3V power when starting up the Wemos and then reconnecting the 3.3V to the W5500. The Wemos will then take a couple of minutes to connect with the UDP stream from the VMS computer. A better solution would be to use an [ESP32](https://www.aliexpress.us/item/3256805801999922.html) board that doesn't suffer this limitation.

I also needed to occassionally disable the Virtual Network Switches VMnet1 and VMnet8 under Network Connections so that the UDP stream would go to the Ethernet port. It may also be beneficial to assign a static ip address to the parsing/transmitting Wemos code.

# Future Considerations

Using an ESP32 chip would simplify the UDP decoder and the ESP32 chip is cheap enough and small enough that it might as well be used throughout the project.

The battery size should also be increased. This project used a 380mAh battery, which, though it worked, is not as practical for prolonged use.

Testing should also be done to find the best LEDs for the mask. Either a high LED concentration or even an LED matrix may work well. IP65 protected LED strips may be a good idea to protect against abrasion, moisture and corrosion. Also a runner or holder for the LEDs can be designed and 3D printed to fasten the LEDs to the interior of the mask.

A printed circuit board would make the assembly smaller and easier to use.
