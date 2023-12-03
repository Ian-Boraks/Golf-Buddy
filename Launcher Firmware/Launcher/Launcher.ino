 #include <Servo.h>

Servo Motor;

#define motorButton 8
#define dropButton 4
#define dropBar 9


int motorSpeed = 1200;

volatile bool ballReady = false;

void setup() {
  Serial.begin(115200);

  pinMode(motorButton, INPUT_PULLUP);
  pinMode(dropButton, INPUT_PULLUP);
  pinMode(dropBar, OUTPUT);
  
  Motor.attach(0);

  delay(100);
  
  Motor.writeMicroseconds(0);
  delayMicroseconds(400);
  Motor.writeMicroseconds(1800);
  delayMicroseconds(500);
  Motor.writeMicroseconds(1000);
}

void updateMotor() {
  if (!digitalRead(motorButton)) {
    Motor.writeMicroseconds(motorSpeed);
  } else {
    Motor.writeMicroseconds(1040);
  }
}

void loop() {
  updateMotor();
  
  if (!digitalRead(dropButton)) {
    digitalWrite(13, HIGH);
    digitalWrite(dropBar, HIGH);
    Motor.writeMicroseconds(1040);

    int i = 0;
    for(;;) {
      digitalWrite(dropBar, HIGH);
      delay(1);
      
      updateMotor();

      if (i > 1000 && !digitalRead(dropButton)) break;
      if (++i > 10000) break;
    }

    digitalWrite(13, LOW);
    digitalWrite(dropBar, LOW);
    delay(500);
  }
}
