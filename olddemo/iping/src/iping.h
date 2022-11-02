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

int parse_packet(uint8_t *buff, int len)
{
    struct iphdr *iphead = (struct iphdr *)buff;
    struct in_addr addr;
    addr.s_addr = iphead->saddr;
    printf("comefrom ip=%s  ", inet_ntoa(addr));
    struct icmp *icmp = (struct icmp *)(buff + sizeof(struct iphdr));

    if (check_sum((uint16_t *)icmp, len - sizeof(struct iphdr)) > 1)
    {
        printf("revc check error\n");
        return -5;
    }
    
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

void fill_packet(uint8_t *sendbuf, int packsize) {
    struct icmp *icmp = (struct icmp *)sendbuf;
    icmp->icmp_type = ICMP_ECHO;
    icmp->icmp_code = 0;
    icmp->icmp_id = getpid();
    icmp->icmp_seq = ++nsent;
    struct timeval *tval = (struct timeval *)icmp->icmp_data;
    gettimeofday(tval, 0);
    icmp->icmp_cksum = check_sum((uint16_t *)icmp, packsize);
}

int iping(const char *address)
{
    struct protoent *protocal = getprotobyname("icmp");
    int sockfd = socket(AF_INET, SOCK_RAW, protocal->p_proto);
    // int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    struct timeval recvto;
    recvto.tv_sec = 5;
    recvto.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &recvto, sizeof(recvto));
    if (sockfd < 0)
    {
        perror("socket open error");
        return -3;
    }
    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = inet_addr(address);
    dest.sin_family = PF_INET;
    dest.sin_port = ntohs(0);

    uint8_t sendbuf[PACKET_SIZE];
    uint8_t recvbuf[PACKET_SIZE];
    int packsize = 8 + 56;
    fill_packet(sendbuf, packsize);
    if (sendto(sockfd, sendbuf, packsize, 0, (struct sockaddr *)&dest, sizeof(dest)) < 0)
    {
        perror("sendto error");
        return -1;
    }
    printf("sendto %s\n", address);

    struct sockaddr_in source;
    memset(&source, 0, sizeof(source));
    socklen_t srclen = 0;
    int retval = recvfrom(sockfd, recvbuf, PACKET_SIZE, 0, (struct sockaddr *)&source, &srclen);
    if (retval <= 0)
    {
        perror("recv error");
        return -2;
    }
    printf("recv %s\n", address);
    parse_packet(recvbuf, retval);
    return 0;
}

#endif
