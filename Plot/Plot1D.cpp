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


#include "Plot1D.h"


Plot1D::Plot1D(const Grid &grdPar, const std::string &namePar) : Plot(grdPar, namePar), flagX{true}, flagY{false} {}

Plot1D::~Plot1D() {}


void Plot1D::setX() {

    flagX = true;
    flagY = false;

}

void Plot1D::setY() {

    flagX = false;
    flagY = true;

}


void Plot1D::setSeriesIntOpt(const int &seriesIntOptPar) {
    seriesIntOptArray.back() = seriesIntOptPar;
}


void Plot1D::outPutData() {


    int NumX = 0;

    std::vector<double> coordinate;

    bool flagPut = false;


    std::ofstream dataStream;

    dataStream.precision(5);

    int widthCellOut = 14;

    dataStream.setf(std::ios::scientific, std::ios::floatfield);

    std::string fileDataName;

    for (int i = 0; i < seriesArray.size(); i++) {

        // Definition of NumX and coordinate:

        if (flagCellsArray[i]) {

            NumX = grd.cellsNumX;

            if (flagX)
                coordinate = grd.cellsX;
            else if (flagY)
                coordinate = grd.cellsY;

        } else if (flagSurfsXArray[i]) {

            NumX = grd.surfsXNumX;

            if (flagX)
                coordinate = grd.surfsXX;
            else if (flagY)
                coordinate = grd.surfsXY;

        } else {

            NumX = grd.surfsYNumX;

            if (flagX)
                coordinate = grd.surfsYX;
            else if (flagY)
                coordinate = grd.surfsYY;

        }


        fileDataName = name + toString(i) + ".txt";

        dataStream.open(fileDataName.c_str());

        for (int j = 0; j < seriesArray[i].size(); j++) {

            flagPut = false;

            if (flagX && (j >= NumX * seriesIntOptArray[i] && j < NumX * (seriesIntOptArray[i] + 1)))
                flagPut = true;
            else if (flagY && (j - seriesIntOptArray[i]) % NumX == 0)
                flagPut = true;

            if (flagPut)
                dataStream << std::setw(widthCellOut) << coordinate[j] << std::setw(widthCellOut) << seriesArray[i][j] << std::endl;

        }

        dataStream.close();

    }

}


void Plot1D::outPutPlotCommands() {

    std::ofstream pltStream;

    std::string filePlotName;

    filePlotName = name + ".plt";

    pltStream.open(filePlotName.c_str(), std::ios::app);

    std::string fileDataName;

    pltStream << "plot\\" << std::endl;

    for (int i = 0; i < seriesArray.size(); i++) {

        fileDataName = name + toString(i) + ".txt";

        if (i > 0)
            pltStream << ",\\" << std::endl;
        pltStream << "'" << fileDataName << "' using 1:2 ";

        if (seriesDescriptionArray[i] == "")
            pltStream << "with linespoints lw 2 pt 7 ti " << "'" << fileDataName << "'";
        else
            pltStream << seriesDescriptionArray[i];
    }

    if (terminal == "")
        pltStream << std::endl << "pause mouse close";

    pltStream.close();

    std::string command = "gnuplot ";

    if (terminal == "")
        command += filePlotName + " &";
    else
        command += filePlotName + "; open " + name + "." + terminal;

    std::cout << std::endl;

    if (usingSysTerm == true)
        std::cout << system(command.c_str());
    else
        std::cout << command << std::endl;

}





