cmake_minimum_required(VERSION 3.10)

project(RectangleBinPack VERSION "1.0.0" LANGUAGES CXX)

set(TEST_PROJECT_NAME MaxRectsBinPackTest)

add_library(${PROJECT_NAME}
    GuillotineBinPack.cpp
    MaxRectsBinPack.cpp
    Rect.cpp
    ShelfBinPack.cpp
    ShelfNextFitBinPack.cpp
    ShelfNextFitBinPack.cpp
    SkylineBinPack.cpp
)

add_library(RectangleBinPack::RectangleBinPack ALIAS ${PROJECT_NAME})
add_executable(${TEST_PROJECT_NAME} test/MaxRectsBinPackTest.cpp MaxRectsBinPack.cpp Rect.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${TEST_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
target_compile_features(${TEST_PROJECT_NAME} PUBLIC cxx_std_11)
