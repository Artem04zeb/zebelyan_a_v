set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(FlagConnection)

find_package(doxygen)

set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxy/Doxyfile)
set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_IN})

add_custom_target(doc ALL
  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Doxy/rtf/refman.rtf DESTINATION .)

find_package(asio REQUIRED)

add_subdirectory(work)
