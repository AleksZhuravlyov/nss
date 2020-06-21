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

    int splittingDegree;


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
