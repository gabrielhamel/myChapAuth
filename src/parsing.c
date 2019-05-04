/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** parsing
*/

#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include "mychap.h"

static const struct option options[] = {
    {"target", required_argument, NULL, 't'},
    {"port", required_argument, NULL, 'p'},
    {"password", required_argument, NULL, 'P'},
    {NULL, 0, NULL, 0}
};

int parsing(cli_t *cli, int ac, char **av)
{
    int idx = 0;
    int opt;

    while ((opt = getopt_long(ac, av, "t:p:P:", options, &idx)) != -1) {
        switch (opt) {
            case 't':
                cli->ip = optarg;
            break;
            case 'p':
                cli->port = optarg;
            break;
            case 'P':
                cli->password = optarg;
            break;
            default:
                return (-1);
        }
    }
    if (cli->ip && cli->port && cli->password)
        return (0);
    return (-1);
}