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


#ifndef FUNCPAR_H
#define FUNCPAR_H


#include <cmath>
#include <string>


#include "GetFromFile.h"


class FuncPar {

public:

    FuncPar(const std::string &dataFileName);

    virtual ~FuncPar();


private:

    GetFromFile dataFile;

    GetFromFile fPFile;


    double Ac;

    double nc;


    double Aw;

    double nw;

    double muw;


    double Ao;

    double no;

    double muo;


public:

    double Swr;

    double rhow;


    double Sor;

    double rhoo;


    double cap(const double &S);


    double sigma(const double &S);


    double kw(const double &S);

    double ko(const double &S);


    double dkw(const double &S);

    double dko(const double &S);


    double psi(const double &Skw, const double &Sko);


    double varphi(const double &Skw, const double &Sko);

};


#endif
