#ifndef LOCATION_H
#define LOCATION_H


#include "Grid.h"


#include <vector>


class Location {


public:

    Location(const Grid &grdPar, double &timeStepMaxPar, const std::string &dataFileName);

    virtual ~Location();


private:

    Grid grd;


    int dim;


    GetFromFile dataFile;


    double &timeStepMax;


    std::vector<double> alpha;

    void calcAlpha();


    void calcAF();


    void calcAC();


    std::vector<double> S;


public:

    double timeStepMult;


    double timeStep;


    std::vector<double> aF;


    std::vector<double> aC;


    void calcСoefficients(const std::vector<double> &SPar);

};


#endif
