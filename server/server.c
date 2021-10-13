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
	struct sockaddr_un addr;
	
	char* path = "/home/kagal/c/chat/text.txt";

	char buff[BUFF_SIZE];
	memset (buff,  '\0', BUFF_SIZE);	

	if ((listener_sock = socket (AF_UNIX, SOCK_STREAM, 0)) < 0) {
		puts ("Failed creating socket");
		exit (EXIT_FAILURE);
	}
	addr.sun_family = AF_UNIX;

	remove ("/home/kagal/c/chat/text.txt");
	strcpy (addr.sun_path, path);

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
	remove ("/home/kagal/c/chat/text.txt");
}