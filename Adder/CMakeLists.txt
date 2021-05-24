add_library(adder adder.cpp)

install(TARGETS adder DESTINATION lib)  #to install our target  in destination  $CMAKE_INSTALL_PREFIX/bin

install(FILES adder.h DESTINATION include) #relative to $CMAKE_INSTALL_PREFIX/src