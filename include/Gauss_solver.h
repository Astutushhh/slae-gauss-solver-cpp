// gauss_solver.h
#pragma once

#include <eigen3/Eigen/Dense>


class GaussForwardElimination {
    public:
        Eigen::MatrixXd forwardElimination(Eigen::MatrixXd A) const;
    private:
        void isMatrixSingular(Eigen::MatrixXd& A, int matrixLength) const;
        void avoidIncreasingErr(Eigen::MatrixXd& A, int i, int matrixLength) const;
        void subtractNormolizedRow(Eigen::MatrixXd& A, int i, int matrixLength) const;
};

class GaussBackwardSubstitution {
    public:
        Eigen::VectorXd backwardSubstitution(Eigen::MatrixXd& U) const;
    private:
        double rowCalc(Eigen::RowVectorXd row, Eigen::VectorXd solution, int rowLen) const;
};

class GaussSolver {
    public:
        GaussSolver(Eigen::MatrixXd& A, Eigen::VectorXd& b);

        Eigen::VectorXd solve();
        double absFirstResidualNorm();
        double absInfiniteResidualNorm();
        
        double getAbsErrorBoundFirst();
        double getAbsErrorBoundInf();

        double getRelErrorBoundFirst();
        double getRelErrorBoundInf();


        double conditionNumber();       
                
    private:
        void checkMatrix(const Eigen::MatrixXd& A) const;
        void prepRectMatrixIfItsNeed(Eigen::MatrixXd& A) const;

        void checkDimensions(const Eigen::MatrixXd& A, const Eigen::VectorXd& b) const;
        Eigen::MatrixXd makeAugmentedMatrix(const Eigen::MatrixXd& A, const Eigen::VectorXd& b) const;

        void solutionExists() const;
        void absFirstNormExist() const;
        void absInfNormExist() const;

        void condNumExist() const;

        void calcResidual();

        void relFirstResidualNorm();
        void relInfiniteResidualNorm();

        Eigen::MatrixXd augmented_;
        Eigen::MatrixXd A_;
        Eigen::VectorXd b_;
        Eigen::VectorXd solution_;
        Eigen::VectorXd residual_;
        double absFirstNorm_;
        double absInfiniteNorm_;

        double absErrorBoundFirst_;
        double absErrorBoundInfinite_;

        double relErrorBoundFirst_;
        double relErrorBoundInfinite_;

        double condNum_;

        GaussForwardElimination forward_;
        GaussBackwardSubstitution backward_;

        bool solved_ = false;
        bool absFirstNormBool_ = false;
        bool absInftNormBool_ = false;
        bool condNumBool_ = false;
};