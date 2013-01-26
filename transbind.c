#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef IPV6_TRANSPARENT
#define IPV6_TRANSPARENT 75
#endif

int bind(int s, const struct sockaddr *sa, socklen_t len)
{
	unsigned one = 1;
	int success = 0;
	char straddr[INET6_ADDRSTRLEN];
	
	switch (sa->sa_family) {
		case AF_INET:
			if ((setsockopt(s, SOL_IP, IP_TRANSPARENT, &one, sizeof(one)) == 0)
			    || (setsockopt(s, SOL_IP, IP_FREEBIND, &one, sizeof(one)) == 0)) {
				success = 1;
			}
			fprintf(stderr, "Enabling transparent bind on %s:%d : %s\n",
				inet_ntop(AF_INET, &((struct sockaddr_in*)sa)->sin_addr, straddr, sizeof(straddr)),
				ntohs(((struct sockaddr_in*)sa)->sin_port),
				success ? "success" : "failed"
      			);
		break;
		case AF_INET6:
			if (setsockopt(s, SOL_IPV6, IPV6_TRANSPARENT, &one, sizeof(one)) == 0) {
				success = 1;
			}
			fprintf(stderr, "Enabling transparent bind on [%s]:%d : %s\n",
				inet_ntop(AF_INET6, &((struct sockaddr_in6*)sa)->sin6_addr, straddr, sizeof(straddr)),
				ntohs(((struct sockaddr_in6*)sa)->sin6_port),
				success ? "success" : "failed"
      			);
		break;
	}
	return syscall(SYS_bind, s, sa, len);
}
