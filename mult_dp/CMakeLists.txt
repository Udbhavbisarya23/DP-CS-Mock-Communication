add_executable(mult_dp dp.cpp)

set(REQUIRED_BOOST_VERSION "1.75.0")

find_package(Boost ${REQUIRED_BOOST_VERSION}
COMPONENTS 
json 
log 
program_options 
REQUIRED)

target_compile_features(mult_dp PRIVATE cxx_std_20)

target_link_libraries(mult_dp
    Boost::json
    Boost::log
    Boost::program_options
)