#!bin/bash

NAME=$1
BINARY_LOCATION=BinaryFiles/$NAME
DECODE_LOCATION=DecodedData/$NAME.root

cmsrun Sim-Out-Config.py

mv decodedData.root ./$DecodedData

./PixelEncoder/PixelEncoder ./$DecodedData

if [ ! -d "./$BINARY_LOCATION" ]; then
    mkdir ./$BINARY_LOCATION
fi

for p in SRAMhit0.bin SRAMhit1.bin SRAMhit2.bin SRAMpix0.bin SRAMpix1.bin SRAMpix2.bin histogram_source.pdf histogram_binary.pdf;
do
    mv $p ./$BINARY_LOCATION/$p
