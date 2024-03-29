#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define h_addr h_addr_list[0]
#define DIM_BUFF 1024

int main(int argc, char *argv[])
{
	int sd, port, nread, fd;
	char buff[DIM_BUFF], nomeFile[256];
	char message[10];
	char response[10];
	struct hostent *host;
	struct sockaddr_in servaddr;
	int size, stringSize;

	/* CONTROLLO ARGOMENTI ---------------------------------- */
	if (argc != 3)
	{
		printf("Error:%s serverAddress serverPort\n", argv[0]);
		exit(1);
	}

	/* INIZIALIZZAZIONE INDIRIZZO SERVER -------------------------- */
	memset((char *)&servaddr, 0, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	host = gethostbyname(argv[1]);

	/*VERIFICA INTERO*/
	nread = 0;
	while (argv[2][nread] != '\0')
	{
		if ((argv[2][nread] < '0') || (argv[2][nread] > '9'))
		{
			printf("Secondo argomento non intero\n");
			exit(2);
		}
		nread++;
	}
	port = atoi(argv[2]);

	/* VERIFICA PORT e HOST */
	if (port < 1024 || port > 65535)
	{
		printf("%s = porta scorretta...\n", argv[2]);
		exit(2);
	}
	if (host == NULL)
	{
		printf("%s not found in /etc/hosts\n", argv[1]);
		exit(2);
	}
	else
	{
		servaddr.sin_addr.s_addr = ((struct in_addr *)(host->h_addr))->s_addr;
		servaddr.sin_port = htons(port);
	}
	/* CREAZIONE SOCKET ------------------------------------ */
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0)
	{
		perror("apertura socket");
		exit(1);
	}
	printf("Client: creata la socket sd=%d\n", sd);

	/* Operazione di BIND implicita nella connect */
	if (connect(sd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) < 0)
	{
		perror("connect");
		exit(1);
	}
	printf("Client: connect ok\n");

	/* CORPO DEL CLIENT:
	ciclo di accettazione di richieste da utente ------- */
	char *operazione = "Inserire message, EOF per terminare: ";
	printf("%s", operazione);

	while (gets(message))
	{
		write(sd, message, strlen(message) + 1);

		// ricezione messaggio
		read(sd, response, 10);

		printf("response: %s\n", response);
	}

	close(sd);
	printf("\nClient: termino...\n");
	exit(0);
}