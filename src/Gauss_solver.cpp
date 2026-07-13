#include <iostream>
#include "Gauss_solver.h"

void GaussSolver::checkMatrix(const Eigen::MatrixXd& A) const
{
    if(!(A.rows() >= A.cols() - 1))
        throw std::invalid_argument("Число уравнений меньше количества переменных");
}

void GaussSolver::prepRectMatrixIfItsNeed(Eigen::MatrixXd& A) const
{
    if(!(A.rows() == A.cols() - 1))
        A = A.topRows(A.cols()-1);
}

void GaussSolver::checkDimensions(const Eigen::MatrixXd& A, const Eigen::VectorXd& b) const
{
    if(A.rows() != b.size())
        throw std::invalid_argument("Длина матрицы и решений матрицы не совпадает");
}

Eigen::MatrixXd GaussSolver::makeAugmentedMatrix(const Eigen::MatrixXd& A, const Eigen::VectorXd& b) const
{
    checkDimensions(A, b);

    Eigen::MatrixXd Aug (A.rows(), A.cols() + 1);
    Aug << A, b;
    return Aug;
}

GaussSolver::GaussSolver(Eigen::MatrixXd& A, Eigen::VectorXd& b) : 
    augmented_(makeAugmentedMatrix(A, b)),
    b_(b),
    A_(A)
{
    checkMatrix(augmented_);
    prepRectMatrixIfItsNeed(augmented_);
}

Eigen::VectorXd GaussSolver::solve()
{
    Eigen::MatrixXd upperTriangularMatrix;
    upperTriangularMatrix = forward_.forwardElimination(augmented_);
    solution_ = backward_.backwardSubstitution(upperTriangularMatrix);

    calcResidual();//Посчитали невязку
    
    solved_ = true;

    return solution_;
}

void GaussSolver::calcResidual()
{
    residual_ = A_ * solution_ - b_; 
}

double GaussSolver::absFirstResidualNorm()
{
    solutionExists();
    absFirstNorm_ = residual_.lpNorm<1>();
    absFirstNormBool_ = true;
    return absFirstNorm_;
}

double GaussSolver::absInfiniteResidualNorm()
{
    solutionExists();
    absInfiniteNorm_ = residual_.lpNorm<Eigen::Infinity>();
    absInftNormBool_ = true;
    return absInfiniteNorm_;
}

double GaussSolver::conditionNumber()
{
    condNum_ = A_.norm() * A_.inverse().norm();
    condNumBool_ = true;
    return condNum_;
}

double GaussSolver::getAbsErrorBoundFirst()
{
    absFirstNormExist();
    absErrorBoundFirst_ = absFirstNorm_ * A_.inverse().norm();
    return absErrorBoundFirst_;
}

double GaussSolver::getAbsErrorBoundInf()
{
    absInfNormExist();
    absErrorBoundInfinite_ = absInfiniteNorm_ * A_.inverse().norm();
    return absErrorBoundInfinite_;
}

double GaussSolver::getRelErrorBoundFirst()
{
    absFirstNormExist();
    condNumExist(); 
    
    relErrorBoundFirst_ = (absFirstNorm_ / b_.lpNorm<1>()) * condNum_;
    return relErrorBoundFirst_;
}

double GaussSolver::getRelErrorBoundInf()
{
    absInfNormExist();
    condNumExist();

    relErrorBoundInfinite_ = (absInfiniteNorm_/b_.lpNorm<Eigen::Infinity>()) * condNum_;
    return relErrorBoundInfinite_;
}

void GaussSolver::solutionExists() const
{
    if(!solved_)
        throw std::invalid_argument("Система обязана быть решенной перед вызовом функции...");
}

void GaussSolver::absFirstNormExist() const
{
    if(!absFirstNormBool_)
        throw std::invalid_argument("Должна быть найдена абсолютная первая норма перед вызовом функции relFirstResidualNorm()");
}
void GaussSolver::absInfNormExist() const
{
    if(!absInftNormBool_)
        throw std::invalid_argument("Должна быть найдена абсолютная inf норма перед вызовом функции relInfiniteResidualNorm()");
}

void GaussSolver::condNumExist() const
{
    if(!condNumBool_)
        throw std::invalid_argument("Должен быть найден порядок числа обусловленности матрицы перед вызовом функции");
}