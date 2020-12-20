#include "triggers.h"


namespace hamstermatrix {


Triggers::Triggers(uint8_t pinLeft, uint8_t pinRight, unsigned long holdTime)
    : m_pinLeft(pinLeft)
    , m_pinRight(pinRight)
    , m_holdTime(holdTime)
{
}

void Triggers::setup(void)
{
    pinMode(m_pinLeft, OUTPUT);
    pinMode(m_pinRight, OUTPUT);
}

void Triggers::work(void)
{
    if (m_state == IDLE)
        return;

    if ((millis() - m_startTime) < m_holdTime)
        return;

    switch (m_state)
    {
    case BIT:
        startBlank(m_bitPosition >= (BITS_COUNT - 1));
        break;

    case BLANK:
        startNextBit();
        break;

    default:
        break;
    }
}

void Triggers::sendSequence(uint8_t seq)
{
    m_bitSequence = seq;
    m_bitPosition = -1;
    startNextBit();
}

void Triggers::startNextBit(void)
{
    ++m_bitPosition;

    Serial.printf("Triggers: %d %d\r\n", HIGH, (m_bitSequence & (1 << m_bitPosition)) ? HIGH : LOW);
    digitalWrite(m_pinLeft, HIGH);
    digitalWrite(m_pinRight, (m_bitSequence & (1 << m_bitPosition)) ? HIGH : LOW);

    m_startTime = millis();
    m_state = BIT;
}

void Triggers::startBlank(bool lastBlank)
{
    digitalWrite(m_pinLeft, LOW);
    digitalWrite(m_pinRight, LOW);

    m_startTime = millis();
    m_state = lastBlank ? IDLE : BLANK;
}

} // namespace hamstermatrix
