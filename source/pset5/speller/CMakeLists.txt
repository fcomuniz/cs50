set(SRCS dictionary.c speller.c)
set(HDRS dictionary.h)
add_executable(speller ${SRCS})


# Move necessary files to correct path
# Creating dictionaries folder
add_custom_command(TARGET speller
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:speller>/dictionaries)

add_custom_command(TARGET speller
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/dictionaries $<TARGET_FILE_DIR:speller>/dictionaries)

#Creating keys folder

add_custom_command(TARGET speller
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:speller>/keys)

add_custom_command(TARGET speller
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/keys $<TARGET_FILE_DIR:speller>/keys)

add_custom_command(TARGET speller
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:speller>/texts)

add_custom_command(TARGET speller
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/texts $<TARGET_FILE_DIR:speller>/texts)


# Adding unit tests


file(GLOB_RECURSE UNIT_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*Test.c)
foreach (file_path ${UNIT_SRCS})
    get_filename_component(dir_path ${file_path} PATH)
    get_filename_component(file_name_we ${file_path} NAME_WE)
    add_executable(${file_name_we} ${file_path} dict-trie.c)
        target_link_libraries(${file_name_we} )
    add_test(NAME ${file_name_we}
            COMMAND ${file_name_we})
endforeach ()

