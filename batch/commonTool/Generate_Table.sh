#!/bin/bash
CUR_DIR=$(pwd)
echo $CUR_DIR
cd ../../Tool/gamebase/binary/gamebase-osx.10.11-x64/
./gamebase gen table --target-path ../../../../Gamebase/Dev/Data --output ../../../../Gamebase/Dev/Output
cd $CUR_DIR