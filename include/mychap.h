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
#include <linux/udp.h>

#define MSGSIZE 65535

typedef struct {
    int fd;
    struct sockaddr_in addr;
    socklen_t size_struct;
} cli_t;

typedef struct {
    struct ip ip;
    struct udphdr head;
    char message[MSGSIZE];
} __attribute__((packed)) packet_t;

ssize_t sockwrite(cli_t *sock, void *buf, size_t n);
cli_t *init_socket(in_addr_t ip, in_port_t port);
void close_socket(cli_t *socket);

#endif