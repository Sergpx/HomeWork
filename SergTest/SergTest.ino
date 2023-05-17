#include <SPI.h>
#include <RFID.h>
 
#define SS_PIN 10
#define RST_PIN 9
 
RFID rfid(SS_PIN, RST_PIN); 
 
int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;

void addCard(int**& cards, int* card, int size){
    int size = _msize(cards) / sizeof(cards[0]);
    int** buf = new int[size + 1];
    for (int i = 0; i < size; i++){
      buf[i] = cards[i];
      }
    buf[size] = card;
  }

void delCard(int**& cards, int index, int size){
    int size = _msize(cards) / sizeof(cards[0]);
    int** buf = new int[size - 1];
    for (int i = 0; i < index; i++){
      buf[i] = cards[i];
      }
    for (int i = index + 1; i < size; i++){
      buf[i-1] = cards[i];
      }
  }
 
void setup()
{ 
  Serial.begin(9600);
  SPI.begin(); 
  rfid.init();
  int** = cards[0];
}
 
void loop()
{
    // Если обнаружена карта
    if (rfid.isCard()) {
        // Считываем адрес
        if (rfid.readCardSerial()){
          int size = sizeof(cards) / sizeof(cards[0]);
          for (int j = 0, flag; j < size; j++){
            flag = true;
            for (int i = 0; i < 5; i++){
              if (cards[i] != rfid.serNum[i]){
                flag = false;
              }
            }
            if (flag == true){
              int size = sizeof(cards) / sizeof(cards[0]);
              Serial.println((millis() - cards[i][5]) / 1000);
              delCard(cards, j, size);
              break;
              }
            else{
              int size = sizeof(cards) / sizeof(cards[0]);
              int* card = new int[6]{rfid.serNum[0], rfid.serNum[1], rfid.serNum[2], rfid.serNum[3], rfid.serNum[4]), millis()};
              addCard(cards, card, size);
              }
          }
        }   
    }
    rfid.halt();
    delay(1000);
}
