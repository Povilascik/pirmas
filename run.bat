@echo off
echo Building project with CMake...

:: Create build directory if it doesn't exist
if not exist "build" mkdir build

:: Navigate to build directory
cd build
#labas
:: Configure project with CMake (generates build files)
cmake -DCMAKE_C_COMPILER=C:\MinGW\bin -DCMAKE_CXX_COMPILER=C:\MinGW\bin ..



:: Build the project
cmake --build .

:: Return to original directory
cd ..

:: Run the executable (replace "YourProgram" with your actual executable name)
echo Running program...
programa.exe


:: Pause so you can see any output
pause