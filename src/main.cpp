#include <eigen3/Eigen/Dense>

#include <iostream>
#include <windows.h>

#include "Gauss_solver.h"
#include "build_and_print_report.h" 

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    using namespace Eigen;

    MatrixXd matrixGood(4, 4);
    matrixGood << -150.6000,        -8.2900,         7.3900,         8.5700,
                     7.7000,       -77.0000,        -0.8900,        -2.6200,
                     4.3300,         3.0300,       146.8000,        -4.2800,
                     8.7400,        -2.6000,        -1.2700,      -112.4000;
    VectorXd bGood(4);
    bGood << -484.3700, -355.0300, 1077.1400, 566.3300;

    MatrixXd matrixBad(4, 4);
    matrixBad << 60.8800,         2.2960,       100.7360,      -660.6400,
                -90.7200,        -3.4450,      -149.7750,       983.4900,
                 15.1200,         0.5740,        25.0140,      -164.0200,
                  7.5600,         0.2870,        12.4970,       -81.9900;
    VectorXd bBad(4);
    bBad << -306.7360, 457.2250, -76.1540, -38.0870;

    GaussSolver solverGood(matrixGood, bGood);
    GaussSolver solverBad(matrixBad, bBad);
    
    std::cout << "Нахождение необходимых параметров для хорошо обусловленной матрицы из 6 варианта" << std::endl;
    buildAndPrintReport(solverGood);

    std::cout << "Нахождение необходимых параметров для плохо обусловленной матрицы из 6 варианта" << std::endl;
    buildAndPrintReport(solverBad);
}