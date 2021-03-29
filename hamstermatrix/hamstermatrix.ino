#include <Arduino.h>

#include "button.h"
#include "triggers.h"
#include "voltage.h"


constexpr static const uint8_t MOTOR_FORWARD_GPI = 34; // (ADC1-6) - измерение напряжения на моторе "вперед" (motor left)
constexpr static const uint8_t MOTOR_BACKWARD_GPI = 35; // (ADC1-7) - измерение напряжения на моторе "назад" (motor right)
constexpr static const uint8_t TRIGGER_LEFT_GPIO = 25;
constexpr static const uint8_t TRIGGER_RIGHT_GPIO = 26;
constexpr static const uint8_t BUTTON_BACK_GPIO = 33; // кнопка на спине

static hamstermatrix::Button BackButton(BUTTON_BACK_GPIO);
static hamstermatrix::Triggers Triggers(TRIGGER_LEFT_GPIO, TRIGGER_RIGHT_GPIO);
static hamstermatrix::Voltage MotorVoltage(MOTOR_FORWARD_GPI, MOTOR_BACKWARD_GPI);

static String UARTBuffer;


void processConsoleInput(void)
{
    int c = 0;

    while ((c = Serial.read()) > 0)
    {
        if (c != '\r' && c != '\n')
        {
            UARTBuffer += static_cast<char>(c);
            continue;
        }

        if (UARTBuffer.isEmpty())
            continue;

        String str(UARTBuffer);
        UARTBuffer.clear();

        if (str.startsWith("START"))
        {
            BackButton.click();
            MotorVoltage.start();
            return;
        }

        if (str.startsWith("STOP"))
        {
            // Если мотор стоит больше 10 секунд, значит хомяк уже выключился сам,
            // и нажимать кнопку не надо, а то опять включится
            if (MotorVoltage.sinceLastAction() < 10000)
                BackButton.click();

            MotorVoltage.stop();
            return;
        }

        if (str.startsWith("TRIGGER"))
        {
            Triggers.sendSequence(static_cast<uint8_t>(str.substring(8).toInt()));
            return;
        }

        if (str.startsWith("REVTRIGGER"))
        {
            Triggers.sendSequence(static_cast<uint8_t>(str.substring(11).toInt()), hamstermatrix::Triggers::REVERSE_MODE);
            return;
        }
    }

    /*
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
    */
}

void setup(void)
{
    Serial.begin(115200);
    Serial.flush();

//    printHelp();
    Serial.println("[[HMSTRMTRX]] READY");

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
