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


#ifndef STRINGANDNUMBER_H
#define STRINGANDNUMBER_H


#include <string>
#include <sstream>


template<typename T>
std::string toString(T val) {
    std::ostringstream oss;
    oss << val;
    return oss.str();
}


template<typename T>
std::string toString(T val, const int &widthCellOut, const int &prec, const bool &scientificFlag) {

    std::ostringstream oss;

    oss.precision(prec);

    if (scientificFlag)
        oss.setf(std::ios::scientific, std::ios::floatfield);
    else
        oss.setf(std::ios::fixed, std::ios::floatfield);

    oss << std::setw(widthCellOut) << val;

    return oss.str();

}


template<typename T>
T fromString(const std::string &s) {
    std::istringstream iss(s);
    T res;
    iss >> res;
    return res;
}


#endif


/*
std::string str;

int iVal;

float fVal;


str = toString(iVal);

str = toString(fVal);


iVal = fromString<int>(str);

fVal = fromString<float>(str);
*/
