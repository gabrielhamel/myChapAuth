/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** main
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "mychap.h"

#include <string.h>
#include <unistd.h>
#include <errno.h>

static bool check_sudo(void)
{
    int id = getuid();

    if (id != 0) {
        printf("Error: you doesn't run with root user\n");
        return (false);
    }
    return (true);
}

int main(int ac, char **av)
{
    cli_t *cli;

    if (check_sudo() == false)
        return (84);
    cli = create_cli(av[1], av[2]);
    if (cli == NULL)
        return (84);
    socket_write(cli, "client hello", 12);
    printf("%s\n", socket_read(cli));
    destroy_cli(cli);
    return (EXIT_SUCCESS);
}