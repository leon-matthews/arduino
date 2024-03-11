
#include <iomanip>
#include <iostream>
#include <cstdint>


using namespace std;


/* The state word must be initialized to non-zero */
uint32_t xorshift32(uint32_t state[])
{
  /* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
  uint32_t x = state[0];
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  state[0] = x;
  return x;
}


uint64_t xorshift64(uint64_t state[])
{
  uint64_t x = state[0];
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  state[0] = x;
  return x;
}



/**
32-bit xorshift pseudo-random generator by George Marsaglia.

Straightforward C++ implmentation, with the addition of narrowing casts
for 8, 16, and 32-bit output. Intended for use in an 8-bit microcontroller.

See:
    Wikipedia:
        https://en.wikipedia.org/wiki/Xorshift

    Xorshift RNGs (2003):
        Journal of Statistical Software. 8 (14). doi:10.18637/jss.v008.i14.
        https://www.jstatsoft.org/article/view/v008i14
*/
class XORShift32 {

public:
    XORShift32(uint32_t state) {
        this->state = state ? state : 1;
    }

    uint8_t uint8() {
        next();
        return static_cast<uint8_t>(state >> 24);
    }

    uint16_t uint16() {
        next();
        return static_cast<uint16_t>(state >> 16);
    }

    uint32_t uint32() {
        next();
        return state;
    }

private:
    void next() {
        uint32_t x{state};
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        state = x;
    }

    uint32_t state;
};


int main()
{
    cout << "xorshift32(1)" << endl;
    uint32_t state[1] = {1};
    for(size_t i = 0; i < 30; i++) {
        cout << xorshift32(state) << endl;
    }
    cout << endl;


    cout << "XORShift32(1)" << endl;
    auto rand = XORShift32(-1);
    for(size_t i = 0; i < 10; i++) {
        cout << "uint8: " << std::setw(6) << (size_t) rand.uint8() << " ";
        cout << "uint16: " << std::setw(8) << rand.uint16() << " ";
        cout << "uint32: " << std::setw(12) << rand.uint32() << std::endl;
    }
    cout << std::endl;


    //~ uint64_t state64[1] = {1};
    //~ cout << "xorshift64()" << endl << state64[0] << endl;
    //~ for (int i = 0; i < 10; i++) {
    //~ cout << xorshift64(state64) << endl;
    //~ }
    //~ cout << endl;
}
