#
# Copyright (C) 2026 by Thun Lu. All rights reserved.
#

cmake_minimum_required(VERSION 3.15...3.31)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# version
file(STRINGS version.txt VMSGS_VERSION)
string(TIMESTAMP VMSGS_VERSION_TIMESTAMP "%Y-%m-%d %H:%M:%S")
execute_process(
  COMMAND git rev-parse HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE VMSGS_VERSION_COMMIT_ID
  OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET
)
execute_process(
  COMMAND git describe --tags
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE VMSGS_VERSION_TAG
  OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET
)

# project
project(
  vmsgs
  VERSION ${VMSGS_VERSION}
  DESCRIPTION "Vlink schemas center"
  LANGUAGES CXX
)
set(PROJECT_NAMESPACE vlink::)

# required
find_package(vlink CONFIG REQUIRED)
if(ENABLE_PROTOBUF)
  find_package(Protobuf CONFIG REQUIRED)
  set(protobuf_libs protobuf::libprotobuf)
endif()
if(ENABLE_FLATBUFFERS)
  find_package(Flatbuffers CONFIG REQUIRED)
  if(TARGET flatbuffers::flatbuffers_shared)
    set(flatbuffers_libs flatbuffers::flatbuffers_shared)
  elseif(TARGET flatbuffers::flatbuffers)
    set(flatbuffers_libs flatbuffers::flatbuffers)
  endif()
endif()

# common
vlink_check()
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
foreach(OUTPUTCONFIG Debug Release RelWithDebInfo MinSizeRel)
  string(TOUPPER "${OUTPUTCONFIG}" OUTPUTCONFIG_U)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_U} ${CMAKE_BINARY_DIR}/output/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_U} ${CMAKE_BINARY_DIR}/output/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG_U} ${CMAKE_BINARY_DIR}/output/lib)
endforeach()
# set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo;Debug;Release;MinSizeRel" CACHE STRING "" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()
if(MSVC)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MANIFEST:NO")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /MANIFEST:NO")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MANIFEST:NO")
  add_compile_options(/wd4068 /wd4158 /wd4819 /wd5287)
  add_compile_options(/GL)
  add_link_options(/LTCG)
  add_link_options(/IGNORE:4078)
endif()

# ipo
if(NOT MSVC AND NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
  include(CheckIPOSupported)
  check_ipo_supported(RESULT ipo_supported)
  if(ipo_supported)
    message(STATUS "Enable Interprocedural Optimization")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION FALSE)
  endif()
endif()
if(POLICY CMP0069)
  cmake_policy(SET CMP0069 NEW)
endif()

# options
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(ENABLE_PROTOBUF "" ON)
option(ENABLE_FLATBUFFERS "" ON)
set(INSTALL_CONFIG_DIR
    ${CMAKE_INSTALL_SYSCONFDIR}/${CMAKE_PROJECT_NAME}
    CACHE STRING "Install dir for config files (relative to prefix)"
)
if(NOT ENABLE_PROTOBUF AND NOT ENABLE_FLATBUFFERS)
  message(FATAL_ERROR "")
endif()
if(IS_ABSOLUTE "${INSTALL_CONFIG_DIR}")
  string(REGEX REPLACE "^([A-Za-z]:)?[\\/]+" "" BUILD_CONFIG_DIR "${_dir}")
else()
  set(BUILD_CONFIG_DIR ${INSTALL_CONFIG_DIR})
endif()

