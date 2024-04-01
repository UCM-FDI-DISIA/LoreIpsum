#!/bin/bash

# Genera una lista de archivo en base al archivo vcxproj

echo "set(vcxproj_src " > vcxproj_list.cmake

grep -Eo '".*.cpp"' Hollenhaus\ proyect\ VS.vcxproj | tr '\\' '/' >> vcxproj_list.cmake

echo ")" >> vcxproj_list.cmake

echo "set(vcxproj_headers " >> vcxproj_list.cmake
grep -Eo '".*.h"' Hollenhaus\ proyect\ VS.vcxproj | tr '\\' '/' >> vcxproj_list.cmake
echo ")" >> vcxproj_list.cmake
