/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** main
*/

#include <stdlib.h>
#include <stdio.h>
#include "mychap.h"

int main(int ac, char **av)
{
    cli_t *cli = init_socket(0x100007f, 0x901f);

    if (cli == NULL)
        perror("Cannot connect to server");
    if (sockwrite(cli, "salut", 5) == -1)
        perror("Cannot write");
    close_socket(cli);
    return (EXIT_SUCCESS);
}