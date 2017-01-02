
file(GLOB_RECURSE SRCS *.c)

add_executable(crack hacker2/crack.c)
#set_target_properties(crack PROPERTIES
#        COMPILE_FLAGS "-lcrypt")
target_link_libraries(crack crypt)

