#include <SPI.h>
#include <MFRC522.h>
#include <MD_MAX72xx.h>



//DOT Matrix Setup
#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

#define MAX_DEVICES 1
#define CS_PIN 6
#define  DELAYTIME  50
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


// //RFID Scanner Setup
// #define RST_PIN         5          // Configurable, see typical pin layout above
// #define SS_PIN          7         // Configurable, see typical pin layout above
// MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

//Limit swith
#define button 5
int buttonState = 1;

byte readCard[4];
const char* rfidTags[] = {"931D7CD", "492561", "4A23E1","451421"};
int tagPoints[] = {1,2,3,4};
String tagID = "";
int points = 0;



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus

  pinMode(button, INPUT_PULLUP);


	// mfrc522.PCD_Init();		// Init MFRC522
	//delay(4);	
	// mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 0);
  mx.clear();
  Serial.println("Scan Card");

}

void loop() {
  while(digitalRead(button));
  
  points = points + 2;

  Serial.print("Total POINTS: ");
  Serial.println(points);


  if (points >= 8) {
    Serial.println("WINNNER");
      
    win();
      

  } else {
    for(int i = 0; i < (points); i++) {
  
      //mx.setRow(i,0xff);
      mx.setColumn(i,0xff);
      delay(DELAYTIME);

    }

  }




}




void win() {
  points = 0;

  for (int i = 0; i < 3; i++) {
    int  rmin = 0, rmax = ROW_SIZE-1;
    int  cmin = 0, cmax = (COL_SIZE*MAX_DEVICES)-1;

    mx.clear();
    while ((rmax > rmin) && (cmax > cmin))
    {
      // do row
      for (int i=cmin; i<=cmax; i++)
      {
        mx.setPoint(rmin, i, true);
        delay(DELAYTIME/MAX_DEVICES);
      }
      rmin++;

      // do column
      for (uint8_t i=rmin; i<=rmax; i++)
      {
        mx.setPoint(i, cmax, true);
        delay(DELAYTIME/MAX_DEVICES);
      }
      cmax--;

      // do row
      for (int i=cmax; i>=cmin; i--)
      {
        mx.setPoint(rmax, i, true);
        delay(DELAYTIME/MAX_DEVICES);
      }
      rmax--;

      // do column
      for (uint8_t i=rmax; i>=rmin; i--)
      {
        mx.setPoint(i, cmin, true);
        delay(DELAYTIME/MAX_DEVICES);
      }
      cmin++;
    }
  }
  
  mx.clear();
}