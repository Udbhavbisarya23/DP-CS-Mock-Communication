add_executable(trial_server trial_server.cpp)

find_package(Boost COMPONENTS json log program_options REQUIRED)

target_compile_features(trial_server PRIVATE cxx_std_20)

target_link_libraries(trial_server
    Boost::json
    Boost::log
    Boost::program_options
)