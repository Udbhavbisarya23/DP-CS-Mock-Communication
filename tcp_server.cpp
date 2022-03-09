#include <iostream>  
#include <boost/asio.hpp>  

using namespace boost::asio;  
using ip::tcp;  
using std::string;  
using std::cout;  
using std::endl; 

struct Shares {
     uint64_t Delta,delta;
};

string read_(tcp::socket & socket) {  
   boost::asio::streambuf buf;

   boost::asio::read_until( socket, buf, "\n" );  
   string data = boost::asio::buffer_cast<const char*>(buf.data());  
   return data;  
}  

void send_(tcp::socket & socket, const string& message) {  
   const string msg = message + "\n";  
   boost::asio::write( socket, boost::asio::buffer(message) );  
}  

int main() {  
  boost::asio::io_service io_service;  

//listen for new connection  
  tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234 ));  

//socket creation  
  tcp::socket socket_(io_service);  

//waiting for the connection  
  acceptor_.accept(socket_);  

//read operation
  boost::system::error_code ec;
  Shares data;  
  std::size_t length = read(socket_ , buffer(&data, sizeof(data)), ec);
  // string message = read_(socket_);  
  cout << data.Delta << endl;  

//write operation  
  send_(socket_, "Hello From Server!");  
  cout << "Servent sent Hello message to Client!" << endl;  
  return 0;  
}  

