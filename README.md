# Project Title
The C++ object-oriented programming demonstration of the numerical scheme splitting method. 


## Motivation

The crucial and sophisticated stage of basin modelling is the hydrodynamic simulation of hydrocarbon migration.
The most accurate and well-researched technique for this type of simulations is the Darcy based FVM model.
However, due to large time and spatial scales, this approach requires extensive computational effort.
The developed numerical scheme splitting (NSS) method allows to markedly decrease the computational time while maintaining the required accuracy.
This C++ project demonstrates the implementation of the above-mentioned NSS-method for a 2D case.
However, it is not a problem to use the developed model in 3D.


## Brief description
The following reservoir engineering problem is solved implementing FVM and NSS methods:

- two-phase incompressible Darcy flow (water and oil)
- buoyancy force and capillary attraction  
- two-dimensional cross-sectional grid system
- absolute permeability and porosity are constant
- source can be set arbitrary
- initial saturation can be set arbitrary
- no-flow boundary condition


## Getting Started

```
git clone https://github.com/AleksZhuravljov/nss
cd nss
mkdir build
cd build
cmake ..
cmake --build .
cd ../inOut
../build/nss data.txt
```
The file [data.txt](inOut/data.txt) with dependence files
 [fP.txt](inOut/fP.txt), [gridPars.txt](inOut/gridPars.txt) and
 [satIni.txt](inOut/satIni.txt) are intuitively understandable input data.
 The final output file of the default run is [Animation2D.gif](inOut/Animation2D.gif).

### Prerequisites

The libraries you need to install and how to install them

#### macOS:
```
brew install eigen
brew install cmake
brew install gnuplot
```
#### Ubuntu:
```
apt-get install eigen
apt-get install cmake
apt-get install gnuplot
```

## Authors

* [**Aleksandr Zhuravlyov**](https://github.com/AleksZhuravlyov/) and [**Zakhar Lanets**](https://github.com/lanetszb/)


## License

This project is licensed under the MIT License wich is a permissive free software license originating at the Massachusetts Institute of Technology (MIT) - see the [LICENSE](LICENSE) file for details
