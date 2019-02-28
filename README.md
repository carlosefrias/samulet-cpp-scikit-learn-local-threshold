# This project attempts to find alternatives to the opencv adaptive threshold #

## Those attemps include ##

- Wrapping python scikit-learn threshold_local method to c++
- Use the c++ generated code from the MATLAB adaptive threshold method

## Dev environment setup (Guess it can be optimized) ##

## Opencv ##

- add the folder ...opencv\build\x64\vc15\bin to your path environment variables
- add the folder ...opencv\build\include to the list of additional include directories under C/C++ -> General project properties
- add the folder ...opencv\build\x64\vc15\lib to the list of additional libraries directories under Linker -> General project properties
- add opencv_world400.lib and opencv_world400d.lib to the list of additional dependencies under Linker -> Input project properties

## Python wrapper (Only works on Release mode) ##

- add the folders ...Python\Python36\include and ...Python\Python36\Lib\site-packages\numpy\core\include to the list of additional include directories under C/C++ -> General project properties
- add the folder ...\Python\Python36\libs to the list of additional libraries directories under Linker -> General project properties

## Matlab c++ gen code ##

- add the folders ...MATLAB\R2018b\extern\bin\win64 and MATLAB\R2018b\bin\win64 to your path environment variables
- add the folder ...MATLAB\R2018b\extern\lib\win64\microsoft to the list of included directories under VC++ Directories on the project properties
- add the folder ...MATLAB\R2018b\extern\include to the list of additional include directories under C/C++ -> General project properties
- add the folders ...MATLAB\R2018b\extern\lib, ...MATLAB\R2018b\extern\lib\win64, ...MATLAB\R2018b\extern\lib\win64\microsoft and ...R2018b\extern\lib\win64\mingw64 to the list of additional libraries directories under Linker -> General project properties
- add all the .lib files present on MATLAB\R2018b\extern\lib\win64\microsoft folder to the list of additional dependencies under Linker -> Input project properties