#ifndef PLOT2D_H
#define PLOT2D_H


#include <iomanip>


#include "Plot.h"
#include "StringAndNumber.h"


class Plot2D : public Plot {

public:

    Plot2D(const Grid &grdPar, const std::string &namePar);

    virtual ~Plot2D();


private:

    void outPutData();


    void outPutPlotCommands();

};


#endif
