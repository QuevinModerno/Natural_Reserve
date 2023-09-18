cmake_minimum_required(VERSION 3.23)
project(TP)

set(CMAKE_CXX_STANDARD 14)

add_executable(TP Logic/TPpack/Cfiles/main.cpp Logic/TPpack/Cfiles/Simulator.cpp Logic/TPpack/Headers/Simulator.h Logic/TPpack/Cfiles/Reserve.cpp Logic/TPpack/Headers/Reserve.h Logic/TPpack/Headers/Animal.h Logic/TPpack/Cfiles/Animal.cpp Logic/TPpack/Headers/Food.h Logic/TPpack/Cfiles/Food.cpp Logic/TPpack/Cfiles/SimGUI.cpp Logic/TPpack/Headers/SimGUI.h Logic/TPpack/Headers/SaveState.h)
