#ifndef Matrix

#pragma once

#include <string>

#include "QueueForRBTree.h"
using namespace std;
struct Matrix
{
    double** matrix;
    int size;

    Matrix(int);
};

Matrix::Matrix(int size)
{
    this->size = size;
    matrix = new double* [size];
    for (int i = 0; i < size; i++)
    {
        matrix[i] = new double[size];
        for (int j = 0; j < size; j++)
            matrix[i][j] = -1;
    }
}


#endif Matrix