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
