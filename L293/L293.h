#pragma once


namespace L293 {


/**
Example of IO interface needed for Motor class.
*/
class IO {
    void set_input1(bool);
    void set_input2(bool);
    void set_enable(bool);
    void pwn_enable(uint8_t);
};


/**
Drive a motor using one half of the L293.
*/
template <typename IO>
class Motor {
    public:
        Motor<IO>(IO& io) : io{io} {}
        void backward(uint8_t speed=255);
        void coast();
        void forward(uint8_t speed=255);
        void set_speed(uint8_t speed);
        void stop();

    private:
        IO& io;
};


/**
Move motor backwards.

Args:
    speed:
        Value between 0 and 255, where 255 is full speed.
        Defaults to 255.
*/
template <typename IO>
void Motor<IO>::backward(uint8_t speed) {
    io.set_input1(false);
    io.set_input2(true);
    set_speed(speed);
}


/**
Allow motor to coast to stop by disconnecting its terminals.
*/
template <typename IO>
void Motor<IO>::coast() {
    io.set_input1(false);
    io.set_input2(false);
    io.set_enable(false);
}


/**
Run motor forwards at the given speed.

Args:
speed:
Value between 0 and 255, where 255 is full speed.
Defaults to 255.

*/
template <typename IO>
void Motor<IO>::forward(uint8_t speed) {
    io.set_input1(true);
    io.set_input2(false);
    set_speed(speed);
}

/**
Change speed without changing direction.

Args:
speed:
Value between 0 and 255, where 255 is full speed.

*/
template <typename IO>
void Motor<IO>::set_speed(uint8_t speed) {
    if (speed == 0) {
        io.set_enable(false);
    } else if (speed == 255) {
        io.set_enable(true);
    } else {
        io.pwn_enable(speed);
    }
}

/**
Stop quickly by shorting motor's terminals together.
*/
template <typename IO>
void Motor<IO>::stop() {
    io.set_input1(false);
    io.set_input2(false);
    io.set_enable(true);
}


}
