#include "build_and_print_report.h"
#include <iostream>
#include <iomanip>

void buildAndPrintReport(GaussSolver& solver)
{
    Eigen::VectorXd solution = solver.solve();

    double absFirstNorm = solver.absFirstResidualNorm();
    double absInfiniteNorm = solver.absInfiniteResidualNorm();

    double conditionNumber = solver.conditionNumber();

    double relFirstErrBound = solver.getRelErrorBoundFirst();
    double relInfiniteErrBound = solver.getRelErrorBoundInf();

    double absFirstErrBound = solver.getAbsErrorBoundFirst();
    double absInfiniteErrBound = solver.getAbsErrorBoundInf();

    std::cout << std::scientific << std::setprecision(17);
    std::cout << "Вектор решений матрицы:" << std::endl << solution << std::endl;

    std::cout << "Первая норма невязки = " << absFirstNorm << std::endl;
    std::cout << "Бесконечная норма невязки = " << absInfiniteNorm << std::endl;

    std::cout << std::endl;

    std::cout << "Абсолютная погрешность решения системы (первая норма) = " << absFirstErrBound << std::endl;
    std::cout << "Абсолютная погрешность решения системы (бесконечная норма) = " << absInfiniteErrBound << std::endl;
    std::cout << std::endl;
    std::cout << "Относительная погрешность решения системы (первая норма) = " << relFirstErrBound << std::endl;
    std::cout << "Относительная погрешность решения системы (бесконечная норма) = " << relInfiniteErrBound << std::endl;

    std::cout << std::endl;

    std::cout << "Порядок числа обусловленности матрицы = " << conditionNumber << std::endl;
    
    std::cin.get();
}