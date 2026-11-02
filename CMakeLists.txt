cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME matrix)
project(${PROJECT_NAME} CXX)

# --- Конфигурация сборки ---
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)

# --- Пути ---
set(MP2_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(MP2_GTEST   "${CMAKE_CURRENT_SOURCE_DIR}/gtest")

# --- Интерфейсная библиотека с заголовками матрицы ---
add_library(mp2_library INTERFACE)
target_sources(mp2_library INTERFACE
    ${MP2_INCLUDE}/tmatrix.h
)
target_include_directories(mp2_library INTERFACE
    ${MP2_INCLUDE}
    ${MP2_GTEST}
)

# --- Google Test ---
add_library(gtest STATIC gtest/gtest-all.cc)
target_include_directories(gtest PUBLIC ${MP2_GTEST})
find_package(Threads REQUIRED)
target_link_libraries(gtest PUBLIC Threads::Threads)

# --- Пример ---
add_executable(sample_matrix samples/sample_matrix.cpp)
target_link_libraries(sample_matrix PRIVATE mp2_library)

# --- Тесты ---
add_executable(test_utmatrix
    test/test_main.cpp
    test/test_tmatrix.cpp
    test/test_tvector.cpp
)
target_link_libraries(test_utmatrix PUBLIC gtest mp2_library)