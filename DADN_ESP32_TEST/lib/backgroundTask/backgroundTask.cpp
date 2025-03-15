#include "backgroundTask.h"

void DHT_Task (void* pvParameter){

   #if DHTTYPE == DHT11
   //Setup DHT11 sensor
   DHT dht(DHTPIN, DHTTYPE);
   dht.begin();   

   #elif DHTTYPE == DHT20


   #endif

   //DHT running
   while(1){
      #if DHTTYPE == DHT11
      // DHT11 Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
      float h = dht.readHumidity();    // Read humidity
      float t = dht.readTemperature(); // Read temperature as Celsius (the default)

      #elif DHTTYPE == DHT20
      // DHT20 Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
      float h = dht.readHumidity();    // Read humidity
      float t = dht.readTemperature(); // Read temperature as Celsius (the default)
      #endif

      // Now we can publish stuff!
      #if SERIAL_PRINT_DATA == 0
      hum.publish(h);
      temp.publish(t);

      #else
      Serial.print(F("\nSending Humidity val "));
         if (!hum.publish(h)) {
            Serial.println(F("Failed"));
         } else {
            Serial.println(F("OK!"));
         }
            Serial.print(F("\nSending Temperature val "));
         if (!temp.publish(t)) {
            Serial.println(F("Failed"));
         } else {
            Serial.println(F("OK!"));
         }
         Serial.print(F("Humidity: "));
         Serial.print(h);
         Serial.print(F("% Temperature: "));
         Serial.print(t);
         Serial.print(F("°C "));
   #endif

      vTaskDelay(10000 / portTICK_PERIOD_MS); // Delay of 10 second
   }
}

// void Dectect_Task (void* pvParameter){
//    //Setup detect pin
//    pinMode(detect_PIN, INPUT_PULLUP);

//    //Detect running
//    while(1){
//       // Detect if the button is pressed
//       if(digitalRead(detect_PIN)==0){
//          detect_state= !detect_state;
//          dectect.publish(detect_state);
//          if (!dectect.publish(detect_state)) {
//             Serial.println(F("Detect_state publish Failed"));
//          } else {
//             Serial.println(F("Detect_state publish OK!"));
//          }
//       }
//       vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay of 500ms
//    }
// }

void LCD_Task (void* pvParameter){

}

void setupBackgroundTask(){
   xTaskCreate( DHT_Task, "DHT_Task", 3096, NULL, 10, NULL);
   //xTaskCreate( Dectect_Task, "Dectect_Task", 3096, NULL, 10, NULL);
}