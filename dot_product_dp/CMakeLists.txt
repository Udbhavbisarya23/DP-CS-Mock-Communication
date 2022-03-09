add_executable(dp dp.cpp)

find_package(Boost COMPONENTS json log program_options REQUIRED)

target_compile_features(dp PRIVATE cxx_std_20)

target_link_libraries(dp
    Boost::json
    Boost::log
    Boost::program_options
)