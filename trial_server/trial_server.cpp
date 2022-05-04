#include <iostream>  
#include <boost/asio.hpp>  
#include <boost/serialization/string.hpp>

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
   boost::asio::write( socket, boost::asio::buffer(msg) );  
}   

void read_struct(tcp::socket & socket,int num_elements, Shares* data) {
    cout << "Before reading of data\n";
    Shares fin_data[num_elements];
    for(int i=0;i<num_elements;i++) {
        boost::system::error_code ec;
        uint64_t arr[2];
        read(socket , boost::asio::buffer(&arr,sizeof(arr)), ec); 
        Shares temp;
        temp.Delta = arr[0];
        temp.delta = arr[1];
        fin_data[i] = temp; 
    }

    for(int i=0;i<num_elements;i++) {
        cout << fin_data[i].Delta << " " << fin_data[i].delta << endl;
    }

    return;
}

int main(int argc,char* argv[]) {

    int port_number = atoi(argv[1]);

    boost::asio::io_service io_service;  

    //listen for new connection  
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), port_number ));  

    //socket creation  
    tcp::socket socket_(io_service);  

    //waiting for the connection  
    acceptor_.accept(socket_);  

    //read operation
    boost::system::error_code ec;
    int num_elements;  
    read(socket_ , boost::asio::buffer(&num_elements, sizeof(num_elements)), ec);
    if(ec) {
        cout << ec << "\n";
    } else {
        cout << "No Error\n";
    }
    // string message = read_(socket_);  
    cout << "The number of elements are :- " << num_elements << endl;  

    //write operation  
    const string msg = "Server has received the number of elements \n"; 
    boost::asio::write( socket_, boost::asio::buffer(msg) ); 
    cout << "Servent sent message to Client!" << endl;
    
    //Read the data in the reuired format
    Shares data[num_elements];
    read_struct(socket_, num_elements, data);

    socket_.close();

}

