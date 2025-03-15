#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H

/************************* Setting *********************************/

#define SERIAL_PRINT_DATA 0
#define BOARD ESP32_DEVKIT_V1

/************************* PIN Setup *********************************/

#if BOARD == ESP32_DEVKIT_V1 //PIN SETUP FOR ESP32_DEVKIT_V1

#define DHTPIN   15           // Digital pin connected to the DHT sensor
#define led1_PIN   27         // Connect LED on pin D27
#define led2_PIN   26         // Connect LED on pin D26
//#define led3_PIN   27       // Connect LED on pin 
//#define led4_PIN   26       // Connect LED on pin 
#define door_PIN   25         // Connect LED on pin D25
#define detect_PIN   5        // Connect LED on pin D5

//PIN SETUP FOR YOLOBIT
#elif BOARD == YOLOBIT
#include "pinsYolobit.h"

#define DHTPIN   15           // Digital pin connected to the DHT sensor
#define led1_PIN   27         // Connect LED on pin D27
#define led2_PIN   26         // Connect LED on pin D26
//#define led3_PIN   27       // Connect LED on pin 
//#define led4_PIN   26       // Connect LED on pin 
#define door_PIN   25         // Connect LED on pin D25
#define detect_PIN   5        // Connect LED on pin D5

#endif

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "Duy Bach"   // Replace with your Wi-Fi SSID
#define WLAN_PASS       "28082004"   // Replace with your Wi-Fi Password

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                                 // use 8883 for SSL
#define AIO_USERNAME    "BachbeastCE"                        // Replace with your Adafruit IO Username
#define AIO_KEY         "aio_eaue76HZurAww7Kso1LWJUbRs8Q8"   // Replace with your Adafruit IO Key

/************************* ETC... Setup *********************************/

#define DHTTYPE  DHT11  // Type of DHT Sensor, DHT11 or DHT22

#endif