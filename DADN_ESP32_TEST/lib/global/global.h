#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "systemConfig.h"
#include "LiquidCrystal_I2C.h"

#if DHTTYPE == DHT11
#include "DHT.h"
#elif DHTTYPE == DHT20
#include "DHT20.h"
#endif

//System Sharing MQTT Client
extern Adafruit_MQTT_Publish temp;
extern Adafruit_MQTT_Publish hum;   
extern Adafruit_MQTT_Publish light;
extern Adafruit_MQTT_Publish dectect;

//System Sharing MQTT Subscribe
extern Adafruit_MQTT_Subscribe onoffbutton1;
extern Adafruit_MQTT_Subscribe onoffbutton2;
extern Adafruit_MQTT_Subscribe onoffbutton3;
extern Adafruit_MQTT_Subscribe onoffbutton4;
extern Adafruit_MQTT_Subscribe onoffdoor;
extern Adafruit_MQTT_Subscribe controll_fan;

//System Sharing Sensor Data and Device State
extern uint8_t global_temp;
extern uint8_t global_hum;
extern uint8_t global_light;
extern uint8_t global_door_state;
extern uint8_t global_detect_state;
extern uint8_t global_fan_state;
extern uint8_t global_led1_state;
extern uint8_t global_led2_state;
extern uint8_t global_led3_state;
extern uint8_t global_led4_state;

extern uint16_t global_year;
extern uint8_t global_month;
extern uint8_t global_day;
extern uint8_t global_hour;
extern uint8_t global_minute;
extern uint8_t global_second;

#endif