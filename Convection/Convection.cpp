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


#include "Convection.h"


Convection::Convection(Grid &grdPar, FuncPar &RPCPPar, double &timeStepMaxPar) : ConvectionPars(grdPar, RPCPPar),
                                                                                     dim(grdPar.cellsV.size()),
                                                                                     fluxExplX(dimX, 0), fluxExplY(dimY, 0),
                                                                                     divergence(dim, 0),
                                                                                     timeStepMax(timeStepMaxPar),
                                                                                     aSurfXR(dimX, 0), aSurfXL(dimX, 0), aSurfXF(dimX, 0),
                                                                                     aSurfYT(dimY, 0), aSurfYB(dimY, 0), aSurfYF(dimY, 0),
                                                                                     aF(dim, 0),
                                                                                     aC(dim, 0),
                                                                                     aR(dim, 0),
                                                                                     aL(dim, 0),
                                                                                     aT(dim, 0),
                                                                                     aB(dim, 0) {}

Convection::~Convection() {}


void Convection::calcfluxExplX() {
    for (int i = 0; i < dimX; i++)
        fluxExplX[i] = betaX[i] * DELTAnX[i] + deltaX[i];
}

void Convection::calcfluxExplY() {
    for (int i = 0; i < dimY; i++)
        fluxExplY[i] = betaY[i] * DELTAnY[i] + deltaY[i];
}


void Convection::calcDivergence(const std::vector<double> &SPar) {

    calcPars(SPar);

    calcfluxExplX();
    calcfluxExplY();


    for (int i = 0; i < dim; i++)
        divergence[i] = fluxExplX[grd.iSurfXR(i)] - fluxExplX[grd.iSurfXL(i)] + fluxExplY[grd.iSurfYT(i)] - fluxExplY[grd.iSurfYB(i)];

    if (deformationFlag == true)
        for (int i = 0; i < dim; i++)
            divergence[i] = fluxExplX[grd.iSurfXR(i)] - fluxExplX[grd.iSurfXL(i)];

}


void Convection::calcTimeStepMax() {

    timeStepMaxCurrent.clear();

    for (int i = 0; i < grd.cellsX.size(); i++) {
        if (divergence[i] < 0)
            timeStepMaxCurrent.push_back((S[i] - 1. + fP.Sor) * grd.cellsV[i] * grd.poro / divergence[i]);
        else if (divergence[i] > 0)
            timeStepMaxCurrent.push_back((S[i] - fP.Swr) * grd.cellsV[i] * grd.poro / divergence[i]);
    }

    timeStepMax = timeStepMaxCurrent[0];
    for (int i = 0; i < timeStepMaxCurrent.size(); i++)
        if (timeStepMax > timeStepMaxCurrent[i])
            timeStepMax = timeStepMaxCurrent[i];

}


void Convection::setImplicitFlag(const bool &implicitFlagPar) {
    implicitFlag = implicitFlagPar;
}


void Convection::calcASurfX() {

    for (int i = 0; i < dimX; i++) {

        aSurfXR[i] = gammaX[i] / 2. + betaX[i] / grd.surfsXL[i];
        aSurfXL[i] = gammaX[i] / 2. - betaX[i] / grd.surfsXL[i];
        aSurfXF[i] = deltaX[i] - gammaX[i] * SX[i];

    }

}

void Convection::calcASurfY() {

    for (int i = 0; i < dimY; i++) {

        aSurfYT[i] = gammaY[i] / 2. + betaY[i] / grd.surfsYL[i];
        aSurfYB[i] = gammaY[i] / 2. - betaY[i] / grd.surfsYL[i];
        aSurfYF[i] = deltaY[i] - gammaY[i] * SY[i];

    }
}


void Convection::calcA() {

    if (implicitFlag == false)

        for (int i = 0; i < dim; i++) {

            aF[i] = divergence[i];
            aC[i] = 0;
            aR[i] = 0;
            aL[i] = 0;
            aT[i] = 0;
            aB[i] = 0;

        }

    else {

        calcASurfX();
        calcASurfY();

        for (int i = 0; i < grd.cellsX.size(); i++) {

            aF[i] = aSurfXF[grd.iSurfXR(i)] - aSurfXF[grd.iSurfXL(i)] + aSurfYF[grd.iSurfYT(i)] - aSurfYF[grd.iSurfYB(i)];
            aC[i] = aSurfXL[grd.iSurfXR(i)] - aSurfXR[grd.iSurfXL(i)] + aSurfYB[grd.iSurfYT(i)] - aSurfYT[grd.iSurfYB(i)];
            aR[i] = aSurfXR[grd.iSurfXR(i)];
            aL[i] = -aSurfXL[grd.iSurfXL(i)];
            aT[i] = aSurfYT[grd.iSurfYT(i)];
            aB[i] = -aSurfYB[grd.iSurfYB(i)];

        }

        if (deformationFlag == true)
            for (int i = 0; i < grd.cellsX.size(); i++) {

                aF[i] = aSurfXF[grd.iSurfXR(i)] - aSurfXF[grd.iSurfXL(i)];
                aC[i] = aSurfXL[grd.iSurfXR(i)] - aSurfXR[grd.iSurfXL(i)];
                aR[i] = aSurfXR[grd.iSurfXR(i)];
                aL[i] = -aSurfXL[grd.iSurfXL(i)];
                aT[i] = 0;
                aB[i] = 0;

            }

    }

}


void Convection::calcСoefficients(const std::vector<double> &SPar, const bool &deformationFlagPar) {

    deformationFlag = deformationFlagPar;

    calcDivergence(SPar);

    calcTimeStepMax();

    calcA();

}