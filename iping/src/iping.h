#ifndef EXERT_LINUX_IPING
#define EXERT_LINUX_IPING

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "icmp.h"

int iping(const char *address)
{
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0)
    {
        return -1;
    }
    int nsent = 0;
    uint8_t sendbuf[1500];
    icmpheader_t *icmpp = (icmpheader_t*)sendbuf;
    icmpp->type = 8;// ICMP_ECHO
    icmpp->code = 0;
    icmpp->un.echo.id = getpid();
    icmpp->un.echo.sequence = ++nsent;
}

#endif