# src
file(GLOB_RECURSE PROJECT_HDRS ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE PROJECT_SRCS ${PROJECT_SOURCE_DIR}/src/*.cc)
add_library(${PROJECT_NAME} ${PROJECT_HDRS} ${PROJECT_SRCS})
add_library(${PROJECT_NAMESPACE}${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PUBLIC vlink::vlink)
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
         $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${PROJECT_NAME}>
         $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
)
if(ENABLE_PROTOBUF)
  file(GLOB_RECURSE PROTO_SRCS ${PROJECT_SOURCE_DIR}/schemas/*.proto)
  vlink_generate_cpp(
    TARGET
    generate_proto
    PROTO
    ${PROTO_SRCS}
    IN_DIR
    ${PROJECT_SOURCE_DIR}/schemas
    OUT_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
  )
  target_link_libraries(${PROJECT_NAME} PUBLIC ${protobuf_libs})
  target_link_libraries(${PROJECT_NAME} PRIVATE generate_proto)
  target_compile_definitions(${PROJECT_NAME} PUBLIC "VMSGS_ENABLE_PROTOBUF")
  set(PROTOBUF_GCC_POSITIVE_FLAGS)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 12)
    list(APPEND PROTOBUF_GCC_POSITIVE_FLAGS -Wno-stringop-overflow)
  endif()
  if(PROTOBUF_GCC_POSITIVE_FLAGS)
    if(TARGET generate_proto)
      target_compile_options(generate_proto PRIVATE ${PROTOBUF_GCC_POSITIVE_FLAGS})
    endif()
    target_compile_options(${PROJECT_NAME} PRIVATE ${PROTOBUF_GCC_POSITIVE_FLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${PROTOBUF_GCC_POSITIVE_FLAGS})
  endif()
endif()
if(ENABLE_FLATBUFFERS)
  file(GLOB_RECURSE FBS_SRCS ${PROJECT_SOURCE_DIR}/schemas/*.fbs)
  vlink_generate_cpp(
    TARGET
    generate_fbs
    FBS
    ${FBS_SRCS}
    IN_DIR
    ${PROJECT_SOURCE_DIR}/schemas
    OUT_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
  )
  vlink_generate_flatbuffers_registry_cpp(
    TARGET
    generate_fbs_registry
    ${FBS_SRCS}
    IN_DIR
    ${PROJECT_SOURCE_DIR}/schemas
    OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/fbs_registry.cc
    OUT_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
  )
  add_dependencies(generate_fbs_registry generate_fbs)
  target_link_libraries(${PROJECT_NAME} PUBLIC ${flatbuffers_libs})
  target_link_libraries(${PROJECT_NAME} PRIVATE generate_fbs generate_fbs_registry)
  target_compile_definitions(${PROJECT_NAME} PUBLIC "VMSGS_ENABLE_FLATBUFFERS")
endif()

# generate informations
if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/version.h.in)
  configure_file(${CMAKE_SOURCE_DIR}/cmake/version.h.in ${CMAKE_BINARY_DIR}/config/version.h @ONLY)
endif()
if(EXISTS ${CMAKE_SOURCE_DIR}/version.txt)
  configure_file(${CMAKE_SOURCE_DIR}/version.txt ${CMAKE_BINARY_DIR}/version.txt COPYONLY)
endif()

# install
install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(
  DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PATTERN "*.pb.cc" EXCLUDE
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME})
if(EXISTS ${CMAKE_BINARY_DIR}/config/version.h)
  install(FILES ${CMAKE_BINARY_DIR}/config/version.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME})
endif()
install(DIRECTORY ${PROJECT_SOURCE_DIR}/schemas DESTINATION ${INSTALL_CONFIG_DIR})
install(FILES ${PROJECT_SOURCE_DIR}/CHANGELOG.md DESTINATION ${INSTALL_CONFIG_DIR})
if(EXISTS ${CMAKE_SOURCE_DIR}/etc)
  install(DIRECTORY ${PROJECT_SOURCE_DIR}/etc/ DESTINATION ${INSTALL_CONFIG_DIR})
endif()

# export
vlink_export(${CMAKE_PROJECT_NAME} ${PROJECT_NAME} ${PROJECT_NAMESPACE} ${CMAKE_PROJECT_VERSION})

# message
set(VLINK_INFO_FILE ${CMAKE_BINARY_DIR}/output/${BUILD_CONFIG_DIR}/vmsgs-options.txt)
message("")
vlink_log()
vlink_log("┌──────── VMsgs Options ─────────────────────────────────────────────────────")
vlink_log("│ Project:              ${CMAKE_PROJECT_NAME}")
vlink_log("│ Version:              ${VMSGS_VERSION}")
vlink_log("│ Time stamp:           ${VMSGS_VERSION_TIMESTAMP}")
vlink_log("│ Git tag:              ${VMSGS_VERSION_TAG}")
vlink_log("│ Git commit-id:        ${VMSGS_VERSION_COMMIT_ID}")
vlink_log("│ Install prefix:       ${CMAKE_INSTALL_PREFIX}")
vlink_log("│ Compiler:             ${CMAKE_CXX_COMPILER}")
vlink_log("│ CMAKE_BUILD_TYPE:     ${CMAKE_BUILD_TYPE}")
vlink_log("│ BUILD_SHARED_LIBS:    ${BUILD_SHARED_LIBS}")
vlink_log("│ INSTALL_CONFIG_DIR:   ${INSTALL_CONFIG_DIR}")
vlink_log("│ ENABLE_PROTOBUF:      ${ENABLE_PROTOBUF}")
vlink_log("│ ENABLE_FLATBUFFERS:   ${ENABLE_FLATBUFFERS}")
vlink_log("└────────────────────────────────────────────────────────────────────────────")
message("")
install(FILES ${VLINK_INFO_FILE} DESTINATION ${INSTALL_CONFIG_DIR}/)
