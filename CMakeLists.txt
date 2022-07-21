cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0075 NEW)
project(DPCommunication LANGUAGES CXX)
set(DPCommunication_VERSION 0.01)

if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
    message(FATAL_ERROR "MOTION requires at least g++-8")
endif ()

add_subdirectory(1value_neural_net)
add_subdirectory(dot_product_dp)
add_subdirectory(mat_const_operations_dp)
add_subdirectory(mat_mul_dp)
add_subdirectory(mult_dp)
add_subdirectory(neural_net_dp)
add_subdirectory(trial_server)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(Threads REQUIRED)
find_package(OpenMP REQUIRED)

set(REQUIRED_BOOST_VERSION "1.75.0")

find_package(Boost ${REQUIRED_BOOST_VERSION}
        COMPONENTS
        context
        fiber
        filesystem
        json
        log
        log_setup
        program_options
        system
        thread)
set(Boost_USE_STATIC_LIBS ON)

if (Boost_FOUND)
    set(MOTION_BOOST_LOG_DYN_LINK ON)
    else()
    include(cmake/BuildBoostLocally.cmake)
endif ()
