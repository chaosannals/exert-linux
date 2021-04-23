#ifndef EXERT_LINUX_IPING_H
#define EXERT_LINUX_IPING_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/ip_icmp.h>
#include "icmp.h"

#define PACKET_SIZE 4096

int nsent = 0;

int parse_packet(char *buff, int len)
{
    struct iphdr *iphead = (struct iphdr *)buff;
    struct in_addr addr;
    addr.s_addr = iphead->saddr;
    printf("comefrom ip=%s  ", inet_ntoa(addr));
    struct icmp *icmp = (struct icmp *)(buff + sizeof(struct iphdr));

    // if (check_sum((uint16_t *)icmp, len - sizeof(struct iphdr)) > 1)
    // {
    //     printf("revc check error\n");
    //     return -5;
    // }
    
    struct timeval nv;
    gettimeofday(&nv, 0);
    struct timeval *tval = (struct timeval *)icmp->icmp_data;
    printf(
        "type=%d seq=%d id=%d pid=%d usec=%d \n",
        icmp->icmp_type,
        icmp->icmp_seq,
        icmp->icmp_id,
        getpid(),
        (int)(nv.tv_usec - tval->tv_usec));
}

int iping(const char *address)
{
    struct protoent *protocal = getprotobyname("icmp");
    int sockfd = socket(AF_INET, SOCK_RAW, protocal->p_proto);
    if (sockfd < 0)
    {
        return -1;
    }
    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(dest));
    dest.sin_family = PF_INET;
    dest.sin_port = ntohs(0);

    uint8_t sendbuf[PACKET_SIZE];
    uint8_t recvbuf[PACKET_SIZE];
    struct icmp *icmp = (struct icmp *)sendbuf;
    icmp->icmp_type = ICMP_ECHO;
    icmp->icmp_code = 0;
    icmp->icmp_id = getpid();
    icmp->icmp_seq = ++nsent;
    struct timeval *tval = (struct timeval *)icmp->icmp_data;
    int packsize = 8 + 56;
    icmp->icmp_cksum = check_sum((uint16_t *)icmp, packsize);
    gettimeofday(tval, 0);
    if (sendto(sockfd, sendbuf, packsize, 0, (struct sockaddr *)&dest, sizeof(dest)) < 0)
    {
        perror("sendto error");
        return -1;
    }

    // struct sockaddr_in source;
    // memset(&source, 0, sizeof(source));
    // socklen_t srclen = sizeof(source);
    // int retval = recvfrom(sockfd, recvbuf, PACKET_SIZE, 0, (struct sockaddr *)&source, &srclen);
    socklen_t  destlen = sizeof(dest);
    int retval = recvfrom(sockfd, recvbuf, PACKET_SIZE, 0, (struct sockaddr *)&dest, &destlen);
    if (retval <= 0)
    {
        perror("recv error");
        return -2;
    }
    parse_packet((char *)recvbuf, retval);
}

#endif
