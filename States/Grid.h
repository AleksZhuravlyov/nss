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
