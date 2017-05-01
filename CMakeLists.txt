cmake_minimum_required(VERSION 3.2.2)
project(Algorithm LANGUAGES C CXX)

# Setting up output subdirectories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/lib)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
endforeach()

# C++ definitions
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_REQUIRED TRUE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Components
add_subdirectory(sorting)
add_subdirectory(utils)
add_subdirectory(tests)

#add_executable(sjabber ${SRC})
#add_dependencies(sjabber qxmpp-static shared-third-party)
#target_link_libraries(sjabber qxmpp-static)
#target_compile_definitions(sjabber PRIVATE QXMPP_STATIC)
#foreach(_QTM ${QT_MODULES_LIST})
#	add_custom_command(
#		TARGET shared-qt POST_BUILD
#		COMMENT "Shared ${_QTM} added to ${_QTM_DIR}"
#		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::${_QTM}> ${_QTM_DIR})
#endforeach()
#add_library(qxmpp-static STATIC ${QXMPP_SRC})
#add_definitions(-DQXMPP_STATIC)
