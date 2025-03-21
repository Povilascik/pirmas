@echo off
echo Building project with CMake...

:: Create build directory if it doesn't exist
if not exist "build" mkdir build

:: Navigate to build directory
cd build

:: Configure project with CMake (generates build files)
cmake ..


:: Build the project
cmake --build .

:: Return to original directory
cd Debug

cls

:: Run the executable (replace "YourProgram" with your actual executable name)
echo Running program...
programa.exe