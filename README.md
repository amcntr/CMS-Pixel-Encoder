## CMS Pixel Encoder Package

A set of programs that will convert CMS Monte Carlo run data into a binary format for FED testing with a GLIB.

### Setup

Runs on CMSSW_10_1_1. Untested on other versions of CMSSW.

To compile the the required code, run ```compile.sh``` or ```bash compile.sh```

You then need to modify ```/MCHitAnalyzer/python/Sim-Out-Config.py``` ```line 31``` to target the run data you want to convert.

### How to run

Run ```run.sh <name>``` or ```bash run.sh <name>```

This will first run cmsrun to pull the pixel hit data from the source, then PixelEncoder to convert the pixel data into the binary files.

The binary files will be stored in the ```BinaryFiles/<name>/``` directory and the pixel hit data will be stored in the DecodedData directory.

### Binary Files

Details on the binary files can be found in the README.md inside the PixelEncoder directory.
