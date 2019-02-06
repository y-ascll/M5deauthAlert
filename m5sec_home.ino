//ホーム画面
void home() {

  m5.update();

  //LCD
  m5.Lcd.setBrightness(100);
  m5.Lcd.fillScreen(TFT_BLACK);
  m5.Lcd.setTextSize(4);
  m5.Lcd.printf("M5Sec-test1");

  //misakiPrint(0, 32, "卒研プロダクトのテスト版です。");
  //misakiPrint(0, 48, "ボタンAで周囲のアクセスポイントをスキャンをし情報を取得します。");
  //misakiPrint(0, 64, "ボタンBは選択したアクセスポイントを監視します。");
  //misakiPrint(0, 80, "ボタンCは現在のM5Stackの状態を表示します。" );

  m5.Lcd.setTextSize(3);
  m5.Lcd.setCursor(36, 215);
  m5.Lcd.printf("BTNA");
  m5.Lcd.setCursor(128, 215);
  m5.Lcd.printf("BTNB");
  m5.Lcd.setCursor(224, 215);
  m5.Lcd.printf("BTNC");

  while (true) {
    if (m5.BtnA.wasPressed()) {
      ap_scan();
      m5.update();
      cursor();
      lcd_clear();
      m5.Lcd.setCursor(0, 0);
      m5.Lcd.print("Channel:");
      m5.Lcd.printf("%d", ch);
      delay(2000);
      lcd_clear();
      home();
      break;
    }

    if (m5.BtnB.wasPressed()) {
      if (ch == 0) {
        m5.update();
        lcd_clear();
        m5.Lcd.printf("Channel is not selected.\nPress ButtonA and select target AP.");
        m5.Lcd.setTextSize(3);
        m5.Lcd.setCursor(144, 215);
        m5.Lcd.printf("OK");
        while (true) {
          if (m5.BtnB.wasPressed()) {
            lcd_clear();
            setup();
            break;
          }
          m5.update();
        }
        break;
      }
      lcd_clear();
      m5.Lcd.printf("Channel %d is selected.", ch);
      m5.update();
      delay(2000);
      continue;
    }

    m5.update();

    if (m5.BtnC.wasPressed()) {
      return ;
    }
  }
}

