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