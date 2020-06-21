#include "PlotFuncPar.h"


PlotFuncPar::PlotFuncPar(const FuncPar &rpcpPar) : fP(rpcpPar), terminal(""), usingSysTerm(true) {}

PlotFuncPar::PlotFuncPar(const FuncPar &rpcpPar, const std::string &terminalPar) : fP(rpcpPar), terminal(terminalPar),
                                                                                               usingSysTerm(true) {}

PlotFuncPar::~PlotFuncPar() {}


void PlotFuncPar::setSysTerm(const bool &usingSysTermPar) {
    usingSysTerm = usingSysTermPar;
}


void PlotFuncPar::addDescription(const std::string &descriptionPlotPar) {
    descriptionPlotArray.push_back(descriptionPlotPar);
}

void PlotFuncPar::clearDescription() {
    descriptionPlotArray.clear();
}


void PlotFuncPar::plotRPermRPermDer() {

    std::string name = "RPermRPermDer";

    std::ofstream outStream;

    std::string dataPlotFile = name + ".txt";

    outStream.open(dataPlotFile.c_str());

    outStream.precision(3);

    outStream.setf(std::ios::scientific, std::ios::floatfield);

    int widthCellOut = 12;

    outStream << std::setw(widthCellOut) << "name" << std::setw(widthCellOut) << "k_w" << std::setw(widthCellOut) << "k_o" << std::setw(10)
              << "k'_w"
              << std::setw(widthCellOut)
              << "k'_o"
              << std::endl;

    double S = 0;

    for (int i = 0; i <= 100; i++) {

        S = 0.01 * i;

        outStream << std::setw(widthCellOut) << S << std::setw(widthCellOut) << fP.kw(S) << std::setw(widthCellOut) << fP.ko(S)
                  << std::setw(widthCellOut) << fP.dko(S)
                  << std::setw(widthCellOut) << fP.dkw(S)
                  << std::endl;

    }

    outStream.close();

    std::string pltPlotFile = name + ".plt";

    outStream.open(pltPlotFile.c_str());

    if (terminal != "")
        outStream << "set term " << terminal << std::endl << "set output '" << name << "." << terminal << "'" << std::endl;

    for (int i = 0; i < descriptionPlotArray.size(); i++)
        outStream << descriptionPlotArray[i] << std::endl;

    outStream << "set key font \",14\"" << std::endl;
    outStream << "set tics font \",10\"" << std::endl;
    outStream << "set xlabel \'S_w\' font \",12\"" << std::endl;
    outStream << "set ylabel \'k_r\' font \",12\"" << std::endl;
    outStream << "set y2label \"k'_r\" font \",12\"" << std::endl;
    outStream << "set xrange [0:1]" << std::endl;
    outStream << "set yrange [0:1]" << std::endl;
    outStream << "set ytics" << std::endl;
    outStream << "set y2tics" << std::endl;
    outStream << "plot '" << dataPlotFile << "' using 1:2 w l lw 2 ti col,\\" << std::endl;
    outStream << "'" << dataPlotFile << "' using 1:3 w l lw 2 ti col,\\" << std::endl;
    outStream << "'" << dataPlotFile << "' using 1:4 axes x1y2 w l lw 2 ti col,\\" << std::endl;
    outStream << "'" << dataPlotFile << "' using 1:5 axes x1y2 w l lw 2 ti col" << std::endl;

    outStream.close();

    std::string command = "gnuplot ";

    if (terminal == "")
        command += pltPlotFile + " &";
    else
        command += pltPlotFile + "; open " + name + "." + terminal;

    if (usingSysTerm == true)
        std::cout << system(command.c_str());
    else
        std::cout << command << std::endl;

}


