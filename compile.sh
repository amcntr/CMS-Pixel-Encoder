#!bin/bash

cd ./MCHitAnalyzer
scram b

cd ../PixelEncoder
make

cd ..

ln ./MCHitAnalyzer/python/Sim-Out-Config.py Sim-Out-Config.py
