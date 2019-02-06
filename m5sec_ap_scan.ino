//APのリスト表示
void ap_scan() {

  //WiFi.mode(WIFI_STA);
  //WiFi.disconnect();
  
  lcd_clear();

  m5.Lcd.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  m5.Lcd.println("scan done");
  if (n == 0) {
    m5.Lcd.println("no networks found");
  } else {
    m5.Lcd.print(n);
    m5.Lcd.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      m5.Lcd.print(i + 1);
      m5.Lcd.print(": ");
      m5.Lcd.print(WiFi.SSID(i));
      m5.Lcd.print(" (");
      m5.Lcd.print(WiFi.RSSI(i));
      m5.Lcd.print(")");
      m5.Lcd.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(60);
    }
  }
  delay(2000);
}
