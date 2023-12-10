#ifndef SOCKET_H
#define SOCKET_H

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

// ----------[socket_data_struct]--------------------

typedef struct{
    int sock;
    struct sockaddr_in addr;
    uint16_t port;
    uint32_t addr_len;
    string ip_addr;
}socket_data;

// ----------[partner_data]----------

class DstData{
public:
    struct sockaddr_in addr;
public:
    DstData(string addr, int port);
};

// ----------[base class]-----------------

class SocketUnit{
protected:
    socket_data own_data;
    socket_data src_data;
    uint8_t RxBuf[BUF_SIZE];

    void socket_bind();

public:
    ~SocketUnit();
    virtual int receive();
    void get_RxData(void *buf);
};

//-----------[UDP class]----------
class UDPUnit: public SocketUnit{
private:
    socket_data bc_data;

public:
    UDPUnit(string ip_addr, int port);
    ~UDPUnit();
    int send(const void *buf, DstData dst);
    int receive() override;
};

#endif // SOCKET_H 