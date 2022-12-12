set CURPATH=%cd%
cd ../../source/binary/gamebase-win-x64/
CommonTool.exe gen table --target-path ../../../data/csv --output ../../../Data/output
cd %CURPATH%
PAUSE