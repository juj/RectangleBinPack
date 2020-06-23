cmake_minimum_required(VERSION 3.10)

project(RectangleBinPack VERSION "1.0.0" LANGUAGES CXX)

add_library(RectangleBinPack
    GuillotineBinPack.cpp
    MaxRectsBinPack.cpp
    Rect.cpp
    ShelfBinPack.cpp
    ShelfNextFitBinPack.cpp
    ShelfNextFitBinPack.cpp
    SkylineBinPack.cpp
)

target_include_directories(RectangleBinPack
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(RectangleBinPack::RectangleBinPack ALIAS RectangleBinPack)
