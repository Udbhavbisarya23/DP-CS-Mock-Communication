#include <iostream>  
#include <type_traits>
#include <cstdint>
#include <random> 
#include <stdexcept> 

#include <boost/asio.hpp>
#include <boost/program_options.hpp>

using namespace boost::asio;
namespace po = boost::program_options;  
using ip::tcp;  
using std::string;  
using std::cout;  
using std::endl;  

struct Options {
  int cs1_port;
  int cs2_port;
};

std::optional<Options> parse_program_options(int argc, char* argv[]) {
  Options options;
  boost::program_options::options_description desc("Allowed options");
  // clang-format off
  desc.add_options()
    ("help,h", po::bool_switch()->default_value(false),"produce help message")
    ("compute-server1-port", po::value<int>()->required(), "Port number of compute server 1")
    ("compute-server2-port", po::value<int>()->required(), "Port number of compute server 2")
    ;
  // clang-format on

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  bool help = vm["help"].as<bool>();
  if (help) {
    std::cerr << desc << "\n";
    return std::nullopt;
  }
  
  options.cs1_port = vm["compute-server1-port"].as<int>();
  options.cs2_port = vm["compute-server2-port"].as<int>();

  return options;
}


template <typename E>
std::uint64_t blah(E& engine) {
    std::uniform_int_distribution<unsigned long long> dis(
        std::numeric_limits<std::uint64_t>::min(),
        std::numeric_limits<std::uint64_t>::max()
    );
    return dis(engine);
}

struct Shares {
     uint64_t Delta,delta;
};


int main(int argc, char* argv[]) {  
 auto options = parse_program_options(argc, argv);
 if (!options.has_value()) {
    return EXIT_FAILURE;
 }

 boost::asio::io_service io_service;  

//socket creation  
 tcp::socket socket(io_service);  

//connection  
 socket.connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), options->cs1_port ));  

// request/message from client  
const string msg = "Hello from Client!\n";
std::random_device rd;
std::mt19937 gen(rd());
std::uint64_t del0 = blah(gen);
std::uint64_t del1 = blah(gen);

std::uint64_t val;

std::cout << "Enter the input value :- ";
std::cin >> val;

std::uint64_t Del = del0 + del1 + val;

Shares main_message {Del,del0};


 boost::system::error_code error;  
 boost::asio::write( socket, boost::asio::buffer(&main_message,sizeof(main_message)), error );  
 if( !error ) {  
      cout << std::to_string(Del) << endl;  
 }  
 else {  
      cout << "send failed: " << error.message() << endl;  
 }  

// getting a response from the server  
 boost::asio::streambuf receive_buffer;  
 boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);  
 if( error && error != boost::asio::error::eof ) {  
      cout << "receive failed: " << error.message() << endl;  
 }  
 else {  
      const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());  
      cout << data << endl;  
 }
 socket.close();

// Now for CS1  
boost::asio::io_service io_service_1;  

//socket creation  
tcp::socket socket_1(io_service_1);  

//connection  
socket_1.connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), options->cs2_port ));  

// request/message from client
Shares main_message_1 {Del,del1};


 boost::asio::write( socket_1, boost::asio::buffer(&main_message_1,sizeof(main_message_1)), error );  
 if( !error ) {  
      cout << std::to_string(Del) << endl;  
 }  
 else {  
      cout << "send failed: " << error.message() << endl;  
 }  

// getting a response from the server  
 boost::asio::streambuf receive_buffer_1;  
 boost::asio::read(socket_1, receive_buffer_1, boost::asio::transfer_all(), error);  
 if( error && error != boost::asio::error::eof ) {  
      cout << "receive failed: " << error.message() << endl;  
 }  
 else {  
      const char* data = boost::asio::buffer_cast<const char*>(receive_buffer_1.data());  
      cout << data << endl;  
 }
 socket.close();
 return 0;  
}  

