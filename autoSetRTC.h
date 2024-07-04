// Berfungsi untuk mengatur waktu RTC dengan waktu dari server NTP
// Untuk melakukan sinkronisasi, silakan buat hotspot di smartphone :
// nama SSID = admin1234
// password  = admin1234
// lalu restart.

#include <virtuabotixRTC.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define PIN_CLK 5 // D1
#define PIN_DAT 4 // D2
#define PIN_RST 2 // D4
virtuabotixRTC timeRTC(PIN_CLK, PIN_DAT, PIN_RST);

// Koneksi Wi-Fi
const char *ssid     = "admin1234";
const char *password = "admin1234";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setupRTC(){
   // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  int wifi_attempts = 0;
  const int max_attempts = 20; // Batasan percobaan koneksi WiFi
  while (WiFi.status() != WL_CONNECTED && wifi_attempts < max_attempts) {
    delay(500);
    Serial.print(".");
    wifi_attempts++;
  }

  delay(3000);
  
  if (WiFi.status() == WL_CONNECTED){
    timeClient.begin();
    timeClient.setTimeOffset(25200);
    timeClient.update();
    int currentSecond = timeClient.getSeconds();
    int currentMinute = timeClient.getMinutes();
    int currentHour = timeClient.getHours();
    int weekDay = timeClient.getDay();
    //Get a time structure
    time_t epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime ((time_t *)&epochTime);
    int monthDay = ptm->tm_mday;
    int currentMonth = ptm->tm_mon+1;
    int currentYear = ptm->tm_year+1900;
  
    // Set RTC secara manual
    // Format: (seconds, minutes, hours, day of the week, day of the month, month, year)
    // Ubah sesuai dengan waktu yang diinginkan
  
    // Perbarui waktu otomatis  
    timeRTC.setDS1302Time(currentSecond, currentMinute, currentHour, weekDay, monthDay, currentMonth, currentYear);
  } else {
    Serial.println("Disconnected");
  }
}
