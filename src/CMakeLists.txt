
add_library(simple_core Simpletron.cpp)
add_executable(simpletron main.cpp)
target_compile_options(simple_core PUBLIC "-g")
target_link_libraries(simpletron PRIVATE simple_core)
target_include_directories(simple_core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})