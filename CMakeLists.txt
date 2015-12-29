project(RemotingNgDemo)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/install)

include(ExternalProject)
ExternalProject_Add(
    macchina.io
    PREFIX macchina.io
    GIT_REPOSITORY https://github.com/macchina-io/macchina.io.git
    GIT_TAG macchina-0.1.0-release
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make -s -j4 DEFAULT_TARGET=shared_release
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND INSTALLDIR=${CMAKE_PREFIX_PATH}/install make install
)

find_library(POCO_FOUNDATION_LIBRARY PocoFoundation)
find_library(POCO_UTIL_LIBRARY PocoUtil)
find_library(POCO_NET_LIBRARY PocoNet)
find_library(POCO_REMOTINGNG_LIBRARY PocoRemotingNG)
find_library(POCO_REMOTINGNG_TCP_LIBRARY PocoRemotingNGTCP)
find_program(REMOTE_GEN_NG RemoteGenNG)

set(POCO_BASE /home/behrens/Projects/macchina.io/platform)

set(
    INTERFACE_FILES
    ParameterServer.h
)

configure_file(
    gen_config.xml.in
    gen_config.xml
    @ONLY
)

add_custom_target(
    code_generation
    COMMAND ${REMOTE_GEN_NG} ${CMAKE_CURRENT_BINARY_DIR}/gen_config.xml -DPOCO_BASE=${POCO_BASE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    SOURCES gen_config.xml ${INTERFACE_FILES}
)

add_dependencies(
    code_generation
    macchina.io
)

add_definitions(-std=c++14)

aux_source_directory(${CMAKE_BINARY_DIR}/src-gen SRC_GEN_LIST)

add_executable(
    ${PROJECT_NAME}
    ${INTERFACE_FILES}
    ${SRC_GEN_LIST}
    ParameterServer.cpp
    ParameterServer.h
    main.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/src-gen
        ${POCO_BASE}/Foundation/include
        ${POCO_BASE}/Util/include
        ${POCO_BASE}/Net/include
        ${POCO_BASE}/RemotingNG/include
        ${POCO_BASE}/RemotingNG/TCP/include
)

target_link_libraries(
    ${PROJECT_NAME}
    ${POCO_FOUNDATION_LIBRARY}
    ${POCO_UTIL_LIBRARY}
    ${POCO_NET_LIBRARY}
    ${POCO_REMOTINGNG_LIBRARY}
    ${POCO_REMOTINGNG_TCP_LIBRARY}
)

add_dependencies(
    ${PROJECT_NAME}
    macchina.io
    code_generation
)