void PlotFuncPar::plotCPressCPressDer() {

    std::string name = "CPressCPressDer";

    std::ofstream outStream;

    std::string dataPlotFile = name + ".txt";

    outStream.open(dataPlotFile.c_str());

    outStream.precision(3);

    outStream.setf(std::ios::scientific, std::ios::floatfield);

    int widthCellOut = 12;

    outStream << std::setw(widthCellOut) << "name" << std::setw(widthCellOut) << "p_c" << std::setw(widthCellOut) << "p'_c" << std::endl;

    double S = 0;

    for (int i = 0; i <= 100; i++) {

        S = 0.01 * i;

        outStream << std::setw(widthCellOut) << S << std::setw(widthCellOut) << fP.cap(S) << std::setw(widthCellOut) << fP.sigma(S)
                  << std::endl;

    }

    outStream.close();

    std::string pltPlotFile = name + ".plt";

    outStream.open(pltPlotFile.c_str());

    if (terminal != "")
        outStream << "set term " << terminal << std::endl << "set output '" << name << "." << terminal << "'" << std::endl;

    for (int i = 0; i < descriptionPlotArray.size(); i++)
        outStream << descriptionPlotArray[i] << std::endl;

    outStream << "set key font \",14\"" << std::endl;
    outStream << "set tics font \",10\"" << std::endl;
    outStream << "set xlabel \'S_w\' font \",12\"" << std::endl;
    outStream << "set ylabel \'p_c\' font \",12\"" << std::endl;
    outStream << "set y2label \"p'_c\" font \",12\"" << std::endl;
    outStream << "set xrange [0:1]" << std::endl;
    outStream << "set ytics" << std::endl;
    outStream << "set y2tics" << std::endl;
    outStream << "plot '" << dataPlotFile << "' using 1:2 w l lw 2 ti col,\\" << std::endl;
    outStream << "'" << dataPlotFile << "' using 1:3 axes x1y2 w l lw 2 ti col" << std::endl;

    outStream.close();

    std::string command = "gnuplot ";

    if (terminal == "")
        command += pltPlotFile + " &";
    else
        command += pltPlotFile + "; open " + name + "." + terminal;

    if (usingSysTerm == true)
        std::cout << system(command.c_str());
    else
        std::cout << command << std::endl;

}

void PlotFuncPar::plotPsiPsiDer() {

    std::string name = "PsiPsiDer";

    std::ofstream outStream;

    std::string dataPlotFile = name + ".txt";

    outStream.open(dataPlotFile.c_str());

    outStream.precision(3);

    outStream.setf(std::ios::scientific, std::ios::floatfield);

    int widthCellOut = 12;

    outStream << std::setw(widthCellOut) << "name" << std::setw(widthCellOut) << "psi" << std::setw(widthCellOut) << "psi'" << std::endl;

    double S = 0;

    for (int i = 0; i <= 100; i++) {

        S = 0.01 * i;

        outStream << std::setw(widthCellOut) << S << std::setw(widthCellOut) << fP.psi(S, S) << std::setw(widthCellOut) << fP.varphi(S, S)
                  << std::endl;

    }

    outStream.close();

    std::string pltPlotFile = name + ".plt";

    outStream.open(pltPlotFile.c_str());

    if (terminal != "")
        outStream << "set term " << terminal << std::endl << "set output '" << name << "." << terminal << "'" << std::endl;

    for (int i = 0; i < descriptionPlotArray.size(); i++)
        outStream << descriptionPlotArray[i] << std::endl;

    outStream << "set key font \",14\"" << std::endl;
    outStream << "set tics font \",10\"" << std::endl;
    outStream << "set xlabel \'S_w\' font \",12\"" << std::endl;
    outStream << "set ylabel \'psi\' font \",12\"" << std::endl;
    outStream << "set y2label \"psi'\" font \",12\"" << std::endl;
    outStream << "set xrange [0:1]" << std::endl;
    outStream << "set ytics" << std::endl;
    outStream << "set y2tics" << std::endl;
    outStream << "plot '" << dataPlotFile << "' using 1:2 w l lw 2 ti col,\\" << std::endl;
    outStream << "'" << dataPlotFile << "' using 1:3 axes x1y2 w l lw 2 ti col" << std::endl;

    outStream.close();

    std::string command = "gnuplot ";

    if (terminal == "")
        command += pltPlotFile + " &";
    else
        command += pltPlotFile + "; open " + name + "." + terminal;

    if (usingSysTerm == true)
        std::cout << system(command.c_str());
    else
        std::cout << command << std::endl;

}





