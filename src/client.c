/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** client
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "mychap.h"

static int create_socket(void)
{
    int fd = -1;
    int no = 0;
    socklen_t int_size = sizeof(int);

    if ((fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) == -1)
        return (-1);
    if (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &no, int_size) == -1) {
        close(fd);
        return (-1);
    }
    return (fd);
}

cli_t *init_socket(in_addr_t ip, in_port_t port)
{
    cli_t *cli = malloc(sizeof(cli_t));

    if (cli == NULL)
        return (NULL);
    cli->addr.sin_family = AF_INET;
    cli->addr.sin_port = port;
    cli->addr.sin_addr.s_addr = ip;
    if ((cli->fd = create_socket()) == -1) {
        free(cli);
        return (NULL);
    }
    return (cli);
}

void close_socket(cli_t *socket)
{
    close(socket->fd);
    free(socket);
}

ssize_t sockwrite(cli_t *sock, void *buf, size_t n)
{
    socklen_t len = sizeof(struct sockaddr_in);
    struct 

    return (sendto(sock->fd, buf, n, 0, (struct sockaddr *)
    &sock->addr, len));
}