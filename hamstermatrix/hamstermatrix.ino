#include <Arduino.h>

#include "button.h"
#include "triggers.h"
#include "voltage.h"


constexpr static const uint8_t MOTOR_FORWARD_GPI = 34; // (ADC1-6) - измерение напряжения на моторе "вперед" (motor left)
constexpr static const uint8_t MOTOR_BACKWARD_GPI = 35; // (ADC1-7) - измерение напряжения на моторе "назад" (motor right)
constexpr static const uint8_t TRIGGER_LEFT_GPIO = 25;
constexpr static const uint8_t TRIGGER_RIGHT_GPIO = 26;
constexpr static const uint8_t BUTTON_BACK_GPIO = 33; // кнопка на спине

constexpr static const uint8_t BATH_CODE  = 5;  // 000101 <-- Первый бит справа
constexpr static const uint8_t WHEEL_CODE = 9;  // 001001 <-- Первый бит справа
constexpr static const uint8_t DISCO_CODE = 17; // 010001 <-- Первый бит справа
constexpr static const uint8_t POOL_CODE  = 19; // 010011 <-- Первый бит справа


static hamstermatrix::Button BackButton(BUTTON_BACK_GPIO);
static hamstermatrix::Triggers Triggers(TRIGGER_LEFT_GPIO, TRIGGER_RIGHT_GPIO);
static hamstermatrix::Voltage MotorVoltage(MOTOR_FORWARD_GPI, MOTOR_BACKWARD_GPI);


void printHelp(void)
{
    Serial.println();
    Serial.println("Hamster Matrix");
    Serial.println();
    Serial.println("? - this help topic");
    Serial.println("1 - Start hamster");
    Serial.println("2 - Send BATH_CODE");
    Serial.println("3 - Send BATH_CODE in reverse order");
    Serial.println("4 - Send WHEEL_CODE");
    Serial.println("5 - Send WHEEL_CODE in reverse order");
    Serial.println("6 - Send DISCO_CODE");
    Serial.println("7 - Send DISCO_CODE in reverse order");
    Serial.println("8 - Send POOL_CODE");
    Serial.println("9 - Send POOL_CODE in reverse order");
    Serial.println("0 - Stop hamster");
    Serial.println();
}

void processConsoleInput(void)
{
    if (Serial.available() <= 0)
        return;

    switch(Serial.read())
    {
    case '?':
        printHelp();
        break;

    case '1':
        BackButton.click();
        MotorVoltage.start();
        break;

    case '2':
        Triggers.sendSequence(BATH_CODE);
        break;

    case '3':
        Triggers.sendSequence(BATH_CODE, hamstermatrix::Triggers::REVERSE_MODE);
        break;

    case '4':
        Triggers.sendSequence(WHEEL_CODE);
        break;

    case '5':
        Triggers.sendSequence(WHEEL_CODE, hamstermatrix::Triggers::REVERSE_MODE);
        break;

    case '6':
        Triggers.sendSequence(DISCO_CODE);
        break;

    case '7':
        Triggers.sendSequence(DISCO_CODE, hamstermatrix::Triggers::REVERSE_MODE);
        break;

    case '8':
        Triggers.sendSequence(POOL_CODE);
        break;

    case '9':
        Triggers.sendSequence(POOL_CODE, hamstermatrix::Triggers::REVERSE_MODE);
        break;

    case '0':
        BackButton.click();
        MotorVoltage.stop();
        break;
    }

}

void setup(void)
{
    Serial.begin(115200);
    Serial.flush();

    printHelp();

    BackButton.setup();
    Triggers.setup();
    MotorVoltage.setup();
}

void loop(void)
{
    processConsoleInput();

    BackButton.work();
    Triggers.work();
    MotorVoltage.work();
}
