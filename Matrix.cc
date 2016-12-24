#include "Matrix.h"

using namespace std;

template <class T>
Matrix<T>::Matrix(const int& r,const int& c):rows(r),columns(c) {
	matrix = static_cast<T*>(calloc(1,sizeof(T) * rows * columns));
}

template <class T>
Matrix<T>::~Matrix() {
	free(matrix);
}

template <class T>
void Matrix<T>::setElem(int row,int col,T val) {
	int offset = row * rows + col;
	matrix[offset] = val;
}

template <class T>
T Matrix<T>::getElem(int row,int col) const {
	int offset = row * rows + col;
	return matrix[offset];
}

template <class T>
Matrix<T>::Matrix(const Matrix& M):rows(M.rows),columns(M.columns) {
	matrix = static_cast<T*>(calloc(1,sizeof(T) * rows * columns));
	for (int i = 0; i < rows * columns; ++i)
	{
		matrix[i] = M.matrix[i];
	}
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix& M) const {
	Matrix<T> mat(rows,columns);
	for (int i = 0; i < rows * columns; ++i)
	{
		mat.matrix[i] = matrix[i] + M.matrix[i];
	}
	return mat;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix& M) const {
	Matrix<T> mat(rows,columns);
	for (int i = 0; i < rows * columns; ++i)
	{
		mat.matrix[i] = matrix[i] - M.matrix[i];
	}
	return mat;
}