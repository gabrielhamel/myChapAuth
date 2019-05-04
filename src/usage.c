/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** usage
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "mychap.h"

static size_t get_short_len(void)
{
    size_t len = 1;
    __uint16_t nb = __UINT16_MAX__;

    while (nb > 9) {
        nb /= 10;
        len++;
    }
    return (len);
}

static bool check_server_port(const char *port)
{
    size_t offset = 0;
    size_t len;

    if (!strlen(port))
        return (false);
    for (size_t idx = 0; port[idx] != '\0'; idx++)
        if (isdigit(port[idx]) == false)
            return (false);
    for (; port[offset] == '0'; offset++);
    len = strlen(port + offset);
    if (len == 0 || len > get_short_len() ||
    strtol(port, NULL, 10) > __UINT16_MAX__)
        return (false);
    return (true);
}

in_addr_t extract_ip(char *ip)
{
    struct hostent *he;
    struct in_addr **addr_list;

    he = gethostbyname(ip);
    if (he == NULL) {
        dprintf(STDERR_FILENO, "Invalid ip\n");
        return (0);
    }
    addr_list = (struct in_addr **)he->h_addr_list;
    for (size_t i = 0; addr_list[i] != NULL; i++)
        return (inet_addr(inet_ntoa(*addr_list[i])));
    dprintf(STDERR_FILENO, "Invalid ip\n");
    return (0);
}

in_port_t extract_port(char *port)
{
    if (check_server_port(port) == false) {
        dprintf(STDERR_FILENO, "Invalid port\n");
        return (0);
    }
    return (htons(strtol(port, NULL, 10)));
}