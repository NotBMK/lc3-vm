set(TARGET "test")

include_directories(include)

add_executable(${TARGET} main.cpp)
    
add_custom_command(
    TARGET ${TARGET}
    COMMAND "./${TARGET} ./2048.obj"
    USES_TARGETS ${TARGET})