# DUT Program Design
Information Management System during COVID-19 Pandemic

This is a Simple Library Management System, written in C++ with the support of SQLite and Nomango/configor.

The project is built pass on following environment: 

|OS|GCC|Clang|MSVC|
|--|--|--|--|
|Ubuntu 18.04|✔️|✔️|N/A|
|Ubuntu 20.04|✔️|✔️|N/A|
|macOS 10.15|✔️|✔️|N/A|
|macOS 11|✔️|✔️|N/A|
|Windows 2019|✔️(MinGW)|N/A|✔️|
|Windows 2022|✔️(MinGW)|N/A|✔️|

## Licence
BSD-3

## Getting Started
CMakeFile.txt has already been congifured, therefore simply specify compiler with CMake CLI Parameter and run `cmake --build`.
Then, copy .csv file in data_example directory into the same directory.
**If OS is Windows, re-encode the .csv file with ANSI encoding.**
