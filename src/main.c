/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** main
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <openssl/sha.h>
#include "mychap.h"

static void sha256(char *to_encrypt, char *buffer, char *password)
{
    SHA256_CTX sha;
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_Init(&sha);
    SHA256_Update(&sha, to_encrypt, 10 + strlen(password));
    SHA256_Final(hash, &sha);
    memset(buffer, '\0', BUFSIZ);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(buffer + (i * 2), "%02x", hash[i]);
    buffer[64] = '\0';
}

void authentificate(cli_t *cli)
{
    char msg[BUFSIZ] = {0};
    char newmsg[BUFSIZ] = {0};

    socket_write(cli, "client hello", 12);
    socket_read(cli, msg, BUFSIZ);
    memcpy(newmsg, msg, 10);
    memcpy(newmsg + 10, cli->password, strlen(cli->password));
    sha256(newmsg, msg, cli->password);
    socket_write(cli, msg, 64);
}

int main(int ac, char **av)
{
    cli_t cli = {0};

    if (parsing(&cli, ac, av) == -1)
        return (84);
    if (create_cli(&cli) == -1)
        return (84);
    authentificate(&cli);
    destroy_cli(&cli);
    return (EXIT_SUCCESS);
}