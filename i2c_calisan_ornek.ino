#include <LiquidCrystal_I2C_AvrI2C.h>

LiquidCrystal_I2C_AvrI2C lcd(0x27,16,2);  // 16 karakter 2 satır için - 20x4 satır için (0x27,20,4) yazın

void setup()
{
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("MERHABA"); //İlk satıra yazalım
  lcd.setCursor(0,1);
  lcd.print("OSMAN CETINKAYA"); //İkinci satıra yazalım
}

void loop()
{
}                                                                                             
