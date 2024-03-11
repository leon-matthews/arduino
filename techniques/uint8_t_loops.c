
#include <cstdint>
#include <iostream>


using std::cout;
using std::endl;


/**
Looping up and down 8-bit values using 8-bit counters is not so easy at
it first seems.
*/
int main(int argv, char** argc) {
    // 0 to 255
    cout << "Loop up from 0 to 255:" << endl;
    uint8_t i = 0;
    do {
        cout << int(i) << ' ';
    } while (i++ != 255);
    cout << endl;
    cout << "Suprisingly, the value of 'i' is now: " << int(i) << endl << endl;

    // 255 to zero
    cout << "Count down from 255 to 0:" << endl;
    i = 255;
    do {
        cout << int(i) << ' ';
    } while (i--);
    cout << endl;
    cout << "And now, the value of 'i' is now: " << int(i) << endl;

    return 0;
}
