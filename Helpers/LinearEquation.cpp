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


#include "LinearEquation.h"


LinearEquation::LinearEquation(std::vector<int> &poi, std::vector<int> &col,
                               std::vector<double> &val, const int &dimPar) : dim(dimPar),
                                                                              poi(poi), col(col), val(val),
                                                                              matrix(dim, dim),
                                                                              X0(dim), F(dim), X(dim) {}

LinearEquation::~LinearEquation() {}


void LinearEquation::fillMatrix() {

    coefficients.clear();

    for (int i = 0; i < poi.size() - 1; i++)
        for (int j = poi[i]; j < poi[i + 1]; j++)
            coefficients.push_back(Eigen::Triplet<double>(i, col[j], val[j]));

    matrix.setZero();

    matrix.setFromTriplets(coefficients.begin(), coefficients.end());

}


void LinearEquation::fillF(const std::vector<double> &FPar) {

    for (int i = 0; i < dim; i++)
        F[i] = -FPar[i];

}


void LinearEquation::fillX0(const std::vector<double> &X0Par) {

    for (int i = 0; i < dim; i++)
        X0[i] = X0Par[i];

}


void LinearEquation::outX(std::vector<double> &XPar) {

    XPar.clear();

    for (int i = 0; i < dim; i++)
        XPar.push_back(X[i]);

}


void LinearEquation::setMaxTolerance(const double &maxTolerance) {

    if (maxTolerance != 0)
        conjugateGrLSq.setTolerance(maxTolerance);

}


void LinearEquation::calcBiConjugateGrSt(const std::vector<double> &FPar, std::vector<double> &XPar, const std::vector<double> &X0Par,
                                         const double &maxTolerance) {
    fillMatrix();

    setMaxTolerance(maxTolerance);

    biConjugateGrSt.compute(matrix);

    fillF(FPar);

    fillX0(X0Par);

    X = biConjugateGrSt.solveWithGuess(F, X0);

    outX(XPar);

}


void LinearEquation::calcConjugateGrLSq(const std::vector<double> &FPar, std::vector<double> &XPar, const std::vector<double> &X0Par,
                                        const double &maxTolerance) {

    fillMatrix();

    setMaxTolerance(maxTolerance);

    conjugateGrLSq.compute(matrix);

    fillF(FPar);

    fillX0(X0Par);

    X = conjugateGrLSq.solveWithGuess(F, X0);

    outX(XPar);

}


void LinearEquation::calcSupernodalLUFact(const std::vector<double> &FPar, std::vector<double> &XPar) {

    fillMatrix();

    supernodalLUFact.compute(matrix);

    fillF(FPar);

    X = supernodalLUFact.solve(F);

    outX(XPar);

}