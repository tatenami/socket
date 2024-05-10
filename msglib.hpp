#ifndef MSGLIB_H
#define MSGLIB_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <string>
#include <iostream>

namespace msglib{

    /* --- [ const values ] --- */

    extern const std::string loopback_address;
    extern const int non_blocking_flag;
    extern const int blocking_flag;

    /* --- [ Basic Datas ] ---*/

    struct socket_data{
        int         sock_fd;
        sockaddr_in addr;
        socklen_t   addr_len;
    };

    class DstInfo{
    public:
        sockaddr_in addr_;
        socklen_t   addr_len_;

        DstInfo(uint16_t port_number);
        DstInfo(std::string ip_address, uint16_t port_number);
        ~DstInfo();
    };

    /* --- [ SocketBase Class ] --- */

    class SocketBase{
    protected:
        socket_data sd_;        // sender: destination socket data.  receiver: own socket data.
        std::string ip_addr_;
        uint16_t    port_;

    protected:
        void set_socket(int sock_type, int protocol, std::string ip_address, uint16_t port_number);
        void print_socket_info();

    public:
        SocketBase(std::string ip_address, uint16_t port_number);
        virtual ~SocketBase() = 0;
    };

    /* --- [ UDP Classes ] ---*/

    class UDPSender: public SocketBase{
    protected:
        void set_socket(std::string ip_address, uint16_t port_number);

    public:
        UDPSender(uint16_t poer_number);
        UDPSender(std::string ip_address, uint16_t port_number);
        void set_dst_info(std::string ip_address, uint16_t port_number);
        int send(void* msg, int size) const;
        int send(void* msg, int size, std::string ip_address, uint16_t port_number) const;

        template <typename T> 
        int send(T& msg) const{
            int result_size = sendto(sd_.sock_fd, &msg, sizeof(T), 0, (struct sockaddr *)&(sd_.addr), sd_.addr_len);
            if(result_size < 0){
                std::cout << "fail to send data" << std::endl;
            }
            return result_size;
        }

        template <typename T> 
        int send(T& msg, DstInfo& dst) const{
            int result_size = sendto(sd_.sock_fd, &msg, sizeof(T), 0, (struct sockaddr *)&(dst.addr_), dst.addr_len_);
            if(result_size < 0){
                std::cout << "fail to send data" << std::endl;
            }
            return result_size;
        }
    };
    
    class UDPReceiver: public SocketBase{
    protected:
        sockaddr_in sender_addr_;

    protected:
        void set_socket(std::string ip_address, uint16_t port_number);

    public:
        UDPReceiver(uint16_t port_number);
        UDPReceiver(std::string ip_address, uint16_t port_number);
        void change_to_non_blocking();
        void change_to_blocking();
        char* get_sender_addr();
        int get_sender_port();
        int receive(void *buf, int size);

        template <typename T> int receive(T& buf){
            socklen_t addr_len = sizeof(sender_addr_);
            return recvfrom(sd_.sock_fd, &buf, sizeof(T), 0, (struct sockaddr *)&sender_addr_, &addr_len);
        }

        template <typename T> int receive(T* buf){
            socklen_t addr_len = sizeof(sender_addr_);
            return recvfrom(sd_.sock_fd, buf, sizeof(T), 0, (struct sockaddr *)&sender_addr_, &addr_len);
        }
    };

    /* --- [ UDPUnit Class ] ---- */

    class UDPUnit{
    public:
        UDPSender   sender;
        UDPReceiver receiver;

    public:
        UDPUnit(std::string ip_address, uint16_t port_number);
    };
};

#endif // MESSAGE_GATE_H