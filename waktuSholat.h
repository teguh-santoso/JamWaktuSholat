#include <stdio.h>
#include <Wire.h>
#include <TimeLib.h>
#include <PrayerTimes.h>

// Teks yang akan ditampilkan
String teks = "WAKTU SHOLAT BELUM DISET";

//penambahan dan pengurangan waktu ihtiyat. 
//mohon sesuaikan dengan waktu ikhtiyat yang berlaku di daerah Anda
int addSubuh  = 2;
int addDhuhur = 3;
int addAshar  = 2;
int addMagrib = 4;
int addIsyak  = 2;

// waktu sholat
double times[sizeof(TimeName)/sizeof(char*)];
void displayPrayerTimes() {
  timeRTC.updateTime();
  Serial.println("Waktu Sholat untuk Ponorogo, Indonesia:"+timeRTC.dayofmonth);
    
  int dst = 7; 
    
  set_calc_method(Karachi);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(20);
  set_isha_angle(18);
    
  // Koordinat untuk Ponorogo, Indonesia
  //String latitude = "-7.8297";
  //String longitude = "111.4957";
    
  get_prayer_times(timeRTC.year, timeRTC.month, timeRTC.dayofmonth, -7.8666f, 111.4666f, dst, times);
  //get_prayer_times(timeRTC.year, timeRTC.month, 3, -7.8666f, 111.4666f, dst, times);  
    
  int hours, minutes;
  char tmp[10];
  String subuh, dhuhur, asyar, magrib, isyak;

  // Imsak
  //get_float_time_parts(times[0], hours, minutes);
  //imsak = (hours < 10 ? "0" : "") + String(hours) + ":" + (minutes < 10 ? "0" : "") + String(minutes);

  // Subuh
  get_float_time_parts(times[0], hours, minutes);
  minutes += addSubuh;
  // Jika menit lebih dari 59, tambahkan ke jam dan kurangi dari menit
  if (minutes >= 60) {
      hours += minutes / 60;
      minutes %= 60;
  }
  // Jika jam lebih dari 23, kembali ke 0
  if (hours >= 24) {
      hours %= 24;
  }
  subuh = (hours < 10 ? "0" : "") + String(hours) + ":" + (minutes < 10 ? "0" : "") + String(minutes);

  // Dhuhr
  get_float_time_parts(times[2], hours, minutes);
  minutes += addDhuhur;
  // Jika menit lebih dari 59, tambahkan ke jam dan kurangi dari menit
  if (minutes >= 60) {
      hours += minutes / 60;
      minutes %= 60;
  }
  // Jika jam lebih dari 23, kembali ke 0
  if (hours >= 24) {
      hours %= 24;
  }
  dhuhur = (hours < 10 ? "0" : "") + String(hours) + ":" + (minutes < 10 ? "0" : "") + String(minutes);

  // Asr
  get_float_time_parts(times[3], hours, minutes);
  minutes += addAshar;
  // Jika menit lebih dari 59, tambahkan ke jam dan kurangi dari menit
  if (minutes >= 60) {
      hours += minutes / 60;
      minutes %= 60;
  }
  // Jika jam lebih dari 23, kembali ke 0
  if (hours >= 24) {
      hours %= 24;
  }
  asyar = (hours < 10 ? "0" : "") + String(hours) + ":" + (minutes < 10 ? "0" : "") + String(minutes);

  // Maghrib
  get_float_time_parts(times[5], hours, minutes);
  minutes += addMagrib;
  // Jika menit lebih dari 59, tambahkan ke jam dan kurangi dari menit
  if (minutes >= 60) {
      hours += minutes / 60;
      minutes %= 60;
  }
  // Jika jam lebih dari 23, kembali ke 0
  if (hours >= 24) {
      hours %= 24;
  }
  magrib = (hours < 10 ? "0" : "") + String(hours) + ":" + (minutes < 10 ? "0" : "") + String(minutes);

  // Isha
  get_float_time_parts(times[6], hours, minutes);
  minutes += addIsyak;
  // Jika menit lebih dari 59, tambahkan ke jam dan kurangi dari menit
  if (minutes >= 60) {
      hours += minutes / 60;
      minutes %= 60;
  }
  // Jika jam lebih dari 23, kembali ke 0
  if (hours >= 24) {
      hours %= 24;
  }
  isyak = (hours < 10 ? "0" : "") + String(hours) + ":" + (minutes < 10 ? "0" : "") + String(minutes);

  // Ubah teks
  teks = "SUBUH " + subuh + " WIB - DHUHUR " + dhuhur + " WIB - ASYAR " + asyar + " WIB - MAGHRIB " + magrib + " WIB - ISYAK " + isyak + " WIB";
  Serial.println(teks+timeRTC.month);
}
