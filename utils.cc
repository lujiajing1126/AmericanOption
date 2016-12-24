#include "utils.h"

using namespace std;

const double PI = 3.1415926;

double uniformRandom(void) {
	return ((double)(rand()) + 1.)/(((double)RAND_MAX) + 1.);
}

double normalRandom(void) {
#if __cplusplus <= 199711L
	double r1 = uniformRandom();
	double r2 = uniformRandom();
	return sqrt(-2.*log(r1))*cos(2.*PI*r2);
#else
	random_device rd;
	mt19937 gen(rd());
	normal_distribution<> d(0,1);
	return d(gen);
#endif
}

void initRandom(void) {
	srand(time(NULL));
}