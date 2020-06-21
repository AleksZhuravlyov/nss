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
