
file(GLOB_RECURSE SRCS *.c)

add_executable(crack hacker2/crack.c)
#set_target_properties(crack PROPERTIES
#        COMPILE_FLAGS "-lcrypt")
add_subdirectory(pset4)
target_link_libraries(crack crypt)

add_executable(resize pset4/resize/resize.c)

add_custom_command(TARGET crack
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/hacker2/test.txt $<TARGET_FILE_DIR:crack>)

file(GLOB_RECURSE BMPS $CMAKE_CURRENT_SOURCE_DIR}/pset4/resize/*.bmp)

add_custom_command(TARGET resize
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/pset4/resize/small.bmp $<TARGET_FILE_DIR:resize>)


