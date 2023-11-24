#include "udp.h"

const string brd_addr = "255.255.255.255";

UdpPartner::UdpPartner(string device_addr, int device_port){
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(device_addr.c_str());
    addr.sin_port = htons(device_port);
    port = device_port;
}

string UdpPartner::get_addr(){
    return string(inet_ntoa(addr.sin_addr));
}

UdpMain::UdpMain(string own_addr, int own_port){
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(own_addr.c_str());
    addr.sin_port = htons(own_port);
    port = own_port;
    addr_len = sizeof(addr);
    udp_bind();
}

UdpMain::~UdpMain(){
    close(sock);
}

void UdpMain::enable_broadcast(){
    permission_broadcast = true;
    if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&broadcast_flag, sizeof(broadcast_flag)) == 0){
        cout << "Broadcast enabled" << endl;
    }
    else{
        cout << "no" << endl;
    }
}

void UdpMain::udp_bind(){
    bind(sock, (const struct sockaddr *)&addr, sizeof(addr));
}

void UdpMain::udp_sendto(const void *buf, UdpPartner dst_device){

    if(dst_device.get_addr() == brd_addr && permission_broadcast == false){
        cout << "permission denied" << endl;
    }

    if(sendto(sock, buf, sizeof(buf), 0, 
             (struct sockaddr *)&dst_device.addr, sizeof(dst_device.addr)) == -1){
        cout << "failed" << endl;
    }
}

int UdpMain::udp_receive(){
    int size = recvfrom(sock, RxBuf, BUF_SIZE, 0, (struct sockaddr *)&dst_device, &addr_len);
    return size;
}

void UdpMain::get_RxData(void *buf){
    
}

char* UdpMain::get_dst_addr(){
    return inet_ntoa(dst_device.sin_addr);
}

int UdpMain::get_dst_port(){
    return ntohs(dst_device.sin_port);
}
