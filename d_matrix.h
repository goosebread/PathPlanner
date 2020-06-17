#pragma once
// Team Sombrero
// 6/12/2019
// d_matrix.h header file
// Implements a basic matrix class with resize and accessor functions
// Taken from Matrix.h from Project 3. The additional functions specific to Project 3 were removed

#include <vector>

//taken from ppt 13
template <typename T>
class matrix {
private:
	int nRows, nCols;
	std::vector<std::vector<T> > mat;

public:
	//constructor
	matrix(int numRows = 1, int numCols = 1, const T& initVal = T());

	//get entire row
	std::vector<T>& operator[] (int i);
	const std::vector<T>& operator[](int i) const;

	//accessor functions
	int rows() const;
	int cols() const;

	//resize
	void resize(int numRows, int numCols);

	//the old additional functions were removed
};

template<typename T>
matrix<T>::matrix(int numRows, int numCols, const T& initVal)
	:nRows{ numRows }, nCols{ numCols }{

	mat.resize(numRows);
	for (int i = 0; i < numRows; i++) {
		mat.at(i).resize(numCols);
		for (int j = 0; j < numCols; j++) {
			mat.at(i).at(j) = initVal;
		}
	}
}

template<typename T>
std::vector<T>& matrix<T>::operator[](int i) {
	return mat.at(i);
}

template<typename T>
const std::vector<T>& matrix<T>::operator[](int i) const {
	return mat.at(i);
}

template<typename T>
int matrix<T>::rows() const {
	return nRows;
}

template<typename T>
int matrix<T>::cols() const {
	return nCols;
}

template<typename T>
void matrix<T>::resize(int numRows, int numCols) {
	nRows = numRows;
	nCols = numCols;
	mat.resize(numRows);
	for (int i = 0; i < numRows; i++) {
		mat.at(i).resize(numCols);
	}
}

