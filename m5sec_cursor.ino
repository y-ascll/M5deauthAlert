//カーソルの上下移動
void cursor () {

  int i = 0;

  cursor_engine(i);

  while (true) {

    if (m5.BtnA.wasPressed()) {
      i = i - 1;
      cursor_engine(i);
      m5.update();
      continue;
    }

    if (m5.BtnB.wasPressed()) {
      i = i + 1;
      cursor_engine(i);
      m5.update();
      continue;
    }

    m5.update();

    if (m5.BtnC.wasPressed()) {
      ch = preferences.getUInt("channel", WiFi.channel(i));
      
      break;
    }
  }
}

void cursor_engine(int x) {
  lcd_clear();
  m5.Lcd.println("Select Target AP");

  m5.Lcd.setTextSize(3);
  m5.Lcd.setCursor(36, 215);
  m5.Lcd.printf("BACK");
  m5.Lcd.setCursor(128, 215);
  m5.Lcd.printf("NEXT");
  m5.Lcd.setCursor(224, 215);
  m5.Lcd.printf("SLCT");

  m5.Lcd.setCursor(0, 16);
  m5.Lcd.setTextSize(2);
  m5.Lcd.setTextColor(RED);
  m5.Lcd.print("Target>>");
  m5.Lcd.print(x);
  m5.Lcd.print(":");
  m5.Lcd.println(WiFi.SSID(x));
  m5.Lcd.setCursor(0, 48);
  m5.Lcd.setTextSize(2);
  m5.Lcd.setTextColor(WHITE);
  m5.Lcd.println("Information");
  m5.Lcd.print("ESSID");
  m5.Lcd.print(":");
  m5.Lcd.println(WiFi.SSID(x));
  m5.Lcd.print("BSSID");
  m5.Lcd.print(":");
  m5.Lcd.println(WiFi.BSSIDstr(x));
  m5.Lcd.print("RSSI");
  m5.Lcd.print(":");
  m5.Lcd.print(WiFi.RSSI(x));
  m5.Lcd.println("dBm");
  m5.Lcd.print("Channel");
  m5.Lcd.print(":");
  m5.Lcd.println(WiFi.channel(x));
}
