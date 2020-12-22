#ifndef HAMSTER_MATRIX_BUTTON_H
#define HAMSTER_MATRIX_BUTTON_H

#include <Arduino.h>


namespace hamstermatrix {


class Button {
public:
    Button(uint8_t pin, unsigned long holdTime = 100);

    void setup(void);
    void work(void);
    void click(void);

private:
    enum State
    {
        PRESSED,
        RELEASED
    };

    uint8_t m_pin;
    unsigned long m_holdTime;
    State m_state = RELEASED;
    unsigned long m_pressTime = 0;
};


} // namespace hamstermatrix

#endif // HAMSTER_MATRIX_BUTTON_H
