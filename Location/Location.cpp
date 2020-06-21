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


#include "Location.h"


Location::Location(const Grid &grdPar, double &timeStepMaxPar,
                   const std::string &dataFileName) : grd(grdPar),
                                                      dim(grdPar.cellsV.size()),
                                                      dataFile(dataFileName),
                                                      timeStepMax(timeStepMaxPar),
                                                      alpha(dim, 0),
                                                      timeStepMult(dataFile.getWord<double>("TIME_STEP_MULT")),
                                                      aF(dim, 0),
                                                      aC(dim, 0) {}

Location::~Location() {}


void Location::calcAlpha() {
    for (int i = 0; i < dim; i++)
        alpha[i] = grd.poro * grd.cellsV[i];
}


void Location::calcAF() {
    for (int i = 0; i < dim; i++)
        aF[i] = -alpha[i] / timeStep * S[i];
}


void Location::calcAC() {
    for (int i = 0; i < grd.cellsV.size(); i++)
        aC[i] = alpha[i] / timeStep;
}


void Location::calcСoefficients(const std::vector<double> &SPar) {
    timeStep = timeStepMax * timeStepMult;
    S = SPar;
    calcAlpha();
    calcAF();
    calcAC();

}