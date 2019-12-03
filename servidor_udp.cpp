#include<stdio.h>
#include<WS2tcpip.h>

/*
Autor : Maycon Almeida

1) Criar um projeto no dev C++
2) Configurar o projeto, clicando em Projeto/Opções do Projeto
Depois clicar em Paramêtros/Adicionar Bibliotecas.
Selecionar as bibliotecas: libws2_32.a e libwsock32.a

*/



int main()
{
	char server_message[100];
	char client_message[100];

	// Iniciando o winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsok = WSAStartup(ver, &wsData);
	if (wsok != 0)
	{
		printf("Nao foi possivel iniciar o socket\n");
		return 0;
	}

	// Criando o socket	
	SOCKET listening = socket(AF_INET, SOCK_DGRAM, 0);
	if (listening == INVALID_SOCKET)
	{
		printf("Nao foi possivel criar o socket\n");
		return 0;
	}

	// Bind the socket 
	struct sockaddr_in hint, cliaddr;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(9002);
	hint.sin_addr.s_addr = INADDR_ANY;
	int len = sizeof(cliaddr);

	bind(listening, (struct sockaddr*)&hint, sizeof(hint));

	
	//  loop: enviando e recebendo msgs
	while (1)
	{
		ZeroMemory(server_message,100);
		ZeroMemory(client_message, 100);
		printf("AGUARDANDO ...\n");
		recvfrom(listening,client_message,100,0,(struct sockaddr*)&cliaddr,&len);
		printf("Mensagem do clinte: %s\n",client_message);

		printf("Servidor: ");
		fgets(server_message, 100, stdin);

		sendto(listening,server_message,100,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
		
	}
	// Close the socket
	closesocket(listening);

	// Shutdown winsock
	WSACleanup();

	getchar();
	return 0;
}
