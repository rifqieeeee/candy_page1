#include <Keypad.h>

String inputString = ""; // Variabel untuk menyimpan input
bool inputStarted = false;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {D0, D1, D2, D3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {D4, D5, D6, D7}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char key = customKeypad.getKey();
  
  if (key) {
    if (key == '*') {
      inputString = ""; // Reset input jika tombol '*' ditekan
      inputStarted = true;
    } else if (key == 'A') {
      if (inputStarted) {
        Serial.print("Input Data: ");
        Serial.println(inputString);
        inputString = ""; // Reset input setelah mencetak
        inputStarted = false;
      }
    } else if (key == 'B') {
      if (inputStarted && inputString.length() > 0) {
        // Hapus satu karakter terakhir jika input sudah dimulai
        inputString = inputString.substring(0, inputString.length() - 1);
        Serial.print("Input Sementara: ");
        Serial.println(inputString);
      }
    } else if (inputStarted) {
      inputString += key; // Tambahkan karakter ke input
      Serial.print("Input Sementara: ");
      Serial.println(inputString);
    }
  }
}
