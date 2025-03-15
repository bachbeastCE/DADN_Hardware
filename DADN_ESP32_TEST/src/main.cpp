#include <Arduino.h>
#include "global.h"
#include "backgroundTask.h"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiClientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup feeds called 'temp' & 'hum' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
// feedname should be the same as set in dashboard for temp and hum gauges
Adafruit_MQTT_Publish temp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/DADN_Temp");  // Puslish temperature feed
Adafruit_MQTT_Publish hum = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/DADN_Humi"); // Publish humidity feed
Adafruit_MQTT_Publish light = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/DADN_Light");  // Puslish temperature feed
Adafruit_MQTT_Publish dectect = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/DADN_Detect"); // Publish dectect feed

// Setup a feed called 'onoff' for controlling LED.
Adafruit_MQTT_Subscribe onoffbutton1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/DADN_LED_1");
Adafruit_MQTT_Subscribe onoffbutton2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/DADN_LED_2");
Adafruit_MQTT_Subscribe onoffbutton3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/DADN_LED_3");
Adafruit_MQTT_Subscribe onoffbutton4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/DADN_LED_4");
Adafruit_MQTT_Subscribe onoffdoor = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/DADN_Door");
Adafruit_MQTT_Subscribe controll_fan = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/DADN_Fan");

void MQTT_connect();
                                                                                                    
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(led1_PIN, OUTPUT);
  pinMode(led2_PIN, OUTPUT);
  //pinMode(ledPin3, OUTPUT);
  //pinMode(ledPin4, OUTPUT);
  pinMode(door_PIN, OUTPUT);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton1);
  mqtt.subscribe(&onoffbutton2);
  mqtt.subscribe(&onoffbutton3);
  mqtt.subscribe(&onoffbutton4);
  mqtt.subscribe(&onoffdoor);

  setupBackgroundTask();  
}

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();
  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here
  Adafruit_MQTT_Subscribe *subscription;
  // Wait 2000 milliseconds, while we wait for data from subscription feed. After this wait, next code will be executed
  while ((subscription = mqtt.readSubscription(2000))) {
    if (subscription == &onoffbutton1) {
      #if SERIAL_PRINT_DATA == 0
        char *value = (char *)onoffbutton1.lastread;
      #else
        Serial.print(F("Got: "));
        char *value = (char *)onoffbutton1.lastread;
        Serial.println((char *)onoffbutton1.lastread);
        Serial.print(F("Received: ")); // Display the value received from dashboard
        Serial.println(value);
      #endif

      // Apply message to OnOff
      String message = String(value);
      Serial.println(message);
      message.trim();
      if (message == "1") {
        digitalWrite(led1_PIN, HIGH);
        Serial.println("LED ON");
      }
      if (message == "0") {
        digitalWrite(led1_PIN, LOW);
        Serial.println("LED OFF");
      }
    }
    if (subscription == &onoffbutton2) {
      #if SERIAL_PRINT_DATA == 0
        char *value = (char *)onoffbutton1.lastread;
      #else
        Serial.print(F("Got: "));
        char *value = (char *)onoffbutton1.lastread;
        Serial.println((char *)onoffbutton1.lastread);
        Serial.print(F("Received: ")); // Display the value received from dashboard
        Serial.println(value);
      #endif

      // Apply message to OnOff
      String message = String(value);
      Serial.println(message);
      message.trim();
      if (message == "1") {
        digitalWrite(led2_PIN, HIGH);
        Serial.println("LED ON");
      }
      if (message == "0") {
        digitalWrite(led2_PIN, LOW);
        Serial.println("LED OFF");
      }
    }
    if (subscription == &onoffdoor) {
      #if SERIAL_PRINT_DATA == 0
        char *value = (char *)onoffdoor.lastread;
      #else
        Serial.print(F("Got: "));
        char *value = (char *)onoffdoor.lastread;
        Serial.println((char *)onoffdoor.lastread);
        Serial.print(F("Received: ")); // Display the value received from dashboard
        Serial.println(value);
      #endif

      // Apply message to OnOff
      String message = String(value);
      Serial.println(message);
      message.trim();
      if (message == "1") {
        digitalWrite(door_PIN, HIGH);
        Serial.println("DOOR OPENED");
      }
      if (message == "0") {
        digitalWrite(door_PIN, LOW);
        Serial.println("DOOR CLOSED");
      }
    }
  }
  // Check if 20 seconds have passed since the last sensor read

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
    if(! mqtt.ping()) {
    mqtt.disconnect();
    }
  */
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}



