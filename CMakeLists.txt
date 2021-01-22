cmake_minimum_required (VERSION 3.1)
project (JNP-6 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall")

# http://stackoverflow.com/questions/10555706/
macro (add_executable _name)
    # invoke built-in add_executable
    _add_executable(${ARGV})
    if (TARGET ${_name})
        target_link_libraries(${_name} ${CMAKE_THREAD_LIBS_INIT} )
    endif()
endmacro()

add_executable(ooasm_example ooasm_example.cc computer.cc flag_handler.cc memory.cc ooasm.cc factory.cc)

install(TARGETS DESTINATION .)
