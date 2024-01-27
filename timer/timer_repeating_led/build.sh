#!/usr/bin/env bash

ROOTDIR=`pwd`
CONFIGS="debug release"

PICO_BOARD=adafruit_feather_rp2040

for CONFIG in $CONFIGS; do
    BUILDFOLDER=$ROOTDIR/build/$CONFIG
    #DISTFOLDER=$ROOTDIR/dist/$CONFIG

    mkdir -p $BUILDFOLDER #$DISTFOLDER    

    cd $BUILDFOLDER

    cmake -DPICO_BOARD=$PICO_BOARD -DCMAKE_BUILD_TYPE=$CONFIG $ROOTDIR || exit 1

    make
    #make install

done
