cmake_minimum_required(VERSION 3.2)

project(New_pro)

add_executable("${PROJECT_NAME}" main.cxx)

install(TARGETS "${PROJECT_NAME}" DESTINATION bin)  #to install our target  in destination  $CMAKE_INSTALL_PREFIX/bin

install(FILES main.cxx DESTINATION src) #relative to $CMAKE_INSTALL_PREFIX/src

include(CTest)


# first param: testcase name 
#second param: the executabele you want to run test on
#current binary dir point to build directory
add_test("test1" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}") 


