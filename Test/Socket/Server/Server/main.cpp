#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    //socket（int af, int type, int protocol）
    //af：AF为地址家族Address Family，AF_INET表示IPv4，AF_INET6表示IPv6.
    //type：SOCK_STREAM表示面向连接TCP，SOCK_DGRAM表示无连接UDP
    //protocol：协议类型，IPPROTO_TCP和IPPROTO_UDP
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //struct sockaddr_in {
    //    sa_family_t     sin_family;   //地址族（Address Family），也就是地址类型
    //    uint16_t        sin_port;     //16位的端口号
    //    struct in_addr  sin_addr;     //32位IP地址
    //    char            sin_zero[8];  //不使用，一般用0填充
    //};
    //1.af
    //2.sin_port：端口号16位两个字节，0~1023为系统特定服务程序，Web服务80，FTP服务21
    //所以我们的程序尽量在1024~65536
    //3.struct in_addr：结构体变量，IP地址

    //sockadd：通用结构体
    //sockaddr_in：将af和ip地址端口号分离，IPv4专用
    //sockaddr_in6：IPv6
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    //绑定套接字，只有流经该ip和对应端口的数据才能交给套接字处理
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //监听套接字
    //只是让套接字处于监听状态，并没有接收请求。
    listen(serv_sock, 20);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    //接受客户端请求
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

    char str[] = "Hello World!";
    write(clnt_sock, str, sizeof(str));

    close(clnt_sock);
    close(serv_sock);

    return 0;
}