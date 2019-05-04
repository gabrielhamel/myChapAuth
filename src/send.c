/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** send
*/

#include <linux/if_ether.h>
#include <stdlib.h>
#include <string.h>
#include "mychap.h"

static size_t make_udp_hdr(cli_t *cli, struct udphdr *packet, size_t size)
{
    packet->source = cli->saddr.sin_port;
    packet->dest = cli->daddr.sin_port;
    packet->len = htons(UDPHDR_SIZE + size);
    return (UDPHDR_SIZE + size);
}

static size_t make_ip_hdr(cli_t *cli, struct iphdr *packet, size_t size)
{
    packet->version = 4;
    packet->ihl = INETHDR_SIZE;
    packet->tot_len = htons(INETHDR_SIZE * 4 + size);
    packet->ttl = 64;
    packet->protocol = IPPROTO_UDP;
    packet->saddr = cli->saddr.sin_addr.s_addr;
    packet->daddr = cli->daddr.sin_addr.s_addr;
    return (sizeof(struct iphdr) + size);
}

ssize_t socket_write(cli_t *cli, void *buf, size_t count)
{
    uint8_t packet[ETH_DATA_LEN] = {0};
    size_t size = 0;

    memcpy(packet + sizeof(struct iphdr) + sizeof(struct udphdr), buf, count);
    size = make_udp_hdr(cli, (void *)packet + sizeof(struct iphdr), count);
    size = make_ip_hdr(cli, (void *)packet, size);
    return (sendto(cli->ext, packet, size, 0, (struct sockaddr *)
    &(cli->daddr), sizeof(struct sockaddr_in)));
}

ssize_t socket_read(cli_t *cli, void *buf, size_t count)
{
    uint8_t packet[ETH_DATA_LEN] = {0};
    socklen_t size = sizeof(struct sockaddr_in);
    ssize_t res;
    in_port_t port = cli->daddr.sin_port;

    recvfrom(cli->ext, packet, ETH_DATA_LEN, 0,
    (struct sockaddr *)&(cli->daddr), &size);
    cli->daddr.sin_port = port;
    res = recvfrom(cli->ext, packet, ETH_DATA_LEN, 0,
    (struct sockaddr *)&(cli->daddr), &size);
    if (res > 0)
        memcpy(buf, packet + sizeof(struct iphdr) +
        sizeof(struct udphdr), count);
    cli->daddr.sin_port = port;
    return (res - sizeof(struct iphdr) - sizeof(struct udphdr));
}