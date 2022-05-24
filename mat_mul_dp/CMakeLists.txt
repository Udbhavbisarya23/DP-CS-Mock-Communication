add_executable(mat_mul_dp dp.cpp)

find_package(Boost COMPONENTS json log program_options REQUIRED)

target_compile_features(mat_mul_dp PRIVATE cxx_std_20)

target_link_libraries(mat_mul_dp
    Boost::json
    Boost::log
    Boost::program_options
)