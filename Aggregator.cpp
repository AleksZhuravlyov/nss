#include "Aggregator.h"


Aggregator::Aggregator(const std::string &dataFileName) : grd(dataFileName),
                                                          rpcp(dataFileName),
                                                          dataFile(dataFileName),
                                                          schemeType(dataFile.getWord<std::string>("SCHEME")),
                                                          schemeName(dataFile.getWord<std::string>("SCHEME", 1)),
                                                          convect(grd, rpcp, timeStepMax),
                                                          migrationTime(dataFile.getVector<double>("TIME")),
                                                          fileWithSini(dataFile.getWord<std::string>("SAT_INI_FILE")),
                                                          Sini(fileWithSini.getVector<double>("SAT_INI")),
                                                          relaxTime(dataFile.getWord<double>("RELAXATION_TIME")),
                                                          deformation(dataFile.getWord<int>("DEFORMATION")),
                                                          locate(grd, timeStepMax, dataFileName),
                                                          dim(grd.cellsV.size()),
                                                          aC(dim, 0), aF(dim, 0), aR(dim, 0), aL(dim, 0), aT(dim, 0), aB(dim, 0),
                                                          maxTolerance(dataFile.getWord<double>("MAX_TOLERANCE")),
                                                          Sold(dim, 0),
                                                          LE(poi, col, val, dim),
                                                          sourceCellIndex(dataFile.getVector<int>("SOURCE_CELL_INDEX")),
                                                          timeStepMult(locate.timeStepMult) {

    if (schemeType == "implicit")
        implicitFlag = true;
    else if (schemeType == "explicit")
        implicitFlag = false;

}

Aggregator::~Aggregator() {}


void Aggregator::saveResults(std::vector<std::vector<double> > &S, const std::vector<double> &ScurPar, const unsigned int &startTimeCalcPar) {

    S.push_back(ScurPar);

    oilVolume.push_back(0);
    for (int i = 0; i < S.back().size(); i++)
        oilVolume.back() += (1 - S.back()[i]) * grd.cellsV[i];
    oilVolume.back() /= S.back().size();

    calculationTime.push_back(1.E-6 * (clock() - startTimeCalcPar));

    numberTimeSteps.push_back(timeStepCount);


}


void Aggregator::aggregateAC() {
    for (int i = 0; i < grd.cellsV.size(); i++)
        aC[i] = locate.aC[i] + convect.aC[i];
}

void Aggregator::aggregateAF() {
    for (int i = 0; i < grd.cellsV.size(); i++)
        aF[i] = locate.aF[i] + convect.aF[i];
}

void Aggregator::aggregateAR() {
    for (int i = 0; i < grd.cellsV.size(); i++)
        aR[i] = convect.aR[i];
}

void Aggregator::aggregateAL() {
    for (int i = 0; i < grd.cellsV.size(); i++)
        aL[i] = convect.aL[i];
}

void Aggregator::aggregateAT() {
    for (int i = 0; i < grd.cellsV.size(); i++)
        aT[i] = convect.aT[i];
}

void Aggregator::aggregateAB() {
    for (int i = 0; i < grd.cellsV.size(); i++)
        aB[i] = convect.aB[i];
}


void Aggregator::aggregateСoefficients(const std::vector<double> &SPar) {

    aggregateAF();

    aggregateAC();

    aggregateAR();

    aggregateAL();

    aggregateAT();

    aggregateAB();

    aggregateMatrix();

    Sold = SPar;

}


void Aggregator::aggregateMatrix() {

    col.clear();
    poi.clear();
    val.clear();

    int j = 0;

    poi.push_back(j);

    for (int i = 0; i < grd.cellsV.size(); i++) {

        if (aB[i] != 0) {
            col.push_back(i - grd.cellsNumX);
            val.push_back(aB[i]);
            j++;
        }

        if (aL[i] != 0) {
            col.push_back(i - 1);
            val.push_back(aL[i]);
            j++;
        }

        if (aC[i] != 0) {
            col.push_back(i);
            val.push_back(aC[i]);
            j++;
        }

        if (aR[i] != 0) {
            col.push_back(i + 1);
            val.push_back(aR[i]);
            j++;
        }

        if (aT[i] != 0) {
            col.push_back(i + grd.cellsNumX);
            val.push_back(aT[i]);
            j++;
        }

        poi.push_back(j);

    }

}


