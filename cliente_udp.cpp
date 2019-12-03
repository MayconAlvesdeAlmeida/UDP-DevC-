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

	// Iniciando winsock
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
	struct sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(9002);
	//hint.sin_addr.s_addr = INADDR_ANY;
	
	// Caso utilize maquinas diferentes, coloque o ip do servidor em inet_addr
	hint.sin_addr.s_addr = inet_addr("127.0.0.1");
	int len = sizeof(hint);
	
	// loop: enviando e recebendo mensagens
	while (1)
	{
		ZeroMemory(server_message,100);
		ZeroMemory(client_message, 100);
		printf("Cliente: ");
		fgets(client_message, 100, stdin);
		sendto(listening,client_message,100,0,(struct sockaddr*)&hint,sizeof(hint));
		
		printf("AGUARDANDO ...\n");
		recvfrom(listening,server_message,100,0,(struct sockaddr*)&hint,&len);
		printf("Mensagem do servidor: %s\n",server_message);

	}
	// Close the socket
	closesocket(listening);

	// Shutdown winsock
	WSACleanup();

	getchar();
	return 0;
}
