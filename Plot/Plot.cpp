#include "Plot.h"

Plot::Plot(const Grid &grd, const std::string &namePar) : grd(grd), name(namePar), terminal(""), usingSysTerm(false) {}

Plot::~Plot() {}


void Plot::setCells() {

    flagCellsArray.back() = true;
    flagSurfsXArray.back() = false;
    flagSurfsYArray.back() = false;

}

void Plot::setSurfsX() {

    flagCellsArray.back() = false;
    flagSurfsXArray.back() = true;
    flagSurfsYArray.back() = false;

}

void Plot::setSurfsY() {

    flagCellsArray.back() = false;
    flagSurfsXArray.back() = false;
    flagSurfsYArray.back() = true;

}


void Plot::addSeries(const std::vector<double> &seriesPar) {

    seriesArray.push_back(seriesPar);
    seriesDescriptionArray.push_back("");
    seriesIntOptArray.push_back(0);

    flagCellsArray.push_back(true);
    flagSurfsXArray.push_back(false);
    flagSurfsYArray.push_back(false);

}

void Plot::addSeries(const std::vector<double> &seriesPar, const std::string &seriesDescriptionPar) {

    seriesArray.push_back(seriesPar);
    seriesDescriptionArray.push_back(seriesDescriptionPar);
    seriesIntOptArray.push_back(0);

    flagCellsArray.push_back(true);
    flagSurfsXArray.push_back(false);
    flagSurfsYArray.push_back(false);

}


void Plot::clearSeries() {

    seriesArray.clear();
    seriesDescriptionArray.clear();
    seriesIntOptArray.clear();

    flagCellsArray.clear();
    flagSurfsXArray.clear();
    flagSurfsYArray.clear();

}


void Plot::addDescription(const std::string &descriptionPlotPar) {
    descriptionPlotArray.push_back(descriptionPlotPar);
}

void Plot::clearDescription() {
    descriptionPlotArray.clear();
}


void Plot::addDefaultDescription(const std::string &defaultDescriptionPlotPar) {
    defaultDescriptionPlotArray.push_back(defaultDescriptionPlotPar);
}


void Plot::setTerminal(const std::string &terminalPar) {
    terminal = terminalPar;
}

void Plot::clearTerminal() {
    terminal = "";
    termOptions = "";
}


void Plot::setTermOptions(const std::string &termOptionsPar) {
    termOptions = termOptionsPar;
}

void Plot::clearTermOptions() {
    termOptions = "";
}


void Plot::setSysTerm(const bool &usingSysTermPar) {
    usingSysTerm = usingSysTermPar;
}


void Plot::make() {

    outPutDescription();

    outPutData();

    outPutPlotCommands();

}


void Plot::outPutDescription() {

    std::ofstream pltStream;

    std::string filePlotName;
    filePlotName = name + ".plt";

    pltStream.open(filePlotName.c_str());

    if (terminal != "") {
        pltStream << "set term " << terminal;
        if (termOptions != "")
            pltStream << " " << termOptions;
        pltStream << std::endl << "set output '" << name << "." << terminal << "'" << std::endl;
    }

    for (int i = 0; i < defaultDescriptionPlotArray.size(); i++)
        pltStream << defaultDescriptionPlotArray[i] << std::endl;

    for (int i = 0; i < descriptionPlotArray.size(); i++)
        pltStream << descriptionPlotArray[i] << std::endl;

    pltStream.close();

}




