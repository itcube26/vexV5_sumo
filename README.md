# VEX5 — кнопка-переключатель моторов

Нажал кнопку → моторы включились. Ещё раз нажал → выключились. И так бесконечно.

## Подключение

- **Моторы** → порты VEX5 (по умолчанию 7 и 12)
- **Кнопка** → пин 43 сбоку на нижней плате

## Настройка

В начале файла меняй под себя:

```cpp
const int MOTOR1_PORT = VEX5_PORT_7;  // порт мотора 1
const int MOTOR2_PORT = VEX5_PORT_12; // порт мотора 2
```

### Скорость и направление моторов

Внутри `if (motorsRunning)`:

```cpp
motor1.setSpeed(-200);  // от -200 до 200
motor2.setSpeed(200);
```

- **Скорость** — меняй число (200, 100, 50...)
- **Направление** — меняй знак (`-200` ↔ `200`)

## Код

```cpp
#include <Vex5.h>

Vex5_Motor motor1;
Vex5_Motor motor2;

const int BUTTON_PIN = 43;
const int MOTOR1_PORT = VEX5_PORT_7;
const int MOTOR2_PORT = VEX5_PORT_12;

bool motorsRunning = false;
bool lastButtonState = HIGH;

void setup() {
  Vex5.begin();
  motor1.begin(MOTOR1_PORT);
  motor2.begin(MOTOR2_PORT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  motor1.setSpeed(0);
  motor2.setSpeed(0);
}

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN);

  if (currentButtonState == LOW && lastButtonState == HIGH) {
    motorsRunning = !motorsRunning;
    if (motorsRunning) {
      motor1.setSpeed(-200);
      motor2.setSpeed(200);
    } else {
      motor1.setSpeed(0);
      motor2.setSpeed(0);
    }
    delay(50); // антидребезг
  }
  lastButtonState = currentButtonState;
}
```
