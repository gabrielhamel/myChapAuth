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

int main(int ac, char **av)
{
    cli_t cli = {0};

    if (parsing(&cli, ac, av) == -1)
        return (84);
    if (create_cli(&cli) == -1)
        return (84);
    socket_write(&cli, "client hello", 12);
    socket_read(&cli);
    destroy_cli(&cli);
    return (EXIT_SUCCESS);
}