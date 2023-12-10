#include "socket.h"

const string broadcast_addr = "255.255.255.255";
const static bool broadcast_flag = USE_BROADCST;

DstData::DstData(string ip_addr, int port){
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    addr.sin_port = htons(port);
}

// ----------[base class func]-----------

SocketUnit::~SocketUnit(){
    close(own_data.sock);
}

void SocketUnit::socket_bind(){
    bind(own_data.sock, (const struct sockaddr *)&(own_data.addr), sizeof(own_data.addr));
}

int SocketUnit::receive(){
    int size = recvfrom(own_data.sock, RxBuf, BUF_SIZE, 0, (struct sockaddr *)&src_data.addr, &src_data.addr_len);
    if(size < 0){
        cout << "Couldn't receive data" << endl;
    }
    return size;
}

void SocketUnit::get_RxData(void *buf){
    memcpy(buf, &RxBuf, BUF_SIZE);
}

// ----------[UDP unit func]-----------

UDPUnit::UDPUnit(string ip_addr, int port){
    own_data.sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    own_data.addr.sin_family = AF_INET;
    own_data.addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    own_data.addr.sin_port = htons(port);
    own_data.port = port;
    own_data.addr_len = sizeof(own_data.addr);

    socket_bind();
}

UDPUnit::~UDPUnit(){
    close(own_data.sock);
}

int UDPUnit::send(const void *buf, DstData dst){
    int result = sendto(own_data.sock, buf, sizeof(buf), 0, (const struct sockaddr *)&dst.addr, sizeof(dst.addr));

    if(result < 0){
        cout << "Couldn't send data" << endl;
    }
    return result;
}

int UDPUnit::receive(){
    int size = recvfrom(own_data.sock, RxBuf, BUF_SIZE, 0, (struct sockaddr *)&src_data.addr, &src_data.addr_len);
    if(size < 0){
        cout << "Couldn't receive data" << endl;
    }
    return size;
}
