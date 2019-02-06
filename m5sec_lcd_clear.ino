//画面クリア
void lcd_clear() {
  m5.Lcd.fillScreen(TFT_BLACK);
  m5.Lcd.setCursor(0, 0);
  m5.Lcd.setTextColor(WHITE);
  m5.Lcd.setTextSize(2);
}
