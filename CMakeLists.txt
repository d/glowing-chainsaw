cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
option(USE_CCACHE "Set of OFF to disable ccache" ON)
if(USE_CCACHE)
  find_program(CCACHE_PROGRAM ccache)
  if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
  else()
    message(
      FATAL_ERROR "Unable to find the program ccache. Set USE_CCACHE to OFF")
  endif()
endif()

add_subdirectory(src)

add_subdirectory(vendor/googletest)
add_subdirectory(vendor/benchmark)
