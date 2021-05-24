cmake_minimum_required(VERSION 3.2)

project(NewPro VERSION 1.0)

add_executable(${PROJECT_NAME} main.cxx)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})#include the binary directory where wew building to.
option(USE_ADDER "LIBRARY for summing two float num ." ON)

if(USE_ADDER)
    add_subdirectory(Adder)
    list(APPEND EXTRA_LIBS adder)
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Adder")

endif()

#Download the submodule
find_package(Git QUIET)
if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
#update all submodules
    option(GIT_SUBMODULE "Check submodules during build" ON)
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

configure_file(NewProConfig.h.in NewProConfig.h) 

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include ${EXTRA_INCLUDES})

target_link_directories(${PROJECT_NAME} PRIVATE external/glfw/src  ${EXTRA_INCLUDES})

target_link_libraries(${PROJECT_NAME} glfw ${EXTRA_LIBS})

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/App")
install(TARGETS ${PROJECT_NAME} DESTINATION bin) 
install(FILES 
    "${PROJECT_BINARY_DIR}/NewProConfig.h" DESTINATION include)
install(CODE "MESSAGE(\"Sample install message.\")")
install(FILES 
    main.cxx DESTINATION src
)



#include(CTest)

#first param : testcase name
#second param : the executabele you want to run test on
#current binary dir point to build directory
#add_test("test1"   "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")