#!bin/bash

echo
echo Compiling MCHitAnalyzer with scram...
echo ================================================================
echo

cd ./MCHitAnalyzer
scram b

echo
echo Compiling PixelEncoder with g++...
echo ================================================================
echo

cd ../PixelEncoder
make

cd ..

echo
echo Done compiling. Ready to run.
echo
