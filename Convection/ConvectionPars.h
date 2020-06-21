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


#ifndef CONVECTIONPARS_H
#define CONVECTIONPARS_H


#include <vector>


#include "Grid.h"
#include "FuncPar.h"


class ConvectionPars {

public:

    ConvectionPars(const Grid &grdPar, const FuncPar &fPPar);

    virtual ~ConvectionPars();


protected:

    Grid grd;


    FuncPar fP;


    int dimX;

    int dimY;


    std::vector<double> DELTAnX;

    std::vector<double> DELTAnY;


    std::vector<double> SX;

    std::vector<double> SY;


    std::vector<double> varepsX;

    std::vector<double> varepsY;


    std::vector<double> psiX;

    std::vector<double> psiY;


    std::vector<double> deltaX;

    std::vector<double> deltaY;


    std::vector<double> epsilonX;

    std::vector<double> epsilonY;


    std::vector<double> varphiX;

    std::vector<double> varphiY;


    std::vector<double> zetaX;

    std::vector<double> zetaY;


    std::vector<double> gammaX;

    std::vector<double> gammaY;


    std::vector<double> betaX;

    std::vector<double> betaY;


    std::vector<double> S;

    void calcPars(const std::vector<double> &SPar);


private:

    void calcDELTAnX();

    void calcDELTAnY();


    void calcSX();

    void calcSY();


    void calcVarepsX();

    void calcVarepsY();


    void calcPsiXVarepsX();

    void calcPsiYVarepsY();


    void calcDeltaX();

    void calcDeltaY();


    void calcEpsilonX();

    void calcEpsilonY();


    void calcZetaX();

    void calcZetaY();


    void calcGammaX();

    void calcGammaY();


    void calcBetaX();

    void calcBetaY();

};


#endif