#include <Vex5.h>

Vex5_Motor motor7;
Vex5_Motor motor12;

const int BUTTON_PIN = 43;

bool motorsRunning = false;
bool lastButtonState = HIGH; // не нажата (подтяжка к VCC)

void setup() {
  Vex5.begin();
  motor7.begin(VEX5_PORT_7);
  motor12.begin(VEX5_PORT_12);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  motor7.setSpeed(0);
  motor12.setSpeed(0);
}

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN);

  // Фронт нажатия: было HIGH (отпущена) → стало LOW (нажата)
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    motorsRunning = !motorsRunning;

    if (motorsRunning) {
      motor7.setSpeed(-3000);
      motor12.setSpeed(3000);
    } else {
      motor7.setSpeed(0);
      motor12.setSpeed(0);
    }

    delay(50); // антидребезг
  }

  lastButtonState = currentButtonState;
}
