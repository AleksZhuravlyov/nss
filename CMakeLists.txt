cmake_minimum_required(VERSION 3.15)

project(nss)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)

include_directories(. States Location Convection Plot Helpers)

set(SOURCE_FILES main.cpp Aggregator.cpp
        States/Grid.cpp States/Grid.cpp States/FuncPar.cpp
        Location/Location.cpp
        Convection/ConvectionPars.cpp Convection/Convection.cpp
        Plot/Plot.cpp Plot/Plot1D.cpp Plot/Plot2D.cpp Plot/PlotFuncPar.cpp
        Helpers/MatrixOperations.cpp Helpers/LinearEquation.cpp)

add_executable(nss ${SOURCE_FILES})
target_link_libraries(nss Eigen3::Eigen)