void Aggregator::calcSaturation(std::vector<double> &S) {

    if (implicitFlag == true) {

        if (schemeName == "biConjugateGrSt")
            LE.calcBiConjugateGrSt(aF, S, Sold, maxTolerance);
        else if (schemeName == "conjugateGrLSq")
            LE.calcConjugateGrLSq(aF, S, Sold, maxTolerance);
        else if (schemeName == "supernodalLUFact")
            LE.calcSupernodalLUFact(aF, S);

    } else
        for (int i = 0; i < dim; i++)
            S[i] = -aF[i] / aC[i];


}


void Aggregator::calculate(std::vector<std::vector<double> > &S) {

    std::cout.precision(3);

    int widthCellOut = 22;

    std::cout.setf(std::ios::scientific, std::ios::floatfield);


    unsigned int startTimeCalc = clock();


    S.clear();


    convect.setImplicitFlag(implicitFlag);


    std::vector<std::vector<double>> Scurrent(2, Sini);


    std::cout << std::setw(widthCellOut) << "calculationPercents, %";
    std::cout << std::setw(widthCellOut) << "migrationTime, s";
    std::cout << std::setw(widthCellOut) << "calculationTime, s";
    std::cout << std::setw(widthCellOut) << "numberTimeSteps";;
    std::cout << std::endl;
    std::cout << std::endl;


    double timeCurrent = 0;

    int resultsOutCount = 0;

    int stageOutCount = 0;

    timeStepCount = 0;

    bool deformationFlag;

    if (migrationTime[resultsOutCount] == 0) {
        saveResults(S, Sini, startTimeCalc);
        resultsOutCount++;
    }

    do {

        deformationFlag = false;
        if (timeCurrent > relaxTime)
            if (deformation != 0)
                if (timeStepCount % deformation == 0)
                    deformationFlag = true;


        convect.calcСoefficients(Scurrent[timeStepCount % 2], deformationFlag);


        locate.calcСoefficients(Scurrent[timeStepCount % 2]);


        if ((timeCurrent + locate.timeStep) > migrationTime[resultsOutCount]) {

            timeStepMax = (migrationTime[resultsOutCount] - timeCurrent) / locate.timeStepMult;

            locate.calcСoefficients(Scurrent[timeStepCount % 2]);

        }


        aggregateСoefficients(Scurrent[timeStepCount % 2]);


        calcSaturation(Scurrent[(timeStepCount + 1) % 2]);


        for (int i = 0; i < sourceCellIndex.size(); i++)
            Scurrent[(timeStepCount + 1) % 2][sourceCellIndex[i]] = Sini[sourceCellIndex[i]];


        timeStepCount++;


        timeCurrent += locate.timeStep;


        if ((timeCurrent / migrationTime.back() * 100) >= stageOutCount) {
            std::cout << std::setw(widthCellOut) << timeCurrent / migrationTime.back() * 100;
            std::cout << std::setw(widthCellOut) << timeCurrent;
            std::cout << std::setw(widthCellOut) << 1.E-6 * (clock() - startTimeCalc);
            std::cout << std::setw(widthCellOut) << timeStepCount;
            std::cout << std::endl;
            stageOutCount = timeCurrent / migrationTime.back() * 100;
            stageOutCount++;
        }


        if (timeCurrent == migrationTime[resultsOutCount]) {
            saveResults(S, Scurrent[timeStepCount % 2], startTimeCalc);
            resultsOutCount++;
        }

    } while (timeCurrent < migrationTime.back());


    std::cout.unsetf(std::ios::floatfield);

}











