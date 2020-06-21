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
