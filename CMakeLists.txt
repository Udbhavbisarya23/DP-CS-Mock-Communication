add_subdirectory(dot_product_dp)
add_subdirectory(mat_mul_dp)
add_subdirectory(mult_dp)
add_subdirectory(trial_server)

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
