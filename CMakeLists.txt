#-------------------------------
# PROJECT INFORMATION
#-------------------------------

cmake_minimum_required(VERSION 3.13)
project(sdbuscpp-examples VERSION 0.0.1 LANGUAGES C CXX)
set (PROJECT_NAME sdbuscpp-examples)
set(CMAKE_CXX_STANDARD 17)

#-------------------------------
# PREPARING THE DEPENDENCIES
#-------------------------------

find_package(PkgConfig REQUIRED)
pkg_check_modules(Systemd IMPORTED_TARGET GLOBAL libsystemd>=236)
if(NOT TARGET PkgConfig::Systemd)
	message(FATAL_ERROR "libsystemd of version at least 236 is required, but was not found "
						"(if you have systemd in your OS, you may want to install package containing pkgconfig "
						" files for libsystemd library. On Ubuntu, that is libsystemd-dev. ")
endif()
add_library(Systemd::Libsystemd ALIAS PkgConfig::Systemd)
string(REGEX MATCHALL "([0-9]+)" SYSTEMD_VERSION_LIST "${Systemd_VERSION}")
list(GET SYSTEMD_VERSION_LIST 0 LIBSYSTEMD_VERSION)

#-------------------------------
# SOURCE FILES CONFIGURATION & PREPARING THE DBUS FILES
#-------------------------------

set(EXAMPLES_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(BASIC_LAYER_SERVER
    ${EXAMPLES_SRC_DIR}/basic_layer_server.cpp)

set(BASIC_LAYER_CLIENT
    ${EXAMPLES_SRC_DIR}/basic_layer_client.cpp)

set(CONVENIENCE_LAYER_SERVER
    ${EXAMPLES_SRC_DIR}/convenience_layer_server.cpp)

set(CONVENIENCE_LAYER_CLIENT
    ${EXAMPLES_SRC_DIR}/convenience_layer_client.cpp)

add_executable(basic_layer_server ${BASIC_LAYER_SERVER})

add_executable(basic_layer_client ${BASIC_LAYER_CLIENT})

add_executable(convenience_layer_server ${CONVENIENCE_LAYER_SERVER})

add_executable(convenience_layer_client ${CONVENIENCE_LAYER_CLIENT})

#----------------------------------
# LINK LIBRARIES
#----------------------------------

target_link_libraries(basic_layer_server sdbus-c++ pthread)
target_link_libraries(basic_layer_client sdbus-c++ pthread)
target_link_libraries(convenience_layer_server sdbus-c++ pthread)
target_link_libraries(convenience_layer_client sdbus-c++ pthread)
