set curdir=%CD%

mkdir build\win64
cd build\win64

set BENCHMARK_INCLUDE_DIR=d:\projects\lib\benchmark\include
set FMT_INCLUDE_DIR=d:\projects\lib\fmt
set FASTFORMAT_INCLUDE_DIR=d:\projects\lib\fastformat-0.7.1\include
set STLSOFT_INCLUDE_DIR=d:\projects\lib\stlsoft-1.9.124\include
:: set STLSOFT_INCLUDE_DIR=d:\projects\lib\STLSoft-1.10-delta\include

cmake -G "Visual Studio 14 Win64" -T v140 ..\..

cd %curdir%
