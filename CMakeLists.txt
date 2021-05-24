cmake_minimum_required(VERSION 3.2)

project(NewPro VERSION 1.0)

configure_file(NewProConfig.h.in NewProConfig.h)

add_executable(${PROJECT_NAME} main.cxx)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})#include the binary directory where wew building to.


add_subdirectory(Adder)

#Download the submodule
find_package(Git QUIET)
if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    #update all submodules
    option(GIT_SUBMODULE "Check submodules during buidl" ON)
    if (GIT_SUBMODULE)
        message(STATUS "submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT
                )
        if (NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT},
            please checkout")
        endif ()
    endif ()
endif ()

#check all submodules
if (NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "the glfw submodules was not downloaded! GIT_SUBMODULE was turned off o failed
        please checkout!")
endif ()


add_subdirectory(external/glfw)


target_include_directories(
        ${PROJECT_NAME} PUBLIC Adder
        PUBLIC external/glfw/include
)

target_link_directories(${PROJECT_NAME}
        PRIVATE Adder/
        PRIVATE external/glfw/src

        )


target_link_libraries(${PROJECT_NAME}
        adder
        glfw
        )

install(TARGETS ${PROJECT_NAME} DESTINATION bin)  #to install our target  in destination  $CMAKE_INSTALL_PREFIX/bin

install(FILES main.cxx DESTINATION src) #relative to $CMAKE_INSTALL_PREFIX/src

#include(CTest)


# first param: testcase name 
#second param: the executabele you want to run test on
#current binary dir point to build directory
#add_test("test1" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}") 


