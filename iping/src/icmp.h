#ifndef EXERT_LINUX_ICMP_H
#define EXERT_LINUX_ICMP_H

#include <stdint.h>
#include <asm/byteorder.h>

// ICMP 头
typedef struct icmpheader_s
{
    uint8_t type;      // 8：请求；0：应答；13：时间戳请求；14：时间戳应答；17：地址掩码请求；18：地址掩码应答；10：路由请求；9：路由宣告
    uint8_t code;      // 0
    uint16_t checksum; // 校验和
    union
    {
        struct
        {
            uint16_t id;
            uint16_t sequence;
        } echo;
        uint32_t gateway;
        struct
        {
            uint16_t unused;
            uint16_t mtu;
        } frag;
    } un;
    uint32_t icmp_timestamp[2];
    uint8_t data[0];
} icmpheader_t;

// IP 头
typedef struct ipheader_s
{
    // 版本（4bit）首部长度（4bit）
#ifdef __LITTLE_ENDIAN_BITFIELD
    uint8_t header_length : 4, version : 4;
#else
    uint8_t version : 4, header_length : 4;
#endif
    uint8_t type;          // 服务类型
    uint16_t total_length; // 总长度
    uint16_t id;           // 标识
    // 标识（3bit）片偏移（13位）
#ifdef __LITTLE_ENDIAN_BITFIELD
    uint16_t offset : 13, flag : 3;
#else
    uint16_t flag : 3, offset : 13;
#endif
    uint8_t ttl;                  // 生存时间 TTL
    uint8_t protocol;             // 协议类型
    uint16_t checksum;            // 头部校验和
    uint32_t source_address;      // 源 IP 地址
    uint32_t destination_address; // 目标 IP 地址
} ipheader_t;

/* 校验和 */
unsigned short check_sum(uint16_t *addr, int len)
{
    int sum = 0;
    int nleft = len;
    /* 每 2 字节累加 */
    while (nleft > 1)
    {
        sum += *addr++;
        nleft -= 2;
    }
    /* 长度奇数补偶 */
    if (nleft == 1)
    {
        uint16_t temp = *(uint8_t *)addr;
        temp = (temp << 8) & 0xFF;
        sum += temp;
    }
    /* 高低位相加 */
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return ~sum;
}



#endif
