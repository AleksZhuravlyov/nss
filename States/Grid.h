#ifndef GRID_H
#define GRID_H


#include <cmath>
#include <string>
#include <vector>


#include "GetFromFile.h"


class Grid {

public:

    Grid(const std::string &dataFileName);

    virtual ~Grid();


    GetFromFile dataFile;

    GetFromFile gridFile;


    double poro;


    double permX;

    double permY;


    double g;


    int nodesNumX;

    std::vector<double> nodesX;

    std::vector<double> nodesY;

    int nodesNumY;


    std::vector<double> surfsXL;

    std::vector<double> surfsYL;


    int surfsXNumX;

    int surfsXNumY;


    std::vector<double> surfsXX;

    std::vector<double> surfsXY;

    std::vector<double> surfsXOMEGA;


    int surfsYNumX;

    int surfsYNumY;


    std::vector<double> surfsYX;

    std::vector<double> surfsYY;

    std::vector<double> surfsYOMEGA;


    int cellsNumX;

    int cellsNumY;


    std::vector<double> cellsX;

    std::vector<double> cellsY;

    std::vector<double> cellsV;


    int iSurfXR(int iPar);

    int iSurfXL(int iPar);

    int iSurfYT(int iPar);

    int iSurfYB(int iPar);


    int iCellXR(int iPar);

    int iCellXL(int iPar);

    int iCellYT(int iPar);

    int iCellYB(int iPar);


private:

    void calcSurfsXL();

    void calcSurfsYL();


    void calcSurfsXParameters();

    void calcSurfsYParameters();


    void calcCellsParameters();

};


#endif
