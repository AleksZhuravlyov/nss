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


#include "ConvectionPars.h"


ConvectionPars::ConvectionPars(const Grid &grdPar, const FuncPar &fPPar) : grd(grdPar),
                                                                                 fP(fPPar),
                                                                                 dimX(grdPar.surfsXOMEGA.size()),
                                                                                 dimY(grdPar.surfsYOMEGA.size()),
                                                                                 DELTAnX(dimX, 0), DELTAnY(dimY, 0),
                                                                                 SX(dimX, 0), SY(dimY, 0),
                                                                                 varphiX(dimX, 0), varphiY(dimY, 0),
                                                                                 psiX(dimX, 0), psiY(dimY, 0),
                                                                                 deltaX(dimX, 0), deltaY(dimY, 0),
                                                                                 epsilonX(dimX, 0), epsilonY(dimY, 0),
                                                                                 varepsX(dimX, 0), varepsY(dimY, 0),
                                                                                 zetaX(dimX, 0), zetaY(dimY, 0),
                                                                                 gammaX(dimX, 0), gammaY(dimY, 0),
                                                                                 betaX(dimX, 0), betaY(dimY, 0) {}

ConvectionPars::~ConvectionPars() {}


void ConvectionPars::calcPars(const std::vector<double> &SPar) {

    S = SPar;

    calcSX();
    calcSY();

    calcVarepsX();
    calcVarepsY();

    calcDELTAnX();
    calcDELTAnY();

    calcEpsilonX();
    calcEpsilonY();

    calcZetaX();
    calcZetaY();

    calcPsiXVarepsX();
    calcPsiYVarepsY();

    calcBetaX();
    calcBetaY();

    calcGammaX();
    calcGammaY();

    calcDeltaX();
    calcDeltaY();

}


void ConvectionPars::calcDELTAnX() {

    for (int i = 0; i < dimX; i++)
        if (i % grd.surfsXNumX == 0 || (i + 1) % grd.surfsXNumX == 0)
            DELTAnX[i] = 0;
        else
            DELTAnX[i] = (S[grd.iCellXR(i)] - S[grd.iCellXL(i)]) / grd.surfsXL[i];

}

void ConvectionPars::calcDELTAnY() {

    for (int i = 0; i < dimY; i++)
        if (i < grd.surfsYNumX || i >= grd.surfsYNumX * (grd.surfsYNumY - 1))
            DELTAnY[i] = 0;
        else
            DELTAnY[i] = (S[grd.iCellYT(i)] - S[grd.iCellYB(i)]) / grd.surfsYL[i];

}


void ConvectionPars::calcSX() {

    for (int i = 0; i < dimX; i++)
        if (i % grd.surfsXNumX == 0)
            SX[i] = S[grd.iCellXR(i)];
        else if ((i + 1) % grd.surfsXNumX == 0)
            SX[i] = S[grd.iCellXL(i)];
        else
            SX[i] = (S[grd.iCellXR(i)] + S[grd.iCellXL(i)]) / 2;

}

void ConvectionPars::calcSY() {

    for (int i = 0; i < dimY; i++)
        if (i < grd.surfsYNumX)
            SY[i] = S[grd.iCellYT(i)];
        else if (i >= grd.surfsYNumX * (grd.surfsYNumY - 1))
            SY[i] = S[grd.iCellYB(i)];
        else
            SY[i] = (S[grd.iCellYT(i)] + S[grd.iCellYB(i)]) / 2;

}


void ConvectionPars::calcVarepsX() {

    for (int i = 0; i < dimX; i++)
        varepsX[i] = fP.sigma(SX[i]) * grd.surfsXOMEGA[i];
}

void ConvectionPars::calcVarepsY() {

    for (int i = 0; i < dimY; i++)
        varepsY[i] = fP.sigma(SY[i]) * grd.surfsYOMEGA[i];
}


void ConvectionPars::calcPsiXVarepsX() {

    for (int i = 0; i < dimX; i++)
        if (zetaX[i] < 0 && (S[grd.iCellXL(i)] < 1 - fP.Sor && S[grd.iCellXR(i)] > fP.Swr))
            if (fP.kw(S[grd.iCellXR(i)]) == 0 || fP.ko(S[grd.iCellXL(i)]) == 0) {
                psiX[i] = 0;
                varphiX[i] = 0;
            } else {
                psiX[i] = fP.psi(S[grd.iCellXR(i)], S[grd.iCellXL(i)]);
                varphiX[i] = fP.varphi(S[grd.iCellXR(i)], S[grd.iCellXL(i)]);
            }
        else if (zetaX[i] > 0 && (S[grd.iCellXR(i)] < 1 - fP.Sor && S[grd.iCellXL(i)] > fP.Swr))
            if (fP.kw(S[grd.iCellXL(i)]) == 0 || fP.ko(S[grd.iCellXR(i)]) == 0) {
                psiX[i] = 0;
                varphiX[i] = 0;
            } else {
                psiX[i] = fP.psi(S[grd.iCellXL(i)], S[grd.iCellXR(i)]);
                varphiX[i] = fP.varphi(S[grd.iCellXL(i)], S[grd.iCellXR(i)]);
            }
        else {
            psiX[i] = 0;
            varphiX[i] = 0;
        }
}

