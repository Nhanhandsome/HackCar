# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/phamminhnhan/Documents/ESP-IDF/esp-idf-v5.0/components/bootloader/subproject"
  "/Users/phamminhnhan/eclipse-workspace/CarTool/build/bootloader"
  "/Users/phamminhnhan/eclipse-workspace/CarTool/build/bootloader-prefix"
  "/Users/phamminhnhan/eclipse-workspace/CarTool/build/bootloader-prefix/tmp"
  "/Users/phamminhnhan/eclipse-workspace/CarTool/build/bootloader-prefix/src/bootloader-stamp"
  "/Users/phamminhnhan/eclipse-workspace/CarTool/build/bootloader-prefix/src"
  "/Users/phamminhnhan/eclipse-workspace/CarTool/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/phamminhnhan/eclipse-workspace/CarTool/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/phamminhnhan/eclipse-workspace/CarTool/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
