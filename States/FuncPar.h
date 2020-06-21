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
