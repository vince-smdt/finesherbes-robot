#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal.h>
#include "General.h"
#include "Globales.h"

LiquidCrystal lcd(14, 15, 16, 17, 18, 19);
unsigned long time_now = 0;
const int lcd_period = 500;
void LCD_Robot_en_service();
void LCD_Robot_au_repos();

void LCD_setup(){
  lcd.begin(16,2);
}

void LCD_Tout(){
  switch (g_etat){
    case INITIER_DEPART_LIVRAISON:
    case SUIVRE_LIGNE_VERS_RANGEE:
    case TOURNER_VERS_TABLE_CLIENT:
    case SUIVRE_LIGNE_VERS_TABLE:
    case PRET_LEVER_PLATEAU:
    case LEVER_PLATEAU:
    case FINI_LEVER_PLATEAU:
    case TOURNER_VERS_COTE_TABLE_CUISINE:
    case SUIVRE_LIGNE_VERS_COLONNE_CUISINE:
    case TOURNER_VERS_TABLE_CUISINE:
    case SUIVRE_LIGNE_VERS_TABLE_CUISINE:
    case RECULER_DANS_CUISINE:
    case TOURNER_VERS_SORTIE_CUISINE:
    case SUIVRE_LIGNE_VERS_SORTIE_CUISINE:
    case TOURNER_VERS_COLONNE_PRINCIPALE_CUISINE:
    case SUIVRE_LIGNE_VERS_COLONNE_CENTRE_DEPUIS_CUISINE:
    case SUIVRE_LIGNE_JUSQUA_BRAS_SOUS_PLATEAU_CUISINE:
    case TOURNER_VERS_TABLES_CLIENT:
    case PRET_DEPOSER_PLATEAU:
    case DEPOSER_PLATEAU:
    case SUIVRE_LIGNE_JUSQUA_BRAS_SUR_TABLE_CLIENT: {
      LCD_Robot_en_service();
      break;
    }

    case FINI_DEPOSER_PLATEAU:
    case DEPART:
    case ATTENDRE_PROCHAINE_COMMANDE:
    case INITIER_RETOUR_BASE:
    case RECULER_VERS_LIGNE_CENTRALE:
    case TOURNER_VERS_LIGNE_CENTRALE:
    case SUIVRE_LIGNE_VERS_LIGNE_CENTRALE:
    case TOURNER_VERS_CUISINE:
    case SUIVRE_LIGNE_VERS_CUISINE: {
      
      LCD_Robot_au_repos();
      break;
    }
  }
}

void LCD_Robot_en_service(){
  //  lcd.print("Service Table 1");
  //delay(1000);

  if(millis() >= time_now + lcd_period){
    time_now+=lcd_period;
   // lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    Table  ");
    lcd.print(g_commande->NumTable);
   // lcd.setCursor(0,1);
   // lcd.print("Service en cours");


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
    //Serial.print("Fonctionne");
    lcd.setCursor(0,1);
    lcd.print("   Bienvenue!");

  }
}

#endif // LCD_H
