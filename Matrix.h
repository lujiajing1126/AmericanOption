#pragma once

#include <cstdlib>
#include <iostream>

template <class T>
class Matrix {
public:
	Matrix(const int& rows,const int& columns);
	Matrix(const Matrix& mat);
	~Matrix();
	void setElem(int row,int col,T val);
	T getElem(int row,int col) const;
	Matrix operator + (const Matrix& M) const;
	Matrix operator - (const Matrix& M) const;
private:
	T* matrix;
	int rows;
	int columns;
};