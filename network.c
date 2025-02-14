/**
 * This program takes a hostname and port as cmd-line args, connects using TCP/IPv4 to the given port
 * on the given hostname, reads data from the remote service until the server closes the connection,
 * and prints the read data to standard out.
 *
 * Author: Isabella Breuhl
 * Date: 09-22-2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Bad input\n");
        	exit(1);
	}

	int exitcode = EXIT_FAILURE;
	int sockfd = -1;
	int status;
	ssize_t size;
	struct addrinfo hints = { .ai_socktype = SOCK_STREAM };
	struct addrinfo *servinfo = NULL, *p;
	char buf[1024];

	status = getaddrinfo(argv[1], argv[2], &hints, &servinfo);

	if (status != 0) {
		fprintf(stderr, "Error looking up hostname: %s\n", gai_strerror(status));
		exit(1);
	}

	for (p = servinfo; p != NULL; p = p->ai_next) {
		sockfd = socket(p->ai_family, p->ai_socktype, 0);
		if (-1 == sockfd) {
			continue;
		}

		if (-1 == connect(sockfd, p->ai_addr, p->ai_addrlen)) {
			close(sockfd);
			sockfd = -1;
			continue;
		}

		break;
	}

	if (sockfd == -1) {
		fprintf(stderr, "Failed to connect\n");
		exit(1);
	}

	for (;;) {
		size = recv(sockfd, buf, 1024 - 1, 0);
		if (0 == size) {
			break;
		} else if (size > 0) {
			write(STDOUT_FILENO, buf, size);
		} else {
			perror("Error reading from socket");
			goto done;
		}
	}

	exitcode = EXIT_SUCCESS;

done:
	if (-1 != sockfd) {
		close(sockfd);
	}

	if (NULL != servinfo) {
		freeaddrinfo(servinfo);
	}

	exit(exitcode);
}
