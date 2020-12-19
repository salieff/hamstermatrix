#include "button.h"


namespace hamstermatrix {


Button::Button(uint8_t pin, unsigned long holdTime)
    : m_pin(pin)
    , m_holdTime(holdTime)
{
}

void Button::setup(void)
{
    pinMode(m_pin, OUTPUT);
}

void Button::work(void)
{
    if (m_state == RELEASED)
        return;

    if ((millis() - m_pressTime) < m_holdTime)
        return;

    digitalWrite(m_pin, LOW);
    m_state = RELEASED;
}

void Button::click(void)
{
    digitalWrite(m_pin, HIGH);
    m_pressTime = millis();
    m_state = PRESSED;
}


} // hamstermatrix
