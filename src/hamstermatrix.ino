#include <Arduino.h>

#include "button.h"
#include "triggers.h"

constexpr static const uint8_t MOTOR_FORWARD_GPI = 34; // (ADC1-6) - измерение напряжения на моторе "вперед" (motor left)
constexpr static const uint8_t MOTOR_BACKWARD_GPI = 35; // (ADC1-7) - измерение напряжения на моторе "назад" (motor right)
constexpr static const uint8_t TRIGGER_LEFT_GPIO = 25;
constexpr static const uint8_t TRIGGER_RIGHT_GPIO = 26;
constexpr static const uint8_t BUTTON_BACK_GPIO = 33; // кнопка на спине

static hamstermatrix::Button BackButton(BUTTON_BACK_GPIO);
static hamstermatrix::Triggers Triggers(TRIGGER_LEFT_GPIO, TRIGGER_RIGHT_GPIO);


void processConsoleInput(void)
{
    if (Serial.available() <= 0)
        return;

#define SWITCH_PIN(pin_no) { \
    auto i = digitalRead(pin_no); \
    Serial.printf("Switch %d pin from %d to %d\r\n", pin_no, i, !i); \
    digitalWrite(pin_no, !i); \
    break; }

#define READ_PIN(pin_no) { \
    auto i = analogRead(pin_no); \
    Serial.printf("Read %d pin = %d\r\n", pin_no, i); \
    break; }

    switch(Serial.read())
    {
        case '1':
            SWITCH_PIN(TRIGGER_LEFT_GPIO)

        case '2':
            SWITCH_PIN(TRIGGER_RIGHT_GPIO)

        case '3':
            BackButton.click();

        case '4':
            READ_PIN(MOTOR_FORWARD_GPI)

        case '5':
            READ_PIN(MOTOR_BACKWARD_GPI)

        default:
            break;
    }

#undef SWITCH_PIN
#undef READ_PIN
}

static unsigned long lastTimestamp = 0;

void setup(void)
{
    Serial.begin(115200);
    Serial.flush();
    Serial.printf("\r\nHamster Matrix\r\n");

    BackButton.setup();
    Triggers.setup();

    for (auto const &pin : {MOTOR_FORWARD_GPI, MOTOR_BACKWARD_GPI})
        pinMode(pin, INPUT);

    for (auto const &pin : {TRIGGER_LEFT_GPIO, TRIGGER_RIGHT_GPIO, BUTTON_BACK_GPIO})
        pinMode(pin, OUTPUT);

    lastTimestamp = millis();
}

void loop(void)
{
    processConsoleInput();

    BackButton.work();
    Triggers.work();

    if ((millis() - lastTimestamp) > 100)
    {
        Serial.printf("Motor_forward = %d Motor_backward = %d\r\n", analogRead(MOTOR_FORWARD_GPI), analogRead(MOTOR_BACKWARD_GPI));
        lastTimestamp = millis();
    }
}
