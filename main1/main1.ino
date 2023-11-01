#include <Keypad.h>
#include <TFT_eSPI.h>
#include <Seeed_FS.h> // Including SD card library
# include"RawImage.h"  //Including image processing library

TFT_eSPI tft;
TFT_eSprite spr = TFT_eSprite(&tft);  //sprite

String inputString = ""; // Variabel untuk menyimpan input
bool inputStarted = false;
bool standbyMode = true;
bool useridMode = false;
bool bookidMode = false;
bool onebook = false;
bool twobook = false;
bool threebook = false;
String userid;
String bookid;

// Daftar buku dan user
int buku[] = {1111, 1112, 1113, 1114, 1115};
int user[] = {5551, 5552, 5553, 5554, 5555};

// Status buku yang sudah dibaca oleh setiap user
bool statusBaca[5][5] = {false}; // Inisialisasi dengan semua buku belum dibaca

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
// Define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {D0, D1, D2, D3}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {D4, D5, D6, D7}; // Connect to the column pinouts of the keypad

// Initialize an instance of class Keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);

  if(!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)) {
    while (1);
  }
  tft.begin();
  tft.setRotation(3);
  drawImage<uint16_t>("home.bmp", 0, 0);
}
  
void loop() {
  char key = customKeypad.getKey();

  if (key) {
    if (standbyMode) {
      drawImage<uint16_t>("home.bmp", 0, 0);
      if (key == '*') {
        drawImage<uint16_t>("userid.bmp", 0, 0);

        spr.createSprite(200, 50);
        spr.fillSprite(TFT_WHITE);
        spr.drawString(inputString, 5, 0, 2);
        spr.pushSprite(60, 120);
        spr.deleteSprite();

        standbyMode = false;
        inputString = "";
        inputStarted = true;
        useridMode = true;
      }
    } else if (useridMode) {
      if (key == 'A') {
        drawImage<uint16_t>("bookid.bmp", 0, 0);
        userid = inputString;
        inputString = "";
        inputStarted = true;
        useridMode = false;
        bookidMode = true;
      } else if (key == 'B' && inputString.length() > 0) {
        inputString = inputString.substring(0, inputString.length() - 1);
        Serial.print("Input UserID: ");
        Serial.println(inputString);

        spr.createSprite(200, 50);
        spr.fillSprite(TFT_WHITE);
        spr.drawString(inputString, 5, 0, 2);
        spr.pushSprite(60, 120);
        spr.deleteSprite();
      } else if (inputStarted) {
        inputString += key;
        Serial.print("Input UserID: ");
        Serial.println(inputString);

        spr.createSprite(200, 50);
        spr.fillSprite(TFT_WHITE);
        spr.drawString(inputString, 5, 0, 2);
        spr.pushSprite(60, 120);
        spr.deleteSprite();
      }
    } else if (bookidMode) {
      if (key == 'A') {
        bookid = inputString;
        // Proses userid dan bookid di sini
        // Misalnya, print ke Serial Monitor
        Serial.print("User ID: ");
        Serial.println(userid);
        Serial.print("Book ID: ");
        Serial.println(bookid);

        inputString = "";
        inputStarted = false;  // Reset inputStarted to false
        useridMode = false;
        bookidMode = false;
        standbyMode = true;  // Reset to standby mode here
      } else if (key == 'B' && inputString.length() > 0) {
        inputString = inputString.substring(0, inputString.length() - 1);
        Serial.print("Input BookID: ");
        Serial.println(inputString);

        spr.createSprite(200, 50);
        spr.fillSprite(TFT_WHITE);
        spr.drawString(inputString, 5, 0, 2);
        spr.pushSprite(60, 120);
        spr.deleteSprite();
      } else if (inputStarted) {
        inputString += key;
        Serial.print("Input BookID: ");
        Serial.println(inputString);

        spr.createSprite(200, 50);
        spr.fillSprite(TFT_WHITE);
        spr.drawString(inputString, 5, 0, 2);
        spr.pushSprite(60, 120);
        spr.deleteSprite();
      }
    }
  }
}


