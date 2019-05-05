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

static bool is_valid(char *msg)
{
    if (!strncmp(msg, "Session Timeout", 15) ||
    !strncmp(msg, "Protocol Mismatch", 17))
        return (false);
    return (true);
}

static int show_secret(char *msg, ssize_t res)
{
    if (is_valid(msg) == false)
        return (-1);
    if (!strncmp(msg, "KO", 2)) {
        printf("KO\n");
        return (0);
    }
    printf("Secret: '");
    for (ssize_t i = 0; i < res; i++)
        printf("%c", msg[i]);
    printf("'\n");
    return (0);
}

int authentificate(cli_t *cli)
{
    char msg[BUFSIZ] = {0};
    char newmsg[BUFSIZ] = {0};
    ssize_t res;

    socket_write(cli, "client hello", 12);
    res = socket_read(cli, msg, BUFSIZ);
    if (is_valid(msg) == false || res != 10)
        return (-1);
    memcpy(newmsg, msg, 10);
    memcpy(newmsg + 10, cli->password, strlen(cli->password));
    sha256(newmsg, msg, cli->password);
    socket_write(cli, msg, 64);
    res = socket_read(cli, msg, BUFSIZ);
    return (show_secret(msg, res));
}

int main(int ac, char **av)
{
    cli_t cli = {0};

    if (parsing(&cli, ac, av) == -1)
        return (84);
    if (create_cli(&cli) == -1)
        return (84);
    while (authentificate(&cli));
    destroy_cli(&cli);
    return (EXIT_SUCCESS);
}