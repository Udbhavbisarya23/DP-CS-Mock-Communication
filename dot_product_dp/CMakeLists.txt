add_executable(dot_product_dp dp.cpp)

set(REQUIRED_BOOST_VERSION "1.75.0")

find_package(Boost ${REQUIRED_BOOST_VERSION}
COMPONENTS 
json 
log 
program_options 
REQUIRED)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_dp0.txt
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_dp1.txt
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

target_compile_features(dot_product_dp PRIVATE cxx_std_20)

target_link_libraries(dot_product_dp
    Boost::json
    Boost::log
    Boost::program_options
)