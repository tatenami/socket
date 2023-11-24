#ifndef SOCKET_UNIT_H
#define SOCKET_UNIT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

#define USE_BROADCST 1
#define BUF_SIZE 4

extern const string brd_addr;
const static int broadcast_flag = 1;

class SocketPartner{
    public:
        struct sockaddr_in ip_addr;
        int port_number;
    
    public:
        SocketPartner(string addr, int port);
        string get_addr();

};

class SocketUnit{
private:
    int sock;
    uint8_t RxData[BUF_SIZE];

    struct sockaddr_in ip_addr;
    int port_number;
    unsigned int ip_addr_len;

    bool permission_broadcast;

public:
    SocketUnit(string ddr, int port);
    ~SocketUnit();
    void socket_bind();

    void udp_sendto();
    void udp_receive();
    void get_RxData(void *buf);
};

#endif // SOCKET_UNIT_H 