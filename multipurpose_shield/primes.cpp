
#include <Arduino.h>

#include "primes.h"


uint16_t is_prime(uint16_t n) {
    if (n == 2) {
        return true;
    }

    if ( ! (n & (1 << 0))) {
        return false;
    }

    for (auto prime : primes) {
        if (n > prime) {
            if ( modulus(n, prime) == 0) {
                return false;
            }
        } else {
            return true;
        }
    }
    return true;
}


uint16_t next_prime(uint16_t n) {
    while (true) {
        n += 1;
        if (n <= 2) {
            return 2;
        }
        if (is_prime(n)) {
            return n;
        }
    }
}


uint16_t previous_prime(uint16_t n) {
    while (true) {
        n -= 1;
        if (n <= 2) {
            return 2;
        }
        if (is_prime(n)) {
            return n;
        }
    }
}
