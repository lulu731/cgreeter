#include "native_byte_order.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <string>

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)

using boost::asio::local::stream_protocol;

enum { max_length = 1024 };

int main(int argc, char* argv[])
{
  try
  {
    using namespace std; // For strlen.
    const char *request = "{\"type\": \"create_session\", \"username\": \"lulu\"}";
    size_t request_length = strlen(request);
    std::cout << request_length << std::endl;

    char len_bytes[4];
    ToNativeByteOrder(request_length, len_bytes);
    std::cout << len_bytes[0] << std::endl;

    boost::asio::io_context io_context;

    stream_protocol::socket s(io_context);
    const char *buf = std::getenv("GREETD_SOCK");
    std::cout << buf << std::endl;

    std::cout << s.is_open() << std::endl;
    s.connect(stream_protocol::endpoint(buf));
    std::cout << s.is_open() << std::endl;

    size_t sent = boost::asio::write(s, boost::asio::buffer(len_bytes, request_length),
      boost::asio::transfer_exactly(4));
    sent = boost::asio::write(s, boost::asio::buffer(request, request_length),
      boost::asio::transfer_exactly(request_length));
    std::cout << request << std::endl;

    std::cout << sent << std::endl;

    char reply_bytes[4];
    std::cout << "in Reply" << std::endl;
    size_t reply_length = boost::asio::read(s,
        boost::asio::buffer(reply_bytes, 4), boost::asio::transfer_exactly(4));
    std::cout << "reply_length1 = " <<reply_length << std::endl;

    size_t reply_size;
    FmNativeByteOrder(reply_bytes, reply_size);
    std::cout << reply_size << std::endl;

    char reply[reply_size];
    reply_length = boost::asio::read(s,
        boost::asio::buffer(reply, reply_size), boost::asio::transfer_exactly(reply_size));
    std::cout << "reply_length2 = " <<reply_length << std::endl;


    std::cout << "after read" << std::endl;
    std::cout << "Reply is: ";
    std::cout.write(reply, reply_length);
    std::cout << "\n";
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}

#else // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
  std::scout << "BOOST_ASIO_HAS_LOCAL_SOCKETS not defined\n"; // error Local sockets not available on this platform.
#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)