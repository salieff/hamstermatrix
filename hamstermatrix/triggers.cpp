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

void Triggers::sendSequence(uint8_t seq, bool reverse)
{
    m_bitSequence = seq;
    m_reverseMode = reverse;
    m_bitPosition = -1;
    startNextBit();
}

void Triggers::startNextBit(void)
{
    ++m_bitPosition;

    uint8_t leftVal = 0;
    uint8_t rightVal = 0;

    if (m_reverseMode)
    {
        rightVal = HIGH;
        leftVal = (m_bitSequence & (1 << (BITS_COUNT - 1 - m_bitPosition))) ? HIGH : LOW;
    }
    else
    {
        leftVal = HIGH;
        rightVal = (m_bitSequence & (1 << m_bitPosition)) ? HIGH : LOW;
    }

    Serial.printf("[[HMSTRMTRX]] TRIGGERS %d %d\r\n", leftVal, rightVal);
    digitalWrite(m_pinLeft, leftVal);
    digitalWrite(m_pinRight, rightVal);

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
