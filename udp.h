#ifndef UDP_H
#define UDP_H

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

class UdpPartner{
    public:
        struct sockaddr_in addr;
        int port;
    
    public:
        UdpPartner(string device_addr, int device_port = 0);
        string get_addr();

};

class UdpMain{
    public:
        int sock;
        char RxBuf[BUF_SIZE];
        struct sockaddr_in addr;
        struct sockaddr_in dst_device;
        int port;
        unsigned int addr_len;

        bool permission_broadcast = false;

    public:
        UdpMain(string own_addr, int own_port);
        ~UdpMain();
        void enable_broadcast();
        void udp_bind();
        void udp_sendto(const void *buf, UdpPartner dst_device);
        int udp_receive();
        void get_RxData(void *buf);
        char* get_dst_addr();
        int get_dst_port();
};



#endif // UDP_H 