void ConvectionPars::calcPsiYVarepsY() {

    for (int i = 0; i < dimY; i++)
        if (zetaY[i] < 0 && (S[grd.iCellYB(i)] < 1 - fP.Sor && S[grd.iCellYT(i)] > fP.Swr))
            if (fP.kw(S[grd.iCellYT(i)]) == 0 || fP.ko(S[grd.iCellYB(i)]) == 0) {
                psiY[i] = 0;
                varphiY[i] = 0;
            } else {
                psiY[i] = fP.psi(S[grd.iCellYT(i)], S[grd.iCellYB(i)]);
                varphiY[i] = fP.varphi(S[grd.iCellYT(i)], S[grd.iCellYB(i)]);
            }
        else if (zetaY[i] > 0 && (S[grd.iCellYT(i)] < 1 - fP.Sor && S[grd.iCellYB(i)] > fP.Swr))
            if (fP.kw(S[grd.iCellYB(i)]) == 0 || fP.ko(S[grd.iCellYT(i)]) == 0) {
                psiY[i] = 0;
                varphiY[i] = 0;
            } else {
                psiY[i] = fP.psi(S[grd.iCellYB(i)], S[grd.iCellYT(i)]);
                varphiY[i] = fP.varphi(S[grd.iCellYB(i)], S[grd.iCellYT(i)]);
            }
        else {
            psiY[i] = 0;
            varphiY[i] = 0;
        }
}


void ConvectionPars::calcDeltaX() {

    for (int i = 0; i < dimX; i++)
        if (psiX[i] == 0)
            deltaX[i] = 0;
        else deltaX[i] = grd.permX * psiX[i] * epsilonX[i];
}

void ConvectionPars::calcDeltaY() {

    for (int i = 0; i < dimY; i++)
        if (psiY[i] == 0)
            deltaY[i] = 0;
        else deltaY[i] = grd.permY * psiY[i] * epsilonY[i];
}


void ConvectionPars::calcEpsilonX() {

    for (int i = 0; i < dimX; i++)
        if (i % grd.surfsXNumX == 0 || (i + 1) % grd.surfsXNumX == 0)
            epsilonX[i] = 0;
        else
            epsilonX[i] = (fP.rhow - fP.rhoo) * grd.g * (grd.cellsY[grd.iCellXR(i)] - grd.cellsY[grd.iCellXL(i)]) / grd.surfsXL[i] *
                          grd.surfsXOMEGA[i];

}

void ConvectionPars::calcEpsilonY() {

    for (int i = 0; i < dimY; i++)
        if (i < grd.surfsYNumX || i >= grd.surfsYNumX * (grd.surfsYNumY - 1))
            epsilonY[i] = 0;
        else
            epsilonY[i] = (fP.rhow - fP.rhoo) * grd.g * (grd.cellsY[grd.iCellYT(i)] - grd.cellsY[grd.iCellYB(i)]) / grd.surfsYL[i] *
                          grd.surfsYOMEGA[i];

}


void ConvectionPars::calcZetaX() {

    for (int i = 0; i < dimX; i++)
        zetaX[i] = varepsX[i] * DELTAnX[i] + epsilonX[i];
}

void ConvectionPars::calcZetaY() {

    for (int i = 0; i < dimY; i++)
        zetaY[i] = varepsY[i] * DELTAnY[i] + epsilonY[i];
}


void ConvectionPars::calcGammaX() {

    for (int i = 0; i < dimX; i++)
        if (varphiX[i] == 0)
            gammaX[i] = 0;
        else gammaX[i] = grd.permX * varphiX[i] * epsilonX[i];

}

void ConvectionPars::calcGammaY() {

    for (int i = 0; i < dimY; i++)
        if (varphiY[i] == 0)
            gammaY[i] = 0;
        else gammaY[i] = grd.permY * varphiY[i] * epsilonY[i];
}


void ConvectionPars::calcBetaX() {

    for (int i = 0; i < dimX; i++)
        if (psiX[i] == 0)
            betaX[i] = 0;
        else betaX[i] = grd.permX * psiX[i] * varepsX[i];
}

void ConvectionPars::calcBetaY() {

    for (int i = 0; i < dimY; i++)
        if (psiY[i] == 0)
            betaY[i] = 0;
        else betaY[i] = grd.permY * psiY[i] * varepsY[i];
}