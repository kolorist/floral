@echo off
setlocal EnableDelayedExpansion
if [%1]==[] (
set BUILD_CONFIG=Debug
set TARGET_DIRECTORY=debug64
) else (
set BUILD_CONFIG=%1
set TARGET_DIRECTORY=release64
)

if not exist "%TARGET_DIRECTORY%" (
mkdir %TARGET_DIRECTORY%
)

pushd %~dp0
cd %TARGET_DIRECTORY%
call cmake -DCMAKE_BUILD_TYPE=%BUILD_CONFIG% -DCMAKE_C_COMPILER:PATH="C:\Program Files\LLVM\bin\clang.exe" -DCMAKE_CXX_COMPILER:PATH="C:\Program Files\LLVM\bin\clang++.exe"  -DCMAKE_RC_COMPILER:PATH="C:Program Files\LLVM\bin\llvm-rc.exe" -DCMAKE_MAKE_PROGRAM="C:\DevTools\ninja\ninja.exe" -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE -G Ninja ..
popd