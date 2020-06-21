#ifndef PLOTFUNCPAR_H
#define PLOTFUNCPAR_H


#include <iomanip>
#include <iostream>
#include <vector>


#include "FuncPar.h"


class PlotFuncPar {

public:

    PlotFuncPar(const FuncPar &rpcpPar);

    PlotFuncPar(const FuncPar &rpcpPar, const std::string &terminalPar);

    virtual ~PlotFuncPar();


    void setSysTerm(const bool &usingSysTermPar);


    void addDescription(const std::string &descriptionPlotPar);

    void clearDescription();


    void plotRPermRPermDer();

    void plotCPressCPressDer();

    void plotPsiPsiDer();


private:

    FuncPar fP;


    std::string terminal;


    std::vector<std::string> descriptionPlotArray;


    bool usingSysTerm;

};


#endif
