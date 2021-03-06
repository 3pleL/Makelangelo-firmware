#pragma once

#include <Arduino.h>

#define TODEGREES (180.0 / PI)
#define TORADIANS (PI / 180.0)

// for assembly in isr inner loop
#define A(CODE) " " CODE "\n\t"

// optimize code, please
#define FORCE_INLINE __attribute__((always_inline)) inline

// convenience
#define PENDING(NOW, SOON) ((uint32_t)(NOW - (SOON)) < 0)
#define ELAPSED(NOW, SOON) (!PENDING(NOW, SOON))

// set bit on
#ifndef SBI
#  define SBI(NN, BB) (NN |= (1 << BB))
#endif

// set bit off
#ifndef CBI
#  define CBI(NN, BB) (NN &= ~(1 << BB))
#endif

#define SET_BIT_ON(NN, BB)  SBI(NN, BB)
#define SET_BIT_OFF(NN, BB) CBI(NN, BB)
#define TEST(NN, BB)        (((NN >> BB) & 0x1) == 0x1)
#define SET_BIT(NN, BB, TF) \
  do {                      \
    if (TF)                 \
      SBI(NN, BB);          \
    else                    \
      CBI(NN, BB);          \
  } while (0);
#define FLIP_BIT(NN, BB) (NN ^= (1 << BB))

// wrap all degrees to within -180...180.
FORCE_INLINE float WRAP_DEGREES(float n) {
  n = fmod(n, 360);
  n += 360;
  n = fmod(n, 360);
  if (n > 180) n -= 360;
  return n;
}

// wrap all radians within -PI...PI
FORCE_INLINE float WRAP_RADIANS(float n) {
  n = fmod(n, TWO_PI);
  n += TWO_PI;
  n = fmod(n, TWO_PI);
  if (n > PI) n -= TWO_PI;
  return n;
}

// use in for(ALL_AXIES(i)) { //i will be rising
#define ALL_AXIES(NN) \
  int NN = 0;         \
  NN < NUM_AXIES;     \
  ++NN

// use in for(ALL_MOTORS(i)) { //i will be rising
#define ALL_MOTORS(NN) \
  int NN = 0;          \
  NN < NUM_MOTORS;     \
  ++NN

// use in for(ALL_MUSCLES(i)) { //i will be rising
#define ALL_MUSCLES(NN) \
  int NN = 0;           \
  NN < NUM_MUSCLES;     \
  ++NN
