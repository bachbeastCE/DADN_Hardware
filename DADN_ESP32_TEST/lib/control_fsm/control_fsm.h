#ifndef control_fsm_h
#define control_fsm_h

#include "global.h"

// LCD
#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

// Define control states
#define INIT 0

#define PAGE_MAIN 10

#define SETTING_LED12 20
#define SETTING_LED34 21
#define SETTING_FAN 22
#define SETTING_DOOR 23

#define NOTICE_DOOR 30
#define NOTICE_DETECT 31

// Define the refresh time
#define REFRESH_TIME 250; // 250ms
#define PAGE_MAIN_LIVE_TIME 30000 // 30s


// Define support variables

void initLCD();
void setControlState(int page, int live_time);
void displayLCD();
void controlFSM();

#endif