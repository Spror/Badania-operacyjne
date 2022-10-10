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

#include "Dynamic2DMatrix.hpp"


template <typename T>
Dynamic2DMatrix<T>::Dynamic2DMatrix(const unsigned int x, const unsigned int y): sizeX(x), sizeY(y)
{
    data.resize(this->sizeX * this->sizeY);
}

template <typename T>
T Dynamic2DMatrix<T>::operator [](const unsigned int x)
{
    if( x >= this->sizeX * this->sizeY)
    {
        std::cerr << "Dynamic2DMatrix:: out of range \n";
        exit(-1);
    }

    return (data[x]);
}


template <typename T>
T& Dynamic2DMatrix<T>::operator ()(const unsigned int x, const unsigned int y)
{
    if( x >= this->sizeX || y >= this->sizeY)
    {
        std::cerr << "Dynamic2DMatrix:: out of range \n";
        exit(-1);
    }

    return (data[this->sizeX]*y + x);
}


template <typename T>
void Dynamic2DMatrix<T>::print()
{
    for(auto i = 0u; i < (this->sizeX*this->sizeY); i++ )
    {
        std::cout << this->data[i] << " ";

        if((i+1) % this->sizeY == 0 && i != 0)
            std::cout << "\n";
    }
}

template <typename T>
bool Dynamic2DMatrix<T>::insert_data(std::vector<T> data)
{
    if(data.size() != this->data.size())
    {
        std::cerr << "Dynamic2DMatrix: Wrong size of input vector \n";
        return false;
    }

    for(auto i = 0u; i < this->data.size(); i++)
    {
        this->data[i] = data[i];
    }
    return true;
}

