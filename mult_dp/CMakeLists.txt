add_executable(mult_dp dp.cpp)

find_package(Boost COMPONENTS json log program_options REQUIRED)

target_compile_features(mult_dp PRIVATE cxx_std_20)

target_link_libraries(mult_dp
    Boost::json
    Boost::log
    Boost::program_options
)