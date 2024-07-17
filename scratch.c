#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#define __USE_MISC 1
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>	
#include <netinet/in.h>
#include <netdb.h>

#define DOG "x\ \ x"

int main(){
	in_addr_t addr = inet_addr("127.0.0.1");
	printf("addr: %d\n", addr);
	EOF;
	printf("EOF is %d\n", EOF);

	printf("atoi: %i\n", atoi("0"));
	printf("atoi: %i\n", atoi("cane"));


	puts("0");

	for (int i = 0; i < strlen("0"); i++){
		printf("isdigit: %i\n", isdigit("0"[i]));
	}

	puts("cane");

	for (int i = 0; i < strlen("cane"); i++){
		printf("isdigit: %i\n", isdigit("cane"[i]));
	}

	printf("SHUT_RD: %i\n", SHUT_RD);
	printf("SHUT_WR: %i\n", SHUT_WR);
	printf("SHUT_RDWR: %i\n", SHUT_RDWR);


	printf("SIG_IGN: %i\n", SIG_IGN);

	unsigned short s = 65535;
	printf("%hu\n", ~(s & 1));
	printf("%hu\n", ~s & ~1);


	printf(DOG);
	printf("\n");

	int y;
	int x = (y = 10);

	FD_SETSIZE;

	printf("assignment: %i\n", x);


	printf("%i\n", 0b0001);
	printf("%i\n", 0b0010);
	printf("%i\n", 0b0001 & 0b0010);
	printf("%i\n", 0b0001 | 0b0010);

	printf("%i\n", 0b0001 << 1); // 0b0010
	printf("%i\n", 0b0001 << 2); // 0b0100
	printf("%i\n", 0b0001 << 3); // 0b1000
}
