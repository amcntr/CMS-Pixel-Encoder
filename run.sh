#!bin/bash

NAME=$1
BINARY_LOCATION=BinaryFiles/$NAME
DECODE_LOCATION=DecodedData/$NAME.root

if [ -z "$VAR" ]; then
    echo
    echo Use: run.sh \<name\>
    echo
else
if [ ! -d "./DecodedData" ]; then
    mkdir DecodedData
fi

if [ ! -d "./$BINARY_LOCATION" ]; then
    mkdir ./$BINARY_LOCATION
fi

echo
echo Pulling pixel data from source files.
echo ================================================================
echo

cd ./MCHitAnalyzer/python

cmsRun Sim-Out-Config.py

echo
echo Moving Decoded Data into $DECODE_LOCATION 
echo

mv decodedData.root ../../$DECODE_LOCATION

cd ../../

echo
echo Converting pulled data to binary.
echo ================================================================
echo

./PixelEncoder/PixelEncoder ./$DECODE_LOCATION

for p in SRAMhit0.bin SRAMhit1.bin SRAMhit2.bin SRAMpix0.bin SRAMpix1.bin SRAMpix2.bin histogram_source.pdf histogram_binary.pdf;
do
    mv $p ./$BINARY_LOCATION/$p
done

echo
echo 
echo Done converting data. Binary files are located in $BINARY_LOCATION
echo ================================================================
echo
fi 
