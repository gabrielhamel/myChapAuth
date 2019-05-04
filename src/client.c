/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** client
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "mychap.h"

static int create_socket(void)
{
    int fd = -1;

    if ((fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) == -1)
        return (-1);
    return (fd);
}

static int init_socket_cli(cli_t *cli, in_addr_t ip, in_port_t port)
{
    socklen_t int_size = sizeof(int);
    int no = 1;

    cli->daddr.sin_family = AF_INET;
    cli->daddr.sin_port = port;
    cli->daddr.sin_addr.s_addr = ip;
    if ((cli->ext = create_socket()) == -1 || setsockopt(cli->ext,
    IPPROTO_IP, IP_HDRINCL, &no, int_size) == -1)
        return (-1);
    return (0);
}

static int init_socket_serv(cli_t *cli)
{
    int no = 1;
    socklen_t int_size = sizeof(int);

    if (setsockopt(cli->ext, SOL_SOCKET, SO_REUSEADDR, &no, int_size) == -1)
        return (-1);
    cli->saddr.sin_port = htons(SALE);
    cli->saddr.sin_family = AF_INET;
    cli->saddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(cli->ext, (struct sockaddr *)&cli->saddr,
    sizeof(struct sockaddr_in)) == -1)
        return (-1);
    cli->saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    return (0);
}

int create_cli(cli_t *cli)
{
    in_addr_t nip = extract_ip(cli->ip);
    in_port_t nport = extract_port(cli->port);

    if (nip == 0 || nport == 0)
        return (-1);
    if (init_socket_cli(cli, nip, nport) == -1 ||
    init_socket_serv(cli) == -1) {
        destroy_cli(cli);
        return (-1);
    }
    return (0);
}

void destroy_cli(cli_t *cli)
{
    close(cli->ext);
}