add_executable(yo main.cc)
add_library(stuff STATIC lzcnt.c lzcnt.cc)
target_link_libraries(yo benchmark::benchmark stuff)
