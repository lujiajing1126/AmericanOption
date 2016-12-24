#include "AmericanOption.h"
#include "Matrix.cc"

using namespace std;

AmericanOption::AmericanOption(double R,double S0,double ExercisePrice,int steps,double sigma,double year):R(R),S0(S0),ExercisePrice(ExercisePrice),sigma(sigma),steps(steps),year(year) {
	deltaT = year / steps;
	u = exp(sigma * sqrt(deltaT));
	d = 1./u;
	p_up = (exp(R * deltaT) - d)/(u-d);
	p_down = 1 - p_up;
	// Init stocks
	stocks = new Matrix<double>(steps+1,steps+1);
	// Init Options
	options = new Matrix<double>(steps+1,steps+1);
	for (int i = 0; i < steps + 1; ++i) {
		for (int j = 0; j < steps+1; ++j) {
			stocks->setElem(i,j,0.);
		}
	}
	stocks->setElem(0,0,S0);
}

AmericanOption::~AmericanOption() {
	delete stocks;
	delete options;
}

void AmericanOption::generateStockPrices() {
	for (int i = 1; i < steps+1; ++i) {
		for (int j = 0; j < i+1; ++j) {
			if (j < (i+1)/2) {
				stocks->setElem(i,j,stocks->getElem(i-1,j) * u);
			} else {
				stocks->setElem(i,j,stocks->getElem(i-1,j-1) * d);
			}
		}
	}
	for (int i = 0; i < steps + 1; ++i) {
		if (getPresentValue(steps,i) <= 0) {
			options->setElem(steps,i,0.);
		} else {
			options->setElem(steps,i,getPresentValue(steps,i));
		}
	}

	for (int i = steps - 1; i >= 0; --i) {
		for (int j = 0; j < i + 1; ++j) {
			options->setElem(i,j,((options->getElem(i+1,j) * p_up + options->getElem(i+1,j+1) * p_down) * exp(-1. * R * deltaT)));
			if (getPresentValue(i,j) >= options->getElem(i,j)) {
				options->setElem(i,j,getPresentValue(i,j));
			}
		}
	}
}

double AmericanOption::getPricing() const {
	return options->getElem(0,0);
}

AmericanCallOption::AmericanCallOption(double R,double S0,double ExercisePrice,int steps,double sigma,double year): AmericanOption(R,S0,ExercisePrice,steps,sigma,year) {

}

double AmericanCallOption::getPresentValue(int row,int cols) const {
	return stocks->getElem(row,cols) - ExercisePrice;
}

AmericanPutOption::AmericanPutOption(double R,double S0,double ExercisePrice,int steps,double sigma,double year): AmericanOption(R,S0,ExercisePrice,steps,sigma,year) {

}

double AmericanPutOption::getPresentValue(int row,int cols) const {
	return ExercisePrice - stocks->getElem(row,cols);
}

int main(void) {
	double rate;
	double pPrice;
	double ePrice;
	double year;
	int steps;
	double sigma;
	cout << "请输入当前股价: ";
	cin >> pPrice;
	cout << "请输入执行价格: ";
	cin >> ePrice;
	cout << "请输入市场无风险利率: ";
	cin >> rate;
	cout << "请输入期权年限: ";
	cin >> year;
	cout << "请输入波动率: ";
	cin >> sigma;
	cout << "请输入步长: ";
	cin >> steps;
	AmericanCallOption option(rate,pPrice,ePrice,steps,sigma,year);
	AmericanOption *opt_ptr = &option;
	opt_ptr->generateStockPrices();
	double price = opt_ptr->getPricing();
	cout << "该期权的现值为: " << price << endl;
}