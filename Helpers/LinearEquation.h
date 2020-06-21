/* MIT License
 *
 * Copyright (c) 2020 Aleksandr Zhuravlyov and Zakhar Lanets
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#ifndef LINEAREQUATION_H
#define LINEAREQUATION_H


#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>


#include <Eigen/Sparse>


class LinearEquation {

public:

    LinearEquation(std::vector<int> &poi, std::vector<int> &col, std::vector<double> &val, const int &dimPar);

    virtual ~LinearEquation();


private:

    std::vector<int> &poi;

    std::vector<int> &col;

    std::vector<double> &val;


    int dim;


    std::vector<Eigen::Triplet<double>> coefficients;


    Eigen::SparseMatrix<double> matrix;

    void fillMatrix();


    Eigen::VectorXd X0;

    void fillX0(const std::vector<double> &X0Par);


    Eigen::VectorXd F;

    void fillF(const std::vector<double> &FPar);


    Eigen::VectorXd X;

    void outX(std::vector<double> &XPar);


    void setMaxTolerance(const double &maxTolerance);


    Eigen::BiCGSTAB<Eigen::SparseMatrix<double>> biConjugateGrSt;


    Eigen::LeastSquaresConjugateGradient<Eigen::SparseMatrix<double>> conjugateGrLSq;


    Eigen::SparseLU<Eigen::SparseMatrix<double>> supernodalLUFact;


public:

    void calcBiConjugateGrSt(const std::vector<double> &FPar, std::vector<double> &XPar,
                             const std::vector<double> &X0Par, const double &maxTolerance);


    void calcConjugateGrLSq(const std::vector<double> &FPar, std::vector<double> &XPar,
                            const std::vector<double> &X0Par, const double &maxTolerance);


    void calcSupernodalLUFact(const std::vector<double> &FPar, std::vector<double> &XPar);


};


#endif