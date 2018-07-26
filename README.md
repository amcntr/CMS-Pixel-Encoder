## CMS Pixel Encoder Package

A set of programs that will convert CMS run data into a binary format for FED testing with a GLIB.

### Setup

To compile the programs run ```compile.sh``` or ```bash compile.sh```

This will compile all the required code and setup a link to the proper config files.

You then need to modify ```/MCHitAnalyzer/python/Sim-Out-Config.py``` line 31 to target the source data you want to convert.

### How to run

Run ```run.sh <name of data>``` or ```bash run.sh <name of data>```

This will first run cmsrun to pull the pixel hit data from the source, then PixelEncoder to convert the pixel data into the binary files.

The binary files will be stored in the BinaryFiles directory and the pixel hit data is stored in the ```DecodedData/<name of data>/``` directory.

## Binary Files

Details on the binary files can be found in the README.md inside the PixelEncoder directory.
