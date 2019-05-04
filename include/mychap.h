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
#include <linux/if_ether.h>
#include <netinet/udp.h>

#define INETHDR_SIZE 5
#define UDPHDR_SIZE 8
#define MSG_SIZE 1024
#define SALE 4242

typedef struct {
    char *ip;
    char *port;
    char *password;
    int ext;
    struct sockaddr_in daddr;
    struct sockaddr_in saddr;
} cli_t;

int create_cli(cli_t *cli);
void destroy_cli(cli_t *cli);
ssize_t socket_write(cli_t *cli, void *buf, size_t count);
char *socket_read(cli_t *cli);
in_addr_t extract_ip(char *ip);
in_port_t extract_port(char *port);
in_addr_t get_local_ip(void);
int parsing(cli_t *cli, int ac, char **av);

#endif