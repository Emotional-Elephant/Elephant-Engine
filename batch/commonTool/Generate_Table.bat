set CURPATH=%cd%
cd ../../Elephant_Engine/binary/gamebase-win-x64/
CommonTool.exe gen table --target-path ../../../Data/csv --output ../../../Data/output
cd %CURPATH%
PAUSE