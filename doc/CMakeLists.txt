option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(CONF_PROJECT_NAME ${PROJECT_NAME})
    set(VERSION ${PROJECT_VERSION})
    set(CONF_INPUT ${CMAKE_SOURCE_DIR}/include)
    set(CONF_OUTPUT_DIR ${CMAKE_BINARY_DIR}/doc)

    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/doc/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT})

    add_custom_target(doc)
    add_custom_command(TARGET doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)