#ifndef HAMSTER_MATRIX_TRIGGERS_H
#define HAMSTER_MATRIX_TRIGGERS_H

#include <Arduino.h>


namespace hamstermatrix {


class Triggers {
public:
    constexpr static const bool REVERSE_MODE = true;

    Triggers(uint8_t pinLeft, uint8_t pinRight, unsigned long holdTime = 50);

    void setup(void);
    void work(void);
    void sendSequence(uint8_t seq, bool reverse = false);

private:
    enum State
    {
        IDLE,
        BIT,
        BLANK
    };

    uint8_t m_pinLeft;
    uint8_t m_pinRight;
    unsigned long m_holdTime;
    State m_state = IDLE;
    uint8_t m_bitSequence = 0;
    int m_bitPosition = -1;
    unsigned long m_startTime = 0;
    bool m_reverseMode = false;

    static constexpr const int BITS_COUNT = 6;

    void startNextBit(void);
    void startBlank(bool lastBlank);
};


} // namespace hamstermatrix

#endif // HAMSTER_MATRIX_TRIGGERS_H
