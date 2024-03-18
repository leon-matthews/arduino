#pragma once

#include <stdint.h>


/**
Quick and (very) dirty primality test.
*/
const uint8_t primes[] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
    43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
};


inline uint16_t modulus(uint16_t x, uint16_t n) {
    return x % n;
}


inline uint16_t modulus2(uint16_t x, uint16_t n) {
  return (uint16_t) (((uint32_t) x * (uint32_t) n) >> 16);
}


uint16_t is_prime(uint16_t n);
uint16_t next_prime(uint16_t n);
uint16_t previous_prime(uint16_t n);
