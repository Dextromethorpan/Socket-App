//Archivo para el Cliente

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>
#include "chat.cpp"


#define PORT 8080

using namespace std;

int main(int argc, char const *argv[]) 
{ 
    //Estructura del Socket para el Cliente
    struct hostent* host = gethostbyname("192.168.1.10");
    sockaddr_in serverAddress;
    bzero((char*)&serverAddress, sizeof(serverAddress)); 
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    serverAddress.sin_port = htons(PORT);
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		cout<<"\n Error al Crear el Socket \n"; 
		return -1; 
	}   

	if (connect(sock, (struct sockaddr *)&serverAddress, sizeof(serv_addr)) < 0) 
	{ 
		cout<<"\n Error en la Conexión \n"; 
		return -1; 
	}

    char ingreso[100000];
    int turno = 2;
    
    //Declaración del Objeto chat_
    chat chat_ = chat(sock,true);
    
    while(chat_.estaActivo())
    { 
        if(turno == 1){
            chat_._read();
            turno = 2;
        }
        else {
            cin.clear();
            cin.getline(ingreso,100000,'\n');
            chat_._send(ingreso);
            turno = 1;
        }
    }

    //Cierrro la Conexión Socket para el Cliente
    close(sock);
	return 0; 
} 

