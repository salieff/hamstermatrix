#include "voltage.h"


namespace hamstermatrix {


Voltage::Voltage(uint8_t pinForward, uint8_t pinBackward, unsigned long sleepTime)
    : m_pinForward(pinForward)
    , m_pinBackward(pinBackward)
    , m_sleepTime(sleepTime)
{
}

void Voltage::setup(void)
{
    pinMode(m_pinForward, INPUT);
    pinMode(m_pinBackward, INPUT);

    m_lastTime = millis();
    m_lastActiveTime = millis();
}

void Voltage::work(void)
{
    if (!m_active)
        return;

    if ((millis() - m_lastTime) < m_sleepTime)
        return;

    int motorVoltage = analogRead(m_pinForward) - analogRead(m_pinBackward);
    Serial.printf("[[HMSTRMTRX]] MOTOR %d\r\n", motorVoltage);
    m_lastTime = millis();

    if (motorVoltage != 0)
        m_lastActiveTime = m_lastTime;
}

void Voltage::start(void)
{
    m_active = true;
}

void Voltage::stop(void)
{
    m_active = false;
}

unsigned long Voltage::sinceLastAction(void)
{
    return millis() - m_lastActiveTime;
}

} // namespace hamstermatrix
