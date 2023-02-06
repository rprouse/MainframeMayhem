@echo off
pushd %~dp0\ParseLevels

dotnet run -- "%~dp0\res\levels\"

popd