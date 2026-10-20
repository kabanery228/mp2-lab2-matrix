cmake_minimum_required(VERSION 3.30)
set(PROJECT_NAME_STR Matrix)
#project(${PROJECT_NAME_STR} VERSION 1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/gtest)	

#add_executable(${PROJECT_NAME_STR} ${CMAKE_CURRENT_SOURCE_DIR}/samples/*.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)
file (GLOB PATH_STR ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
				${CMAKE_CURRENT_SOURCE_DIR}/samples/*.cpp)
add_executable(${PROJECT_NAME_STR} ${PATH_STR})