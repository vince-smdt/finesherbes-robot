#ifndef LCD_H
#define LCD_H
#include <LiquidCrystal.h>
#include "General.h"

LiquidCrystal lcd(14, 15, 16, 17, 18, 19);
unsigned long time_now = 0;
const int lcd_period = 500;


void LCD_setup(){
lcd.begin(16,2);
avancer(0, 0);

}

void LCD_Robot(){
  //  lcd.print("Service Table 1");
    //delay(1000);

    if(millis() >= time_now + lcd_period){
        time_now+=lcd_period;
        lcd.setCursor(0,1);
        //lcd.clear();
        lcd.print("Table  4");
    }
}



#endif