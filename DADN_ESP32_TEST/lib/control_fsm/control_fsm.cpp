#include "control_fsm.h"

LiquidCrystal_I2C lcd(0x27,LCD_COLS,LCD_ROWS);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int current_row = 0;
int lcd_page = 0 ;
int refresh_cycle = 0;

 
// SOME SUPPORT FUNCTIONS

void initLCD(){
   lcd.begin(LCD_COLS, LCD_ROWS);
   lcd.init();
   lcd.backlight();
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Hello, world!");
   delay(1000);
   lcd.clear();
}

/*
@brief setLCDPage and live time
@param page: page number
@param live_time: time to live of the page in seconds
*/
void setLCDPage(int page, int live_time)
{
   lcd_page = page;
   refresh_cycle = live_time / REFRESH_TIME;
   displayLCD();
}

// @brief displayLCD
void displayLCD(){
   switch (lcd_page){
      case PAGE_MAIN:
         //PRINT MAIN PAGE (TEMP, HUM, LIGHT)
         // ROW0: T:25 H:100  L:100
         // ROW1: DD/MM/YYYY HH:MM
         lcd.clear();
         lcd.setCursor(0, 0); lcd.print("T:"); lcd.print(global_temp);
         lcd.setCursor(5, 0); lcd.print(" H:"); lcd.print(global_hum);
         lcd.setCursor(11, 0); lcd.print(" L:"); lcd.print(global_light);
         lcd.setCursor(0, 1); lcd.print(global_day); lcd.print("/"); lcd.print(global_month); lcd.print("/"); lcd.print(global_year);
         lcd.setCursor(11, 1); lcd.print(global_hour); lcd.print(":"); lcd.print(global_minute);
         break;

      case SETTING_LED12:
         //PRINT LED12 PAGE (LED1, LED2)
         // ROW0: LED1: <ON>  <-
         // ROW1: LED2: <OFF> <-
         lcd.clear();
         lcd.setCursor(0, 0); lcd.print("LED1: "); lcd.print(global_led1_state == 1 ? "<ON>" : "<OFF>");
         lcd.setCursor(0, 1); lcd.print("LED2: "); lcd.print(global_led2_state == 1 ? "<ON>" : "<OFF>");
         lcd.setCursor(14, current_row); lcd.print("<-");
         break;

      case SETTING_LED34:
         //PRINT LED34 PAGE (LED3, LED4)
         // ROW0: LED3: <ON>  <-
         // ROW1: LED4: <OFF> <-
         lcd.clear();
         lcd.setCursor(0, 0); lcd.print("LED3: "); lcd.print(global_led3_state == 1 ? "<ON>" : "<OFF>");
         lcd.setCursor(0, 1); lcd.print("LED4: "); lcd.print(global_led4_state == 1 ? "<ON>" : "<OFF>");
         lcd.setCursor(14, current_row); lcd.print("<-");
         break;

      case SETTING_FAN:
         //PRINT FAN PAGE (FAN)
         // ROW0: FAN: <ON>  <-
         lcd.clear();
         lcd.setCursor(0, 0); lcd.print("FAN: "); lcd.print( "<");lcd.print(global_fan_state);lcd.print( ">");
         lcd.setCursor(14, current_row); lcd.print("<-");
         break;
      
      case SETTING_DOOR:
         //PRINT DOOR PAGE (DOOR)
         // ROW0: DOOR: <OPEN>  <-
         lcd.clear();
         lcd.setCursor(0, 0); lcd.print("DOOR: "); lcd.print(global_door_state == 1 ? "<OPEN>" : "<CLOSE>");
         lcd.setCursor(14, current_row); lcd.print("<-");
         break;

      case NOTICE_DOOR:
         //PRINT NOTICE DOOR PAGE
         // ROW0: DOOR IS OPEN
         lcd.clear();
         lcd.setCursor(0, 0); lcd.print(global_door_state == 1 ? "DOOR IS OPEN" : "DOOR IS CLOSE");
         break;

      case NOTICE_DETECT:
         //PRINT NOTICE DETECT PAGE
         // ROW0: DETECT IS ON
         lcd.clear();
         lcd.setCursor(0, 0); lcd.print(global_detect_state == 1 ? "HUMAN DETECTED" : "HUMAN NOT DETECTED");
         break;
   }

}

void LCD_Task (void* pvParameter){
   initLCD();
   while(1){
      refresh_cycle--;
      if(refresh_cycle == 0){
         setLCDPage(PAGE_MAIN, PAGE_MAIN_LIVE_TIME);
         displayLCD();
      }

      vTaskDelay( 250 / portTICK_PERIOD_MS); // Delay of 250ms
   }
}




 