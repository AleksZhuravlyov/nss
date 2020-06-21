#ifndef PLOT_H
#define PLOT_H


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


#include "Grid.h"


class Plot {

public:

    Plot(const Grid &grdPar, const std::string &namePar);

    virtual ~Plot();


    void setCells();

    void setSurfsX();

    void setSurfsY();


    void addSeries(const std::vector<double> &seriesPar);

    void addSeries(const std::vector<double> &seriesPar,
                   const std::string &seriesDescriptionPar);

    void clearSeries();


    void addDescription(const std::string &descriptionPlotPar);

    void clearDescription();


    void addDefaultDescription(const std::string &defaultDescriptionPlotPar);


    void setTerminal(const std::string &terminalPar);

    void clearTerminal();


    void setTermOptions(const std::string &termOptionsPar);

    void clearTermOptions();


    void setSysTerm(const bool &usingSysTermPar);


    void make();


protected:

    Grid grd;


    std::string name;


    std::vector<bool> flagCellsArray;

    std::vector<bool> flagSurfsXArray;

    std::vector<bool> flagSurfsYArray;


    std::vector<std::vector<double>> seriesArray;

    std::vector<std::string> seriesDescriptionArray;


    std::vector<std::string> descriptionPlotArray;

    std::vector<std::string> defaultDescriptionPlotArray;


    std::string terminal;

    std::string termOptions;


    bool usingSysTerm;


    std::vector<int> seriesIntOptArray;


    void outPutDescription();


    virtual void outPutData() {}


    virtual void outPutPlotCommands() {}


};


#endif
