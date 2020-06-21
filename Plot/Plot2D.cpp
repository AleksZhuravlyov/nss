#include "Plot2D.h"


Plot2D::Plot2D(const Grid &grdPar, const std::string &namePar) : Plot(grdPar, namePar) {

    defaultDescriptionPlotArray.push_back("set pm3d map corners2color c1");

    defaultDescriptionPlotArray.push_back("set key outside");

    defaultDescriptionPlotArray.push_back("set cntrparam levels auto 7");

    defaultDescriptionPlotArray.push_back("set xlabel 'X, m'");

    defaultDescriptionPlotArray.push_back("set ylabel 'Y, m'");

}

Plot2D::~Plot2D() {}


void Plot2D::outPutData() {

    // definition of minValueArray and maxValueArray:

    std::vector<double> minValueArray;
    std::vector<double> maxValueArray;

    double currentValue = 0;

    for (int i = 0; i < seriesArray.size(); i++) {

        minValueArray.push_back(0);
        maxValueArray.push_back(0);

        minValueArray[i] = seriesArray[i][0];
        maxValueArray[i] = seriesArray[i][0];

        for (int j = 0; j < seriesArray[i].size(); j++) {

            currentValue = seriesArray[i][j];

            if (minValueArray[i] > currentValue)
                minValueArray[i] = currentValue;

            if (maxValueArray[i] < currentValue)
                maxValueArray[i] = currentValue;

        }
    }


    // definition of modSeriesArray:

    int NumX = 0;

    std::vector<double> coordinateX;
    std::vector<double> coordinateY;

    std::vector<double> modSeries; // temporary modified series

    std::vector<std::vector<double>> modSeriesArray; // modified series array


    for (int i = 0; i < seriesArray.size(); i++) {
        modSeries.clear();

        for (int j = 0; j < seriesArray[i].size(); j++) {

            modSeries.push_back(seriesArray[i][j]);

            if (flagCellsArray[i])
                if ((j + 1) % grd.cellsNumX == 0)
                    modSeries.push_back(minValueArray[i]);

        }

        if (flagCellsArray[i])
            for (int j = 0; j < grd.cellsNumX + 1; j++)
                modSeries.push_back(minValueArray[i]);

        modSeriesArray.push_back(modSeries);

    }


    // out put series to data files:

    std::ofstream dataStream;

    dataStream.precision(5);

    int widthCellOut = 14;

    dataStream.setf(std::ios::scientific, std::ios::floatfield);

    std::string fileDataName;

    for (int i = 0; i < modSeriesArray.size(); i++) {

        // definition of NumX, coordinateX and coordinateY:

        if (flagSurfsXArray[i]) {

            NumX = grd.surfsXNumX;

            coordinateX = grd.surfsXX;
            coordinateY = grd.surfsXY;

        } else if (flagSurfsYArray[i]) {

            NumX = grd.surfsYNumX;

            coordinateX = grd.surfsYX;
            coordinateY = grd.surfsYY;

        } else {

            NumX = grd.nodesNumX;

            coordinateX = grd.nodesX;
            coordinateY = grd.nodesY;
        }


        fileDataName = name + toString(i) + ".txt";

        dataStream.open(fileDataName.c_str());

        for (int j = 0; j < modSeriesArray[i].size(); j++) {

            dataStream << std::setw(widthCellOut) << coordinateX[j];
            dataStream << std::setw(widthCellOut) << coordinateY[j];
            dataStream << std::setw(widthCellOut) << modSeriesArray[i][j] << std::endl;

            if ((j + 1) % NumX == 0)
                dataStream << std::endl;

        }

        dataStream.close();

    }

}


void Plot2D::outPutPlotCommands() {


    std::ofstream pltStream;

    std::string filePlotName;

    filePlotName = name + ".plt";

    pltStream.open(filePlotName.c_str(), std::ios::app);

    std::string fileDataName;


    pltStream << "splot\\" << std::endl;

    for (int i = 0; i < seriesArray.size(); i++) {

        fileDataName = name + toString(i) + ".txt";

        if (i > 0)
            pltStream << ",\\" << std::endl;
        pltStream << "'" << fileDataName << "' ";

        if (seriesDescriptionArray[i] == "")
            if (flagCellsArray[i])
                pltStream << "notitle";
            else
                pltStream << "with point ps 2 pt 7 palette notitle";
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


