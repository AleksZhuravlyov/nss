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


#ifndef CONVECTION_H
#define CONVECTION_H


#include "ConvectionPars.h"


class Convection : public ConvectionPars {

public:

    Convection(Grid &grdPar, FuncPar &RPCPPar, double &timeStepMaxPar);

    virtual ~Convection();

private:

    int dim;

    bool deformationFlag;


    std::vector<double> fluxExplX;

    std::vector<double> fluxExplY;

    void calcfluxExplX();

    void calcfluxExplY();


    std::vector<double> divergence;

    void calcDivergence(const std::vector<double> &SPar);


    double &timeStepMax;

    std::vector<double> timeStepMaxCurrent;

    void calcTimeStepMax();


    bool implicitFlag;


public:

    void setImplicitFlag(const bool &implicitFlagPar);


private:


    std::vector<double> aSurfXR;

    std::vector<double> aSurfXL;

    std::vector<double> aSurfXF;

    void calcASurfX();


    std::vector<double> aSurfYT;

    std::vector<double> aSurfYB;

    std::vector<double> aSurfYF;

    void calcASurfY();


    void calcA();


public:


    std::vector<double> aF;

    std::vector<double> aC;

    std::vector<double> aR;

    std::vector<double> aL;

    std::vector<double> aT;

    std::vector<double> aB;


    void calcСoefficients(const std::vector<double> &SPar, const bool &deformationFlagPar);


};


#endif
