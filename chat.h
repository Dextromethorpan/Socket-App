//Archivo para el Chat
//Archivo chat.h


#include <iostream>		
#include <unistd.h>

using namespace std;



class chat
{
    private: 
        
        //Declaración de Atributos
        bool estado;
        int socket;
        bool esCliente;
    
    public:

        //Declaración de un Constructor
        //Por Defecto
        chat();
        //Por Pase de Argumentos
        chat(int,bool);

        /*//Destructor
        ~chat();*/
        
        
        //Declaración de Métodos
        
        //Método de Lectura
        void _read(void);

        //Método de Envío
        void _send(char[]);

        //Método de Activación
        bool estaActivo(void);

        //Método de Inactivación
        void inactivar(void);


};