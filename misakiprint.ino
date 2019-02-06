//日本語表示
void misakiPrint(int x, int y, char * pUTF8) {
  int n = 0;
  byte buf[40][8];  //320x8ドットのバナー表示パターン
  while (*pUTF8)
    //pUTF8 = getFontData(&buf[n++][0], pUTF8);  // フォントデータの取得

  // 文字の描画
  for (byte i = 0; i < 8; i++) {
    for (byte j = 0; j < n; j++) {
      for (byte k = 0; k < 8; k++) {
        if (bitRead(buf[j][i], 7 - k)) {
          M5.Lcd.drawPixel(x + 8 * j + k , y + i, TFT_WHITE);
        }
      }
    }
  }
}
