# Golf Buddy

![Golf Buddy](/images/GolfDaddy.png)

[Demo Video (https://youtu.be/wagic4B7uYY)](https://youtu.be/wagic4B7uYY)

## Overview

Welcome to the project documentation for an innovative addition to the world of mini golf: a High-Speed Golf Ball Shooter. This project began with a simple yet ambitious goal: to enhance the traditional golfing experience, particularly in the realm of putting. Our initial vision was to develop a tool that would assist golfers in refining their putting skills in a competitive and engaging manner. However, as we delved deeper into the project, our focus shifted, leading us to a more dynamic and playful interpretation of golfing aids.

**Main Reasons for Project Shift:**

1. Our motor was too powerful for the golf ball. We were unable to tune the motor speed too produce reasonable ball speeds.
2. Our RFID reader was unable to read the RFID tags on the golf balls. We were unable to find a solution to this problem that would be cost feasible with our limited budget.

## Project Photos

### Launcher

\
<img src="/images/product_photos/PXL_20231204_000930088.jpg" width="300" height="300">
<img src="/images/product_photos/PXL_20231204_000943244.jpg" width="300" height="300">

### Hole

\
<img src="/images/product_photos/PXL_20231204_000956457.jpg" width="300" height="300">
<img src="/images/product_photos/PXL_20231204_001002481.jpg" width="300" height="300">

## Hardware

### BOM

| Part             | Quantity | Price  | Link                                                                                          |
| ---------------- | -------- | ------ | --------------------------------------------------------------------------------------------- |
| Seeduino Xiao    | 2        | $5.90  | https://www.seeedstudio.com/Seeeduino-XIAO-p-4878.html                                        |
| NeoPixel Matrix  | 2        | $9.95  | https://www.adafruit.com/product/1487                                                         |
| 6s LiPo Battery  | 1        | $30.00 | https://www.getfpv.com/cnhl-black-series-100c-6s-lipo-battery-1300mah.html                    |
| ESC SpeedyBee    | 1        | $60.00 | https://www.speedybee.com/speedybee-f7-v3-bl32-50a-4-in-1-esc/                                |
| Bearings         | 4        | $10.00 | https://www.amazon.com/gp/product/B07Q2ZQY2L/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1 |
| 3D Printed Parts | 1        | ~~~    | ~~~                                                                                           |
| Limit Switch     | 2        | $5.00  | https://www.amazon.com/gp/product/B07Q2ZQY2L/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1 |
| Switches         | 2        | $5.00  | https://www.amazon.com/gp/product/B07Q2ZQY2L/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1 |

### CAD

**Launcher**: \
<img src="/images/cad/Full%20Laucnher.png" width="300" height="300">
<img src="/images/cad/Feeder%20Tube.png" width="300" height="300">

### Laser Cut Parts

**Hole Plate**: \
<img src="/images/cad/Plate.png" width="300" height="300">

## Electronics

### Wiring Diagram Launcher

![Wiring Diagram](/Electrical/Launcher/Schematic.png)

### Wiring Diagram Hole

![Wiring Diagram](/Electrical/Hole/Schematic.png)

## Testing

### RFID

The original idea was to use the RFID tags embedded into the balls to read the player's score. Initial testing with the RFID was positive, as it could read different tags with different point values and add them. \
<img src="/images/IMG_2636.jpg" width="300" height="300">
<img src="/images/IMG_2637.jpg" width="300" height="300">

However, the issue arose during integration with the golf balls. The RFID was not strong enough to travel through the golf ball to get consistent readings. The issue only worsened with the launcher integration because the ball traveled too fast to be read. The RFID hardware needed to be changed with something that could be more reliable and work at faster speeds. The change to limit swithces proved to be very reliable and work on any speed we tested because of the simplicity of the tech. The lessoned learned was to not overcomplicate things sometimes instead of trying to make a golf ball smart just add a simple button. \
<img src="/images/IMG_2627.JPG" width="300" height="300">

### Launcher

The original design of the launcher was a tube that would need an additional feeder tube to function. The issue with this design was that the ball would get stuck in the feeder tube and not be able to be launched. The solution was to change the design to a single tube that would be able to launch the ball without the need of a feeder tube.

**Hole Initial Design**: \
<img src="/images/cad/Inital%20Concept.png" height=300>

**Hole Final Design**: \
<img src="/images/cad/Full%20Laucnher.png" height=300>

However, this design didn't allow enough balls to be loaded in and our project changed to a single ball launcher. At this point, we decided to completely pivot from a putting assistant to a fun golf ball launcher. The lesson learned was to not be afraid to change the design if it doesn't work.

## Skills Beyond

### Fernando

- Laser cutting metal using the fablight in The Hive
- Programming on a Seeed Studio XIAO SAMD21 mircocontroller
- Using multiple SPI devices

### Ian

- Laser cutting metal using the fablight in The Hive
- Doing manual brushless motor control
- Sublimation printing

## Special Thanks

We would like to thank the following people for their contributions to this project:

Our ambassador and visionary, Golf Daddy:

<img src="/images/ambassador.jpg" height=300>

Golf Daddy helped us and supported us through the initial stages of this project. He provided us with the inspiration and motivation to pursue this project, and we are forever grateful for his guidance.
