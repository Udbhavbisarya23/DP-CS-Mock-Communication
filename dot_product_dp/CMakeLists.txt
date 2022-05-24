add_executable(dot_product_dp dp.cpp)

find_package(Boost COMPONENTS json log program_options REQUIRED)

target_compile_features(dot_product_dp PRIVATE cxx_std_20)

target_link_libraries(dot_product_dp
    Boost::json
    Boost::log
    Boost::program_options
)