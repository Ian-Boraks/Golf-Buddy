#include <SPI.h>
#include <MFRC522.h>
#include <MD_MAX72xx.h>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

// DOT Matrix Setup
#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

#define MAX_DEVICES 1
#define CS_PIN 6
#define DELAYTIME 50
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// //RFID Scanner Setup
// #define RST_PIN         5          // Configurable, see typical pin layout above
// #define SS_PIN          7         // Configurable, see typical pin layout above
// MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// Limit swith
#define button 5
int buttonState = 1;

#define mic 7
int hits = 0;

bool gameOver = false;
bool player = true;

int playerOnePoints = 0;
int playerTwoPoints = 0;

byte readCard[4];
const char *rfidTags[] = {"931D7CD", "492561", "4A23E1", "451421"};
int tagPoints[] = {1, 2, 3, 4};
String tagID = "";
int points = 0;

void setup()
{
  // put your setup code here, to run once:

  // Serial.begin(9600); // Initialize serial communications with the PC
  // while (!Serial)
  // ;          // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin(); // Init SPI bus

  pinMode(button, INPUT_PULLUP);
  pinMode(mic, INPUT);

  // mfrc522.PCD_Init();		// Init MFRC522
  // delay(4);
  // mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 0);
  mx.clear();
  Serial.println("Scan Card");
}

void updatePoints()
{
  for (int i = 0; i < min(points, 8); i++)
  {
    mx.setColumn(i, 0xf0);
    delay(DELAYTIME);
  }

  for (int i = points - 8; i < min(points, 16); i++)
  {
    mx.setColumn(i - 8, 0xff);
    delay(DELAYTIME);
  }
}

void loop()
{
  gameOver = false;
  hits = 0;
  points = 0;

  if (player)
  {
    displayNumberOne();
  }
  else
  {
    displayNumberTwo();
  }

  delay(5000);
  dissolve();

  while (digitalRead(button))
  {
    int sound = analogRead(mic);
    if (sound < 20)
    {
      hits++;
      delay(500);
      Serial.print("HIT: ");
      Serial.println(sound);

      points++;

      updatePoints();
    }

    if (hits >= 16)
    {
      break;
    }
  }

  Serial.println(hits);
  delay(500);

  Serial.print("Total POINTS: ");
  Serial.println(points);

  if (player)
  {
    playerOnePoints += points;
  }
  else
  {
    playerTwoPoints += points;
  }

  if (points < 16)
  {
    win();
  }
  else
  {
    dissolve();
  }

  if (!player)
  {
    Serial.print("Player 1: ");
    Serial.println(playerOnePoints);
    Serial.print("Player 2: ");
    Serial.println(playerTwoPoints);

    if (playerOnePoints < playerTwoPoints)
    {
      // Blink player 1
      for (int i = 0; i < 3; i++)
      {
        displayNumberOne();
        delay(500);
        mx.clear();
        delay(500);
      }
    }
    else if (playerOnePoints > playerTwoPoints)
    {
      // Blink player 2
      for (int i = 0; i < 3; i++)
      {
        displayNumberTwo();
        delay(500);
        mx.clear();
        delay(500);
      }
    }
    else
    {
      // Blink both
      for (int i = 0; i < 3; i++)
      {
        displayNumberOne();
        delay(500);
        mx.clear();
        delay(500);

        displayNumberTwo();
        delay(500);
        mx.clear();
        delay(500);
      }
    }

    playerOnePoints = 0;
    playerTwoPoints = 0;
  }

  player = !player;
}

void win()
{
  points = 0;

  int rmin = 0, rmax = ROW_SIZE - 1;
  int cmin = 0, cmax = (COL_SIZE * MAX_DEVICES) - 1;

  mx.clear();
  while ((rmax > rmin) && (cmax > cmin))
  {
    // do row
    for (int i = cmin; i <= cmax; i++)
    {
      mx.setPoint(rmin, i, true);
      delay(DELAYTIME / MAX_DEVICES);
    }
    rmin++;

    // do column
    for (uint8_t i = rmin; i <= rmax; i++)
    {
      mx.setPoint(i, cmax, true);
      delay(DELAYTIME / MAX_DEVICES);
    }
    cmax--;

    // do row
    for (int i = cmax; i >= cmin; i--)
    {
      mx.setPoint(rmax, i, true);
      delay(DELAYTIME / MAX_DEVICES);
    }
    rmax--;

    // do column
    for (uint8_t i = rmax; i >= rmin; i--)
    {
      mx.setPoint(i, cmin, true);
      delay(DELAYTIME / MAX_DEVICES);
    }
    cmin++;
  }

  mx.clear();
}

// Function to update the display based on the matrix state
void updateDisplay(bool matrix[][COL_SIZE])
{
  for (int r = 0; r < ROW_SIZE; r++)
  {
    for (int c = 0; c < COL_SIZE; c++)
    {
      mx.setPoint(r, c, matrix[r][c]);
    }
  }
}

void dissolve()
{
  // Assuming ROW_SIZE and COL_SIZE are defined elsewhere
  bool matrix[ROW_SIZE][COL_SIZE];

  // Initialize all points to true (on)
  for (int r = 0; r < ROW_SIZE; r++)
  {
    for (int c = 0; c < COL_SIZE; c++)
    {
      matrix[r][c] = true;
    }
  }

  // Update the display with the initial state
  updateDisplay(matrix);

  // Total number of points
  int totalPoints = ROW_SIZE * COL_SIZE;
  srand(time(NULL)); // Seed for random number generation

  while (totalPoints > 0)
  {
    // Generate a random row and column
    int r = rand() % ROW_SIZE;
    int c = rand() % COL_SIZE;

    // If the point is already off, continue
    if (!matrix[r][c])
      continue;

    // Turn off the point
    matrix[r][c] = false;
    totalPoints--;

    // Update the display
    updateDisplay(matrix);

    // Delay to visualize the effect
    delay(DELAYTIME);
  }
}

void displayNumberOne()
{
  bool numberOne[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0},
                          {1, 0, 0, 0, 0, 0, 0, 0},
                          {1, 0, 0, 0, 0, 0, 0, 0},
                          {1, 1, 1, 1, 1, 1, 1, 1},
                          {1, 0, 0, 0, 0, 0, 1, 0},
                          {0, 0, 0, 0, 0, 1, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0}};

  mx.clear(); // Clear the matrix
  updateDisplay(numberOne);
}

void displayNumberTwo()
{
  bool numberTwo[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 1, 0, 0, 1, 1, 1, 1},
                          {0, 1, 0, 0, 1, 0, 0, 1},
                          {0, 1, 0, 0, 1, 0, 0, 1},
                          {0, 1, 0, 0, 1, 0, 0, 1},
                          {0, 1, 0, 0, 1, 0, 0, 1},
                          {0, 1, 1, 1, 1, 0, 0, 1},
                          {0, 0, 0, 0, 0, 0, 0, 0}};

  mx.clear(); // Clear the matrix
  updateDisplay(numberTwo);
}