#ifndef LCD_H
#define LCD_H
#include <LiquidCrystal.h>
#include "General.h"

LiquidCrystal lcd(14, 15, 16, 17, 18, 19);
unsigned long time_now = 0;
const int lcd_period = 500;


void LCD_setup(){
lcd.begin(16,2);
avancer(0, 0);//********************pour tests pas que le robot pate en fou furieux*********

}

void LCD_Robot_en_service(){
  //  lcd.print("Service Table 1");
    //delay(1000);

    if(millis() >= time_now + lcd_period){
        time_now+=lcd_period;
        lcd.setCursor(0,0);
        //lcd.clear();
        lcd.print("Service en cours");
       lcd.setCursor(0,1);
       lcd.print("    Table  4");
    }
}
void LCD_Robot_au_repos(){
  //  lcd.print("Service Table 1");
    //delay(1000);

    if(millis() >= time_now + lcd_period){
        time_now+=lcd_period;
        lcd.setCursor(0,0);
        //lcd.clear();
        lcd.print("  Fines Herbes");
       lcd.setCursor(0,1);
       lcd.print("   Bienvenue!");
    }
}



#endif