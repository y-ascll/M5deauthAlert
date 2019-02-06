//main
#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include <stdio.h>
#include <string>
#include <cstddef>
#include <Wire.h>
#include <Preferences.h>
#include <M5Stack.h>
#include <SPI.h>
#include <Ethernet2.h>
#include "WiFi.h"
#include "M5StackUpdater.h"
#include "FS.h"
#include "SD_MMC.h"
#include "Buffer.h"
//#include <misakiUTF16.h>

using namespace std;

/* ===== compile settings ===== */
#define MAX_CH 14       // 1 - 14 channels (1-11 for US, 1-13 for EU and 1-14 for Japan)
#define SNAP_LEN 2324   // max len of each recieved packet

//#define USE_SD
#ifdef USE_SD
#define BUTTON_PIN 5    // button to change the channel
#endif

#define USE_TFT
#define FLIP_DISPLAY    // comment out if you don't like to flip it
#define SDA_PIN 26
#define SCL_PIN 27
#define MAX_X 320
#define MAX_Y 220

#if CONFIG_FREERTOS_UNICORE
#define RUNNING_CORE 0
#else
#define RUNNING_CORE 1
#endif

//Wired
#define SCK 18
#define MISO 19
#define MOSI 23
#define CS 26

//  01 05 00 01 02 00 9d 6a
char uart_buffer[8] = {0x01, 0x05, 0x00, 0x01, 0x02, 0x00, 0x9d, 0x6a};
char uart_rx_buffer[8] = {0};

char Num = 0;
char stringnum = 0;
unsigned long W5500DataNum = 0;
unsigned long Send_Num_Ok = 0;
unsigned long Rec_Num = 0;
unsigned long Rec_Num_Ok = 0;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 11, 177);

esp_err_t event_handler(void* ctx, system_event_t* event) {
  return ESP_OK;
}

Buffer sdBuffer;
Preferences preferences;

bool useSD = false;
bool buttonEnabled = true;
uint32_t lastDrawTime;
uint32_t lastButtonTime;
uint32_t tmpPacketCounter;
uint32_t pkts[MAX_X];       // here the packets per second will be saved
uint32_t deauths = 0;       // deauth frames per second
unsigned int ch = 1;        // current 802.11 channel
int rssiSum;

//setup
void setup() {

  //Initialize
  Serial.begin(115200);
  m5.begin();
  Wire.begin();

  SPI.begin(SCK, MISO, MOSI, -1);
  Ethernet.init(CS);
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  if (digitalRead(BUTTON_A_PIN) == 0) {
    Serial.println("Will Load menu binary");
    updateFromFS(SD, "/menu.bin");
    ESP.restart();
  }
    home();

  //Settings
  preferences.begin("packetmonitor32", false);
  preferences.end();

  // System & WiFi
  nvs_flash_init();
  tcpip_adapter_init();
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  //ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));
  //ESP_ERROR_CHECK(esp_wifi_init(&cfg));
  //ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
  //ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_NULL));
  //ESP_ERROR_CHECK(esp_wifi_start());

  esp_wifi_set_channel(ch, WIFI_SECOND_CHAN_NONE);

#ifdef USE_SD
  // SD card
  sdBuffer = Buffer();

  if (setupSD())
    sdBuffer.open(&SD_MMC);

  // I/O
  pinMode(BUTTON_PIN, INPUT_PULLUP);
#endif

  lcd_clear();

  // second core
  xTaskCreatePinnedToCore(
    coreTask,               /* Function to implement the task */
    "coreTask",             /* Name of the task */
    2500,                   /* Stack size in words */
    NULL,                   /* Task input parameter */
    0,                      /* Priority of the task */
    NULL,                   /* Task handle. */
    RUNNING_CORE);          /* Core where the task should run */

  // start Wifi sniffer
  esp_wifi_set_promiscuous_rx_cb(&wifi_promiscuous);
  esp_wifi_set_promiscuous(true);

}

//ループ処理
void loop() {
  vTaskDelay(portMAX_DELAY);
}
