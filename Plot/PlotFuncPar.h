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


#ifndef PLOTFUNCPAR_H
#define PLOTFUNCPAR_H


#include <iomanip>
#include <iostream>
#include <vector>


#include "FuncPar.h"


class PlotFuncPar {

public:

    PlotFuncPar(const FuncPar &rpcpPar);

    PlotFuncPar(const FuncPar &rpcpPar, const std::string &terminalPar);

    virtual ~PlotFuncPar();


    void setSysTerm(const bool &usingSysTermPar);


    void addDescription(const std::string &descriptionPlotPar);

    void clearDescription();


    void plotRPermRPermDer();

    void plotCPressCPressDer();

    void plotPsiPsiDer();


private:

    FuncPar fP;


    std::string terminal;


    std::vector<std::string> descriptionPlotArray;


    bool usingSysTerm;

};


#endif
