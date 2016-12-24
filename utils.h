#include <cmath>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <random>

#ifndef _FP_UTILS
#define _FP_UTILS

extern const double PI;
#define EPSILON (1.0E-8)

extern double uniformRandom(void);
extern double normalRandom(void);
extern void initRandom(void);

#endif