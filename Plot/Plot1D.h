#ifndef PLOT1D_H
#define PLOT1D_H


#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


#include "StringAndNumber.h"
#include "Plot.h"


class Plot1D : public Plot {

public:

    Plot1D(const Grid &grdPar, const std::string &namePar);

    virtual ~Plot1D();


    void setX();

    void setY();

    void setSeriesIntOpt(const int &seriesIntOptPar);


private:


    void outPutData();


    void outPutPlotCommands();


    bool flagX;

    bool flagY;

};


#endif
