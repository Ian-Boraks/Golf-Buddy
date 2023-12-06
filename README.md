- [Overview](#overview)
  - [Project Photos](#project-photos)
    - [Launcher](#launcher)
    - [Hole](#hole)
- [Hardware](#hardware)
  - [BOM](#bom)
  - [CAD](#cad)
    - [Laser Cut Parts](#laser-cut-parts)
  - [Electronics](#electronics)
    - [Wiring Diagram Launcher](#wiring-diagram-launcher)
    - [Wiring Diagram Hole](#wiring-diagram-hole)
- [Development](#development)
  - [RFID](#rfid)
    - [Code Snippets](#code-snippets)
  - [Launcher](#launcher-1)
    - [Code Snippets](#code-snippets-1)
  - [Hole](#hole-1)
    - [Code Snippets](#code-snippets-2)
- [Skills Beyond](#skills-beyond)
  - [Fernando](#fernando)
  - [Ian](#ian)

---

![Golf Buddy](/images/GolfDaddy.png)

[Demo Video (https://youtu.be/wagic4B7uYY)](https://youtu.be/wagic4B7uYY)

# Overview

Welcome to the project documentation for an innovative addition to the world of mini golf: a High-Speed Golf Ball Shooter. This project began with a simple yet ambitious goal: to enhance the traditional golfing experience, particularly in the realm of putting. Our initial vision was to develop a tool that would assist golfers in refining their putting skills in a competitive and engaging manner. However, as we delved deeper into the project, our focus shifted, leading us to a more dynamic and playful interpretation of golfing aids.

**Main Reasons for Project Shift:**

1. Our motor was too powerful for the golf ball. We were unable to tune the motor speed too produce reasonable ball speeds.
2. Our RFID reader was unable to read the RFID tags on the golf balls. We were unable to find a solution to this problem that would be cost feasible with our limited budget.
3. The ball return mechanism was too complex for our limited time frame.

## Project Photos

### Launcher

\
<img src="/images/product_photos/PXL_20231204_000930088.jpg" width="300" height="300">
<img src="/images/product_photos/PXL_20231204_000943244.jpg" width="300" height="300">

### Hole

\
<img src="/images/product_photos/PXL_20231204_000956457.jpg" width="300" height="300">
<img src="/images/product_photos/PXL_20231204_001002481.jpg" width="300" height="300">

# Hardware

## BOM

| Part             | Quantity | Price  |
| ---------------- | -------- | ------ |
| Seeduino Xiao    | 2        | $5.90  |
| NeoPixel Matrix  | 2        | $9.95  |
| 6s LiPo Battery  | 1        | $30.00 |
| ESC SpeedyBee    | 1        | $60.00 |
| Bearings         | 4        | $10.00 |
| 3D Printed Parts | 1        | ~~~    |
| Limit Switch     | 2        | $5.00  |
| Switches         | 2        | $5.00  |
| Microphone       | 1        | $5.00  |

## CAD

**Launcher**: \
<img src="/images/cad/Full%20Laucnher.png" width="300" height="300">
<img src="/images/cad/Feeder%20Tube.png" width="300" height="300">

### Laser Cut Parts

**Hole Plate**: \
<img src="/images/cad/Plate.png" height="300">

## Electronics

### Wiring Diagram Launcher

![Wiring Diagram](/Electrical/Launcher/Schematic.png)

### Wiring Diagram Hole

![Wiring Diagram](/Electrical/Hole/Schematic.png)

# Development

## RFID

The original idea was to use the RFID tags embedded into the balls to read the player's score. Initial testing with the RFID was positive, as it could read different tags with different point values and add them. \
<img src="/images/IMG_2636.jpg" width="300" height="300">
<img src="/images/IMG_2637.jpg" width="300" height="300">

However, the issue arose during integration with the golf balls. The RFID was not strong enough to travel through the golf ball to get consistent readings. The issue only worsened with the launcher integration because the ball traveled too fast to be read. The RFID hardware needed to be changed with something that could be more reliable and work at faster speeds. The change to limit swithces proved to be very reliable and work on any speed we tested because of the simplicity of the tech. The lessoned learned was to not overcomplicate things sometimes instead of trying to make a golf ball smart just add a simple button. \
<img src="/images/IMG_2627.JPG" width="300" height="300">

### Code Snippets

Even though RFID didn't get implemented into the final design. A lot of effort went into the development of the RFID tracking system.

```cpp
#include <SPI.h>
#include <MFRC522.h>

//RFID Scanner Setup
#define RST_PIN         5           // Configurable, see typical pin layout above
#define SS_PIN          7           // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

byte readCard[4];
const char *rfidTags[] = {"931D7CD", "492561", "4A23E1", "451421"};
int tagPoints[] = {1, 2, 3, 4};
String tagID = "";
int points = 0;

void setup() {
    mfrc522.PCD_Init();		            // Init MFRC522
    delay(4);
    mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
}

// TODO: Add the rest of the code needed for RFID also add in some more photos if you have them
```

---

## Launcher

The original design of the launcher was a tube that would need an additional feeder tube to function. The issue with this design was that the ball would get stuck in the feeder tube and not be able to be launched. The solution was to change the design to a single tube that would be able to launch the ball without the need of a feeder tube.

**Launcher Initial Design**: \
<img src="/images/cad/Inital%20Concept.png" height=300>

**Launcher Final Design**: \
<img src="/images/cad/Full%20Laucnher.png" height=300>

However, this design didn't allow enough balls to be loaded in and our project changed to a single ball launcher. At this point, we decided to completely pivot from a putting assistant to a fun golf ball launcher. The lesson learned was to not be afraid to change the design if it doesn't work.

The final pivot point was the addition of a miss counter. This is done via a mic on the back of the device that can track if the user misses. This allows us to re-gamify the system and add a competitive aspect to the game.

### Code Snippets

**ESC Arming**:

The most difficult part of the launcher code was the arming of the ESC. This required us to go through the BLHELI_32 documentation and codebase to figure out the specific commands to send to the ESC. The code below is the final code that we used to arm the ESC.\
<img src="/images/ESC-ARM.png" height=300>

```c++
Motor.attach(0);

delay(100);

Motor.writeMicroseconds(0);
delayMicroseconds(400);
Motor.writeMicroseconds(1800);
delayMicroseconds(500);
Motor.writeMicroseconds(1000);
```

---

## Hole

<img src="/images/product_photos/PXL_20231204_000956457.jpg" width="300" height="300">

### Code Snippets

**Pixel Matrix**: \
The pixel matrix output is done via two ways.

1. Manually setting each row / col.
   1. The `win()` and `updatePoints()` functions use this method.
2. Using a custom `updateDisplay()` function.
   1. Other functions like `dissolve()`, `displayNumberOne()`, and `displayNumberTwo()` all use this update function.

The `updateDisplay()` function is as follows:

```cpp
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
```

**Score Tracking (Microphone)**: \
Below is the code used to detect if the player missed their shot. It is a simple system that pulls the microphone to see if it drop below its volume threshold.

```c++
#define VOLUME_THRESHOLD 20
while (digitalRead(button))
  {
    int sound = analogRead(mic);
    if (sound < VOLUME_THRESHOLD)
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
```

# Skills Beyond

## Fernando

- Laser cutting metal using the fablight in The Hive
- Programming on a Seeed Studio XIAO SAMD21 mircocontroller
- Using multiple SPI devices

## Ian

- Laser cutting metal using the fablight in The Hive
- Doing manual brushless motor control
- Sublimation printing

<!--
# Special Thanks

We would like to thank the following people for their contributions to this project:

Our ambassador and visionary, Golf Daddy:

<img src="/images/ambassador.jpg" width=300 height=300>

Golf Daddy helped us and supported us through the initial stages of this project. He provided us with the inspiration and motivation to pursue this project, and we are forever grateful for his guidance. But in all seriousness, he did help bring our spirits up by playing guitar during our long nights at the HIVE.
-->
