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


#ifndef GETFROMFILE_H
#define GETFROMFILE_H


#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>


class GetFromFile {

public:

    GetFromFile(const std::string &fileName) : fileName(fileName) {};

    virtual ~GetFromFile() {};


    template<typename T>
    T getWord(const std::string &variableKey, const int &count);

    template<typename T>
    T getWord(const std::string &variableKey);

    template<typename T>
    std::vector<T> getVector(const std::string &variableKey);


private:

    std::string fileName;

};


template<typename T>
T GetFromFile::getWord(const std::string &variableKey, const int &count) {

    T variable;

    std::ifstream inStream;

    inStream.open(fileName.c_str());

    std::string word;

    while (inStream >> word)
        if (word == variableKey)
            break;

    for (int i = 0; i < count; i++)
        inStream >> word;

    inStream >> variable;

    inStream.close();

    return variable;

}


template<typename T>
T GetFromFile::getWord(const std::string &variableKey) {

    return getWord<T>(variableKey, 0);

}


template<typename T>
std::vector<T> GetFromFile::getVector(const std::string &variableKey) {

    std::vector<T> variable;

    std::ifstream inStream;

    inStream.open(fileName.c_str());

    std::string word;

    while (inStream >> word)
        if (word == variableKey)
            break;

    std::stringstream sStream;

    while (inStream >> word)
        if (word != "\\")
            sStream << word << std::endl;
        else
            break;

    inStream.close();

    T clipboard;

    while (sStream >> clipboard)
        variable.push_back(clipboard);

    return variable;

}

#endif
