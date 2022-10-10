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