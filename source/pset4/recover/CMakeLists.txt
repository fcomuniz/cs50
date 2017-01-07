



add_executable(recover recover.c)

add_custom_command(TARGET recover
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/card.raw $<TARGET_FILE_DIR:recover>)