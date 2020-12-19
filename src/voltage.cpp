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
}

void Voltage::work(void)
{
    if (!m_active)
        return;

    if ((millis() - m_lastTime) < m_sleepTime)
        return;

    printVoltages();
    m_lastTime = millis();
}

void Voltage::start(void)
{
    m_active = true;
}

void Voltage::stop(void)
{
    m_active = false;
}

void Voltage::printVoltages(void)
{
}


} // namespace hamstermatrix
