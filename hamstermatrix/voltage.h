#ifndef HAMSTER_MATRIX_VOLTAGE_H
#define HAMSTER_MATRIX_VOLTAGE_H

#include <Arduino.h>


namespace hamstermatrix {


class Voltage
{
public:
    Voltage(uint8_t pinForward, uint8_t pinBackward, unsigned long sleepTime = 100);

    void setup(void);
    void work(void);
    void start(void);
    void stop(void);
    unsigned long sinceLastAction(void);

private:
    uint8_t m_pinForward;
    uint8_t m_pinBackward;
    unsigned long m_sleepTime;
    unsigned long m_lastTime = 0;
    unsigned long m_lastActiveTime = 0;
    bool m_active = false;
};


} // namespace hamstermatrix

#endif // HAMSTER_MATRIX_VOLTAGE_H
