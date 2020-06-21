#ifndef AGGREGATOR_H
#define AGGREGATOR_H


#include <ctime>
#include <iomanip>
#include <iostream>


#include "Convection.h"
#include <Eigen/Sparse>
#include "LinearEquation.h"
#include "Location.h"


class Aggregator {

public:

    Aggregator(const std::string &dataFileName);

    virtual ~Aggregator();


    Grid grd;


    FuncPar rpcp;


private:


    GetFromFile dataFile;


    std::string schemeType;


public:

    std::string schemeName;


private:

    double timeStepMax;


    bool implicitFlag;


    Convection convect;


public:

    std::vector<double> migrationTime;


private:


    GetFromFile fileWithSini;

    std::vector<double> Sini;


    long long int timeStepCount;


public:

    std::vector<double> oilVolume;

    std::vector<double> calculationTime;

    std::vector<long long int> numberTimeSteps;


private:

    void saveResults(std::vector<std::vector<double> > &S, const std::vector<double> &ScurPar, const unsigned int &startTimeCalcPar);


    double relaxTime;


public:

    int deformation;


private:

    Location locate;


    int dim;


    std::vector<double> aC;

    void aggregateAC();


    std::vector<double> aF;

    void aggregateAF();


    std::vector<double> aR;

    void aggregateAR();


    std::vector<double> aL;

    void aggregateAL();


    std::vector<double> aT;

    void aggregateAT();


    std::vector<double> aB;

    void aggregateAB();


    void aggregateСoefficients(const std::vector<double> &SPar);


    double maxTolerance;


    std::vector<double> Sold;


    std::vector<int> poi;

    std::vector<int> col;

    std::vector<double> val;

    void aggregateMatrix();


public:

    LinearEquation LE;


private:

    std::vector<int> sourceCellIndex;


    void calcSaturation(std::vector<double> &S);


public:

    void calculate(std::vector<std::vector<double> > &S);


    template<class T>
    void logOut(T &outPut);


    double timeStepMult;

};


template<class T>
void Aggregator::logOut(T &outPut) {

    outPut << "schemeName: " << schemeName << std::endl;
    outPut << std::endl;

    outPut.precision(4);
    int widthCellOut = 22;


    outPut << std::setw(widthCellOut) << "migrationTime, s";
    outPut << std::setw(widthCellOut) << "calculationTime, s";
    outPut << std::setw(widthCellOut) << "numberTimeSteps";
    outPut << std::setw(widthCellOut) << "oilVolume, m2";
    outPut << std::endl;
    outPut << std::endl;

    outPut.setf(std::ios::scientific, std::ios::floatfield);
    for (int i = 0; i < migrationTime.size(); i++) {

        outPut << std::setw(widthCellOut) << migrationTime[i];
        outPut << std::setw(widthCellOut) << calculationTime[i];
        outPut << std::setw(widthCellOut) << numberTimeSteps[i];
        outPut << std::setw(widthCellOut) << oilVolume[i];
        outPut << std::endl;

    }
    outPut.unsetf(std::ios::floatfield);
}


#endif
