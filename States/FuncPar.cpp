#include "FuncPar.h"


FuncPar::FuncPar(const std::string &dataFileName) : dataFile(dataFileName),
                                                    fPFile(dataFile.getWord<std::string>("FP_FILE")),

                                                    Ac(fPFile.getWord<double>("Ac")),
                                                    nc(fPFile.getWord<double>("nc")),

                                                    Aw(fPFile.getWord<double>("Aw")),
                                                    nw(fPFile.getWord<double>("nw")),
                                                    muw(fPFile.getWord<double>("viscWater")),

                                                    Ao(fPFile.getWord<double>("Ao")),
                                                    no(fPFile.getWord<double>("no")),
                                                    muo(fPFile.getWord<double>("viscOil")),


                                                    Swr(fPFile.getWord<double>("Swr")),
                                                    rhow(fPFile.getWord<double>("densWater")),

                                                    Sor(fPFile.getWord<double>("Sor")),
                                                    rhoo(fPFile.getWord<double>("densOil")) {}


FuncPar::~FuncPar() {}


double FuncPar::cap(const double &S) {
    return Ac * std::pow(1. - S, nc);
}


double FuncPar::sigma(const double &S) {
    return -nc * Ac * std::pow(1. - S, nc - 1);
}


double FuncPar::kw(const double &S) {
    if (S < Swr)
        return 0;
    else if (S > 1. - Sor)
        return Aw;
    else
        return Aw * std::pow((S - Swr) / (1. - Swr - Sor), nw);
}

double FuncPar::ko(const double &S) {
    if (S < Swr)
        return Ao;
    else if (S > 1. - Sor)
        return 0;
    else
        return Ao * std::pow((1. - S - Sor) / (1. - Swr - Sor), no);
}


double FuncPar::dkw(const double &S) {
    if (S < Swr)
        return 0;
    else if (S > 1. - Sor)
        return 0;
    else
        return nw * Aw * std::pow((S - Swr), (nw - 1.)) / std::pow((1. - Swr - Sor), (2. * nw - 2.));
}

double FuncPar::dko(const double &S) {
    if (S < Swr)
        return 0;
    else if (S > 1. - Sor)
        return 0;
    else
        return -no * Ao * std::pow((1. - S - Sor), (no - 1.)) / std::pow((1. - Swr - Sor), (2. * no - 2.));
}


double FuncPar::psi(const double &Skw, const double &Sko) {
    return kw(Skw) * ko(Sko) / (muo * kw(Skw) + muw * ko(Sko));
}


double FuncPar::varphi(const double &Skw, const double &Sko) {
    return (muw * dkw(Skw) * ko(Sko) * ko(Sko) + muo * dko(Sko) * kw(Skw) * kw(Skw)) / std::pow((muo * kw(Skw) + muw * ko(Sko)), 2.);
}


