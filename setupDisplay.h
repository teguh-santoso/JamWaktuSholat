#include <DMDESP.h>
#include <fonts/EMKotak5x7.h>
#include <fonts/ElektronMart6x8.h>

// Inisiasi pin untuk modul P10
#define FontDefault EMKotak5x7
#define FontJalan ElektronMart6x8

// DMDESP Setup
#define DISPLAYS_WIDE 1 // Kolom Panel
#define DISPLAYS_HIGH 1 // Baris Panel
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH); // Jumlah Panel P10 yang digunakan (KOLOM, BARIS)

void setupDMDESP(){
   // DMDESP
   Disp.start(); // Jalankan library DMDESP
   Disp.setBrightness(1); // Tingkat kecerahan
   Disp.setFont(FontDefault); // Huruf default
}

void TeksJalan(int y, uint8_t kecepatan) {
  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
  Disp.setFont(FontJalan);
  int fullScroll = Disp.textWidth(teks.c_str()) + width;
  if ((millis() - pM) > kecepatan) {
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      return;
    }
    Disp.drawText(width - x, y, teks.c_str());
  }
}
