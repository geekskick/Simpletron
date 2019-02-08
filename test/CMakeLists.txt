enable_testing()

add_executable(simpletron_test test.cpp)
target_link_libraries(simpletron_test PUBLIC simple_core)
add_test(simpletron_test simpletron_test)
