//Archivo para el Servidor 

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <iostream>
#include "chat.cpp"



#define PORT 8080

using namespace std;

int main(int argc, char const *argv[]) 
{ 
	
	//Establecimiento para el Socket del Servidor
	int new_socket;
	
	
	int server_fd;
	struct sockaddr_in address; 
	 
	int addrlen = sizeof(address); 
	
	
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		cout<<"socket failed"; 
		exit(EXIT_FAILURE); 
	} 
	 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		cout<<"bind failed"; 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) 
	{ 
		cout<<"listen"; 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		cout<<"accept"; 
		exit(EXIT_FAILURE); 
	}
	
	

    char ingreso[100000];
    int turno = 1;
    
	//Declaración del objeto chat_
	chat chat_=chat(new_socket,false);
    cout<<"Esperando a que el cliente escriba...\n";
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
    
	//Cierre de la Conexión de Socket para el Servidor
	close(new_socket);  
	return 0; 
} 

