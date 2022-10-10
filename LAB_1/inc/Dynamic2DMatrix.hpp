#pragma once
#include <iostream>
#include <vector>
/*
 * The class was created to represent a 2d matrix which stores data defined by a template type
 */
template <typename T>
class Dynamic2DMatrix{

std::vector<T> data;         // Vector of T-type data
unsigned int sizeX, sizeY;   // size of a matrix 

public:
/*
 *  Parametric construcor is used to setting sizeX and sizeY and resizing the vector data
 *  @param[in] x  - number of rows
 *  @param[in] y  - number of columns
 */
Dynamic2DMatrix(const unsigned int x, const unsigned int y);

/*
 * Overloading [] operator. Created to get data from the matrix (vector:: data) 
 * @param[in] x - an index of a cell of the matrix
 * 
 * @return - copy of a value of cell
 */
T operator [](const unsigned int x);

/*
 * Overloading () operator. Created to write data to the matrix (vector:: data) 
 * @param[in] x - an index of a cell's row
 * @param[in] y - an index of a cell's row
 * 
 * @return - reference to the cell(x,y)
 */
T& operator ()(const unsigned int x, const unsigned int y);

/*
 * Method to print contents of the matrix
 */
void print();

/*
 * Method to insert data to the matrix(vector)
 * @param[in] data - vector storing T-types values and which is used to set matrix data
 * @return = true if the operation will be executed properly or false in another case
 */
bool insert_data(std::vector<T> data);


unsigned int rows_number() { return this->sizeX; }
unsigned int columns_number() { return this->sizeY; }
};



