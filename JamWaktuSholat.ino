#include "autoSetRTC.h"
#include "waktuSholat.h"
#include "setupDisplay.h"

void setup() {
  Serial.begin(9600);
  setupRTC();
  setupDMDESP();
  displayPrayerTimes();
}

void loop() {
  // Update waktu RTC
  timeRTC.updateTime();

  // Ubah format jam menjadi dua digit
  String jam, menit, detik, waktu, waktuserial;
  if (timeRTC.hours < 10) {
    jam = "0" + String(timeRTC.hours);
  } else {
    jam = String(timeRTC.hours);
  }
  
  // Ubah format menit menjadi dua digit
  if (timeRTC.minutes < 10) {
    menit = "0" + String(timeRTC.minutes);
  } else {
    menit = String(timeRTC.minutes);
  }

  // Ubah format menit menjadi dua digit
  if (timeRTC.seconds < 10) {
    detik = "0" + String(timeRTC.seconds);
  } else {
    detik = String(timeRTC.seconds);
  }
  

  // Tampilkan waktu di display
  waktu = jam + ":" + menit;
  Disp.setFont(FontDefault);
  Disp.drawText(3, 0, waktu);

  // TextJalan
  TeksJalan(9, 50);

  Disp.loop();

  int currentHours = timeRTC.hours;
  int currentMinutes = timeRTC.minutes;
  int currentSeconds = timeRTC.seconds;

  if (currentHours == 1 && currentMinutes == 0 && currentSeconds == 0) {
      displayPrayerTimes();
      delay(1000); // Hindari menjalankan fungsi lebih dari sekali dalam satu detik
  }

}
