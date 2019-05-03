/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** mychap
*/

#ifndef MYCHAP_H
#define MYCHAP_H

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

#define INETHDR_SIZE 5
#define UDPHDR_SIZE 8
#define MSG_SIZE 1024
#define SALE 4242

typedef struct {
    int ext;
    struct sockaddr_in daddr;
    struct sockaddr_in saddr;
} cli_t;

typedef struct {
    struct iphdr ip_hdr;
    struct udphdr udp_hdr;
} __attribute__((packed)) packet_t;

cli_t *create_cli(char *ip, char *port);
void destroy_cli(cli_t *cli);
ssize_t socket_write(cli_t *cli, void *buf, size_t count);
char *socket_read(cli_t *cli);
in_addr_t extract_ip(char *ip);
in_port_t extract_port(char *port);

#endif