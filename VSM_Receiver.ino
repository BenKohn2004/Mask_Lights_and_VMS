#include <ESP8266WiFi.h>
#include <espnow.h>

#include <FastLED.h>

#define DATA_PIN D1  // Define the pin connected to the data input of the LED strip
#define NUM_LEDS 30  // Define the number of LEDs in your strip

#define MY_NAME "SLAVE_NODE"

CRGB leds[NUM_LEDS];

struct __attribute__((packed)) dataPacket {
  int unsigned Right_Score;
  int unsigned Left_Score;
  int unsigned Seconds_Remaining;
  int unsigned Minutes_Remaining;
  bool Green_Light;
  bool Red_Light;
  bool White_Green_Light;
  bool White_Red_Light;
  bool Yellow_Green_Light;
  bool Yellow_Red_Light;
  bool Yellow_Card_Green;
  bool Yellow_Card_Red;
  bool Red_Card_Green;
  bool Red_Card_Red;
  bool Priority_Left;
  bool Priority_Right;
};

dataPacket packet;

unsigned long previousMillis_timer = 0;
unsigned long previousMillis_timer_lights = 0;
unsigned long timer_lights_interval = 3000;
bool update_lights = false;  //Toggles a Bool in the Data Received to turn on and off lights
bool light_selection = 0;    // Green is 0, Red is 1
bool prev_light = false;     // Stores the previous Light Value to detect change

const int buttonPin = 4;             // Pin number where the button is connected, D2
bool buttonState = LOW;              // Current state of the button
bool lastButtonState = LOW;          // Previous state of the button
unsigned long lastDebounceTime = 0;  // Last time the button state changed
unsigned long debounceDelay = 50;    // Delay in milliseconds to debounce the button


void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);  // Set the button pin as INPUT_PULLUP

  Serial.println("");
  Serial.println("");
  Serial.println("Initializing...");
  Serial.print("My Name: ");
  Serial.println(MY_NAME);
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(dataReceived);

  Serial.println("ESP-NOW Initialized.");

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // Define the LED strip configuration
  FastLED.setBrightness(50);                                // Set the brightness (0-255)
  fill_solid(leds, NUM_LEDS, CRGB::Black);                  // Turn off all LEDs initially
  FastLED.show();                                           // Update the LED strip

  Serial.println("FastLED Initialized.");

  Serial.println("Setup Complete");
}

void update_light() {
  if (light_selection == 0) {
    Serial.println("Green Lights Lit.");
    fill_solid(leds, NUM_LEDS, CRGB::Green);  // Turn on all LEDs with a Green color
  }
  if (light_selection == 1) {
    Serial.println("Red Lights Lit.");
    fill_solid(leds, NUM_LEDS, CRGB::Red);  // Turn on all LEDs with a Red color
  }

  FastLED.show();  // Update the LED strip
                   // Sets the Light on Timer
  previousMillis_timer_lights = millis();
}

void loop() {
  if (millis() - previousMillis_timer >= 1000) {
    Serial.print(".");
    previousMillis_timer = millis();
  }

  if (millis() - previousMillis_timer_lights >= timer_lights_interval) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);  // Turn off all LEDs
    FastLED.show();                           // Update the LED strip
  }

  if (update_lights == true) {
    update_light();
    update_lights = false;
  }

  // Toggles Light Selection Buttion
  int reading = digitalRead(buttonPin);  // Read the state of the button

  // Check if the button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // Reset the debounce timer
  }

  // Check if the button state has remained stable for the debounce delay
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed, update the buttonState
    if (reading != buttonState) {
      buttonState = reading;

      // If the button is pressed (LOW), toggle the light_selection variable
      if (buttonState == LOW) {
        light_selection = !light_selection;
        Serial.print("Light Selection: ");
        Serial.println(light_selection ? "Green" : "Red");
      }
    }
  }

  lastButtonState = reading;  // Save the current button state
}

void dataReceived(uint8_t *senderMac, uint8_t *data, uint8_t dataLength) {
  Serial.println("Data Received Callback was called.");
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", senderMac[0], senderMac[1], senderMac[2], senderMac[3], senderMac[4], senderMac[5]);
  Serial.print("Received data from: ");
  Serial.println(macStr);

  memcpy(&packet, data, sizeof(packet));

  if (light_selection == 0) {
    if (packet.Green_Light != prev_light) {
      update_lights = 1;
    }
  }
  if (light_selection == 1) {
    if (packet.Red_Light != prev_light) {
      update_lights = 1;
    }
  }
}
