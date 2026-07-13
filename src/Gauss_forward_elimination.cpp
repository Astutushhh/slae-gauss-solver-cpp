#include "Gauss_solver.h"
#include <iostream>

void GaussForwardElimination::avoidIncreasingErr(Eigen::MatrixXd& A, int i, int matrixLength) const
{
    int segmentIndexMaxRow;
    A.col(i).segment(i, matrixLength - i).cwiseAbs().maxCoeff(&segmentIndexMaxRow); // Нашли максимальный элемент
    A.row(i).swap(A.row(segmentIndexMaxRow + i));                                   // Поменяли строчки 
}

void GaussForwardElimination::subtractNormolizedRow(Eigen::MatrixXd& A, int i, int matrixLength) const
{
    for(int j = i + 1; j < matrixLength; j++)
        A.row(j) -= A.row(i) * A(j, i);   
}

void GaussForwardElimination::isMatrixSingular(Eigen::MatrixXd& A, int matrixLength) const
{
    constexpr double kEps = 1e-12; // значение константы задается на этапе компиляции. Машинный эпсилон примерно е-16 для дабла, но мы учли накопление ошибки
    
    for(int i = 0; i < matrixLength; i++)
        if(kEps >= A.col(i).cwiseAbs().maxCoeff())
            throw std::invalid_argument("Матрица вырождена");   
}

Eigen::MatrixXd GaussForwardElimination::forwardElimination(Eigen::MatrixXd A) const
{

    int matrixLength = A.rows();

    isMatrixSingular(A, matrixLength);

    for(int i = 0; i < matrixLength; i++)
    {
        avoidIncreasingErr(A, i, matrixLength);
        
        A.row(i) /= A(i,i); // Нормализовали строку
        
        subtractNormolizedRow(A, i, matrixLength);
    }
    return A;
}