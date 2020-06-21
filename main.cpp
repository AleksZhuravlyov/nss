#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "Aggregator.h"
#include "GetFromFile.h"
#include "StringAndNumber.h"
#include "Plot1D.h"
#include "Plot2D.h"
#include "PlotFuncPar.h"


int main(int narg, char **arg) {

    // block 1 - log
    // block 2 - Plot1D
    // block 3 - Plot2D
    // block 4 - AnimationPlot2D, change MigrationTimeIntervals and their number (it doesn't work without block 3)
    // block 5 - PlotFuncPar



    Aggregator example(arg[1]);


    // block 4
    //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

    double migrationTimeMax = example.migrationTime.back();

    example.migrationTime.clear();

    int numMigrationTimeIntervals = 50;

    for (int i = 0; i < numMigrationTimeIntervals + 1; i++)
        example.migrationTime.push_back(migrationTimeMax / numMigrationTimeIntervals * i);

    //↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑



    std::vector<std::vector<double>> S;


    std::cout << std::endl;
    std::cout << "start" << std::endl;
    std::cout << std::endl;

    example.calculate(S);

    std::cout << std::endl;
    std::cout << "finish" << std::endl;
    std::cout << std::endl;



    // block 1
    //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

    example.logOut(std::cout);

    std::string logFileName = "log.txt";
    std::ofstream streamOut;
    streamOut.open(logFileName.c_str());
    example.logOut(streamOut);
    streamOut.close();

    //↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑



    // block 5
/*
    //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

    PlotFuncPar testPlotFP(example.rpcp, "png");

    testPlotFP.setSysTerm(true);

    testPlotFP.addDescription("set term png size 700,500");

    testPlotFP.plotPsiPsiDer();

    testPlotFP.plotCPressCPressDer();

    testPlotFP.plotRPermRPermDer();

    //↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
*/


    // block 3
    //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

    std::string nameFile;
    std::string decription;


    for (int i = 0; i < S.size(); i++) {

        nameFile = "saturation.2D." + toString(i);
        Plot2D testPlot2D(example.grd, nameFile);

        testPlot2D.addSeries(S[i]);
        testPlot2D.setCells();

        decription = "set title \"";
        decription += "migrTime:" + toString(example.migrationTime[i], 10, 2, true) + " s";
        decription += " || calcTime:" + toString(example.calculationTime[i], 10, 2, true) + " s";
        decription += " || oilVolume:" + toString(example.oilVolume[i], 10, 2, true) + " m2";
        decription += " || numTimeSteps:" + toString(example.numberTimeSteps[i], 7, 0, false) + " steps";
        decription += "\\n\"";

        testPlot2D.addDescription(decription);


        decription = "set label 1 at  7355, 6 '" + example.schemeName + "'";

        testPlot2D.addDescription(decription);


        decription = "set label 2 at  7355, 4 'timeStepMult:  " + toString(example.timeStepMult) + "'";

        testPlot2D.addDescription(decription);


        decription = "set label 3 at  7300, 2 ' deformation:  " + toString(example.deformation) + "'";

        testPlot2D.addDescription(decription);


        testPlot2D.addDescription("set cbrange [0:1]");
        testPlot2D.addDescription("set xrange [0:10000]");
        testPlot2D.addDescription("set cblabel 'saturation'");

        testPlot2D.setTerminal("png");
        testPlot2D.setTermOptions("size 900,450");

        testPlot2D.setSysTerm(false);
        testPlot2D.make();

    }

    //↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑



    // block 4
    //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

    std::string Animation2DFileName = "Animation2D.plt";
    streamOut.open(Animation2DFileName.c_str());

    streamOut << "set term gif \\" << std::endl;
    streamOut << "  animate \\" << std::endl;
    streamOut << "  optimize \\" << std::endl;
    streamOut << "  delay 15 \\" << std::endl;
    streamOut << "  size 1600, 800 \\" << std::endl;
    streamOut << "  background \"white\"" << std::endl;
    streamOut << std::endl;
    streamOut << "set output \"Animation2D.gif\"" << std::endl;
    streamOut << std::endl;
    streamOut << "set pm3d map corners2color c1" << std::endl;
    streamOut << "set key outside" << std::endl;
    streamOut << "set cntrparam levels auto 7" << std::endl;
    streamOut << "set xlabel 'X, m'" << std::endl;
    streamOut << "set ylabel 'Y, m'" << std::endl;
    streamOut << "set title '0 s'" << std::endl;
    streamOut << "set cbrange [0:1]" << std::endl;
    streamOut << "set xrange [0:10000]" << std::endl;
    streamOut << "set cblabel 'saturation'" << std::endl;
    streamOut << std::endl;

    streamOut.precision(2);
    streamOut.setf(std::ios::scientific, std::ios::floatfield);


    decription = "set label 1 at  7355, 6 '" + example.schemeName + "'";

    streamOut << decription << std::endl;


    decription = "set label 2 at  7355, 4 'timeStepMult:  " + toString(example.timeStepMult) + "'";

    streamOut << decription << std::endl;


    decription = "set label 3 at  7300, 2 ' deformation:  " + toString(example.deformation) + "'";

    streamOut << decription << std::endl;


    for (int i = 0; i < S.size(); i++) {

        decription = "set title \"";
        decription += "migrTime:" + toString(example.migrationTime[i], 10, 2, true) + " s";
        decription += " || calcTime:" + toString(example.calculationTime[i], 10, 2, true) + " s";
        decription += " || oilVolume:" + toString(example.oilVolume[i], 10, 2, true) + " m2";
        decription += " || numTimeSteps:" + toString(example.numberTimeSteps[i], 7, 0, false) + " steps";
        decription += "\\n\"";

        streamOut << decription << std::endl;

        nameFile = "saturation.2D." + toString(i) + "0.txt";
        streamOut << "splot '" << nameFile << "' notitle" << std::endl;

    }
    streamOut.unsetf(std::ios::floatfield);

    streamOut.close();

    std::cout << system("gnuplot Animation2D.plt") << std::endl;


    std::string command;

    /*for (int i = 0; i < S.size(); i++) {
        command = "rm ";
        command += "saturation.2D." + toString(i) + "0.txt";
        std::cout << system(command.c_str()) << std::endl;
    }

    for (int i = 0; i < S.size(); i++) {
        command = "rm ";
        command += "saturation.2D." + toString(i) + ".plt";
        std::cout << system(command.c_str()) << std::endl;
    }

    command = "rm Animation2D.plt";
    std::cout << system(command.c_str()) << std::endl;*/

    // std::cout << system("open -a safari Animation2D.gif") << std::endl;

    //↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑



    // block 2
/*
    //↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

    Plot1D testPlot1D(example.grd, "saturation.1D.");
    testPlot1D.setY();
    std::string lineDescription;

    for (int i = 0; i < S.size(); i++) {
        lineDescription = "with linespoints lw 2 pt 7 ti '";
        lineDescription += toString(example.migrationTime[i]);
        lineDescription += " s'";
        testPlot1D.addSeries(S[i], lineDescription);
        testPlot1D.setCells();
        testPlot1D.setSeriesIntOpt(7);
    }

    testPlot1D.setTerminal("png");
    testPlot1D.setTermOptions("size 450,550");
    testPlot1D.setSysTerm(true);
    testPlot1D.make();

    //↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
*/


    return 0;
}