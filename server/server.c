/*
* @file main.c
* @author Renat Kagal <kagal@itspartner.net>
*
* Assembling : gcc -Wall main.c -pthread -o main
*
* Description : server in chat
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

#include "head_s.h"

#define BUFF_SIZE 1024

int main () {
	int sock, listener_sock;
	struct sockaddr_in addr;
	
	char buff[BUFF_SIZE];
	memset (buff,  '\0', BUFF_SIZE);	

	if ((listener_sock = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
		puts ("Failed creating socket");
		exit (EXIT_FAILURE);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons (1321);
	addr.sin_addr.s_addr = htonl (INADDR_ANY);
	
	if (bind (listener_sock, (struct sockaddr *) &addr, sizeof (addr)) < 0) {
		puts ("Failed bind");
		exit (EXIT_FAILURE);
	}
	listen (listener_sock, 1);

	if ((sock = accept (listener_sock, NULL, NULL)) < 0) {
		puts ("Failed accept sock");
		exit (EXIT_FAILURE);
	}

	while (1) {
		if ((recv (sock, buff, 1024, 0)) <= 0){
			break;
		}
		printf ("%s", buff);
		memset (buff,  '\0', BUFF_SIZE);
	}
	close (sock);
	close (listener_sock);
}