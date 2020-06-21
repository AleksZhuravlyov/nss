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


#include "MatrixOperations.h"


MatrixOperations::MatrixOperations(std::vector<int> &poi, std::vector<int> &col, std::vector<double> &val) : poi(poi), col(col), val(val) {}

MatrixOperations::~MatrixOperations() {}


void MatrixOperations::vectorMult(std::vector<double> &result, const std::vector<double> &param) {

    for (int i = 0; i < poi.size() - 1; i++) {

        result[i] = 0;

        for (int j = poi[i]; j < poi[i + 1]; j++)
            result[i] += val[j] * param[col[j]];

    }

}


double MatrixOperations::elementVectorMult(const std::vector<double> &param, const int &iPar) {

    double result = 0;

    for (int j = poi[iPar]; j < poi[iPar + 1]; j++)
        result += val[j] * param[col[j]];

    return result;

}


void MatrixOperations::getDiagonal(std::vector<double> &result) {

    for (int i = 0; i < poi.size() - 1; i++) {

        result[i] = 0;

        for (int j = poi[i]; j < poi[i + 1]; j++)
            if (i == col[j])
                result[i] = val[j];

    }

}


