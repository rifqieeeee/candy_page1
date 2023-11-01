# include"TFT_eSPI.h"
# include "Seeed_FS.h" //Including SD card library
# include"RawImage.h"  //Including image processing library
TFT_eSPI tft;

void setup() {
    //Initialise SD card
    if(!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)) {
        while (1);
    }
    tft.begin();
    tft.setRotation(3);

}

void loop() {
  drawImage<uint16_t>("For Wio.bmp", 0, 0); //Display this 8-bit image in sd card from (0, 0)
  delay(1500);
  
}
