#ifndef MSGLIB_H
#define MSGLIB_H

/**--------------
 * C-lang Headers
 * --------------**/
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

/**--------------
 * C++ Headers
 * --------------**/
#include <string>
#include <iostream>

namespace msglib {

  /**----------------------------------------------
   * [ struct of datas of socket (needed on Linux) 
   * - socket ( file discripter )
   * - Internet address structure
   * - Length of Internet address structure  
   * ---------------------------------------------**/
  struct socket_data {
    int         sock_fd;
    sockaddr_in addr;
    socklen_t   addr_len;
  };

  class BaseSocket {
   private:
    socket_data m_sd;
    std::string m_ip_addr;
    uint16_t    m_port;

   public:

  };


}

#endif // MSGLIB_H