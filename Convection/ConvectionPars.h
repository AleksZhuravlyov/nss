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