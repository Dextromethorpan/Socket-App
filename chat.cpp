//Archivo chat.cpp 
//Archivo para el chat 

#define ACTIVO true
#define INACTIVO false
#define CLAVE_FINALIZAR "Adios"

#include <iostream>		

#include <sys/socket.h> 
#include <arpa/inet.h>	
#include <unistd.h>
#include <netdb.h>
#include "chat.h"

using namespace std;

//Definición del Constructor
//Por Defecto
chat::chat(){};

//Por Pase de Argumentos
chat::chat(int _socket, bool _esCliente)
{   
    socket = _socket;
    esCliente = _esCliente;
    estado = ACTIVO;
    if(esCliente){
        cout<<"Cliente: "<<endl;
    }
}

//Destructor
//chat::~chat(){}



//Definición de los Métodos

//Definición del Método Inactivar
void chat::inactivar(void)
{
    cout<<"\nChat Finalizado\n";
    estado = INACTIVO;
};

//Definición del Método Activar
bool chat::estaActivo(void)
{
    return estado == ACTIVO;
};


//Definición del Método Lectura
void chat::_read(void)
{
    char buffer[1024] ={0};
    read( socket , buffer, 1024);
    if(esCliente){
        cout<<"Servidor: "<<endl;
    } else{
        cout<<"Cliente: "<<endl;
    }
    cout<<buffer<<endl;
    if(strcmp(buffer,CLAVE_FINALIZAR) == 0)
    {
        chat::inactivar();
        return;
    }
    if(!esCliente){
        cout<<"Servidor: "<<endl;
    } else{
        cout<<"Cliente: "<<endl;
    }
};

//Definición del Método Envío
void chat::_send(char mensaje[])
{
    send(socket , mensaje , strlen(mensaje) , 0 );
    if(strcmp(mensaje,CLAVE_FINALIZAR) == 0)
    {
        chat::inactivar();
        return;
    }
}
