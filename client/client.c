/*
* @file main.c
* @author Renat Kagal <kagal@itspartner.net>
*
* Assembling : gcc -Wall main.c -pthread -o main
*
* Description : program writes numbers from each thread to file 
*
* Copyright (c) 2021, ITS Partner LLC.
* All rights reserved.
*
* This software is the confidential and proprietary information of
* ITS Partner LLC. ("Confidential Information"). You shall not
* disclose such Confidential Information and shall use it only in
* accordance with the terms of the license agreement you entered into
* with ITS Partner.
*/

#include "head_c.h"

#define MESS_SIZE 1024

int main () {
    int sock;
    struct sockaddr_in addr;

    if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        puts ("Failed creating socket");
        exit (EXIT_FAILURE);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons (3425);
    addr.sin_addr.s_addr = htonl (INADDR_LOOPBACK);

    if (connect (sock, (struct sockaddr*) &addr, sizeof (addr)) < 0) {
        puts ("Failed connection");
        exit (EXIT_FAILURE);
    }
    char mess[MESS_SIZE];

    while (scanf ("%s", mess)) {
        if (strcmp (mess, "stop") == 0)
            break;
        if ((send (sock, mess, sizeof (mess), 0)) < 0){
            puts ("Failed send mess");
            exit (EXIT_FAILURE);
        }
    }
    close (sock);
}