#pragma once

#include "utils.h"
#include "Matrix.h"

// A Abstract Class, should not be allow to call Consturctor on it
class AmericanOption {
protected:
	AmericanOption(double R,double S0,double ExercisePrice,int steps,double sigma,double year);
	~AmericanOption();
public:
	double getPricing() const;
	virtual double getPresentValue(int row,int cols) const { return 0.; };
	void generateStockPrices();
protected:
	double year;
	// interest rate
	double R;
	// steps of time
	double deltaT;
	// up movement rate
	double u;
	// down movement rate
	double d;
	// price at T0
	double S0;
	// up and down movement probability
	double p_down;
	double p_up;
	// ExercisePrice
	double ExercisePrice;
	// Std.Ev
	double sigma;
	// Steps
	int steps;
	// prices
	Matrix<double> *stocks;
	Matrix<double> *options;
};

class AmericanCallOption: public AmericanOption
{
public:
	AmericanCallOption(double R,double S0,double ExercisePrice,int steps,double sigma,double year);
	~AmericanCallOption(){};
	double getPresentValue(int row,int cols) const;
};

class AmericanPutOption: public AmericanOption
{
public:
	AmericanPutOption(double R,double S0,double ExercisePrice,int steps,double sigma,double year);
	~AmericanPutOption(){};
	double getPresentValue(int row,int cols) const;
};