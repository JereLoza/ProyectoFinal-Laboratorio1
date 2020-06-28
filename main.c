#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct {
     int id;
     int nroCliente;
     char nombre[30];
     char apellido[30];
     int dni;
     char email[30];
     char domicilio[45];
     int movil;
     int baja;
} stCliente;

typedef struct {
    int id;
    int idCliente;
    int anio;
    int mes;
    int dia;
    int datosConsumidos;
    int baja;
} stConsumos;

#define ESC 27

#define ARCH_CLIENTES "archClientes.dat"
#define ARCH_CLIENTESALTA "archClientesAlta.dat"
#define ARCH_CLIENTESBAJA "archClientesBaja.dat"

//MENUS
void menuPrincipal();
void menuClientes();
void textoMenuClientes();
void menuConsumos();
void textoMenuConsumos();

//CARGA DE CLIENTES + VALIDACIONES
stCliente cargarUnCliente();
int ultimoID();
int validaDNI(int dni);
int validaEmail(char email[]);
int validaEmail2(char email[]);
int validaMovil(int movil);
void cargarCliente();
void guardaClienteArch(stCliente c);

//MUESTRA DE CLIENTES
void muestraUnCliente(stCliente c);
void muestraClientes();

//BAJA DE CLIENTES
void bajaCliente();
stCliente buscaClienteDNI(char archivo[], int dni);
int buscaPosicion(int id);
void modifRegistroBaja(stCliente c);


//COLORES
void rojo(char texto[]);
void verde(char texto[]);


int main()
{
    char opcion;

    do{
        system("cls");
        menuPrincipal();
        opcion = getch();
        system("cls");

        switch(opcion){
            case 'a':
                menuClientes();
            break;
            case 'b':
                menuConsumos();
            break;
        }

    }while(opcion!=ESC);

    system("cls");

    return 0;
}

void menuPrincipal(){
    printf("\tMenu principal");
    printf("\n\n");
    printf("a) Clientes.\n");
    printf("b) Consumos.\n");
    printf("\n\n");
    printf("Presiona ESC para salir...");
}

void menuClientes(){
    char opcion;

    do{
        system("cls");
        textoMenuClientes();
        opcion = getch();
        system("cls");

        switch(opcion){
            case 'a':
                cargarCliente(); // ACA IRIA EL ALTA DEL CLIENTE
            break;
            case 'b':
                bajaCliente(); // ACA IRIA LA BAJA DEL CLIENTE
            break;
            case 'c':
                muestraClientes(); // ACA IRIA LA MODIFICACION DEL CLIENTE
            break;
            case 'd':
                //cargaDeDatos(); // ACA SE MOSTRARIAN SOLO LOS CLIENTES ACTIVOS
            break;
            case 'e':
                //cargaDeDatos(); // ACA SE MOSTRARIAN SOLO LOS CLIENTES INACTIVOS
            break;
        }

        system("pause");
    }while(opcion!=ESC);

    system("cls");
}

void textoMenuClientes(){
    printf("\tClientes");
    printf("\n\n");
    printf("a) Cargar nuevo cliente.\n");
    printf("b) Dar de baja a un cliente.\n");
    printf("c) Modificar un cliente.\n");
    printf("d) Listar clientes (activos).\n");
    printf("e) Listar clientes (inactivos).\n");
    printf("\n\n");
    printf("Presiona ESC para salir...");
}

void menuConsumos(){
    char opcion;

    do{
        system("cls");
        textoMenuConsumos();
        opcion = getch();
        system("cls");

        switch(opcion){
            case 'a':
                //cargaDeDatos(); // ACA EL ALTA DEL CONSUMO
            break;
            case 'b':
                //cargaDeDatos(); // ACA IRIA LA BAJA DEL CONSUMO
            break;
            case 'c':
                //cargaDeDatos(); // ACA IRIA LA MODIFICACION DEL CONSUMO
            break;
            case 'd':
                //cargaDeDatos(); // ACA SE MOSTRARIAN EL LISTADO DE CONSUMOS
            break;
        }

        system("pause");
    }while(opcion!=ESC);

    system("cls");
}

void textoMenuConsumos(){
    printf("\tConsumos");
    printf("\n\n");
    printf("a) Alta de consumo.\n");
    printf("b) Baja de consumo.\n");
    printf("c) Modificacion de consumo.\n");
    printf("d) Listado de consumos.\n");
    printf("\n\n");
    printf("Presiona ESC para salir...");
}


/*********************************************************//**
*
* \brief Funcion de carga de un Cliente
* \return stCliente
*
*************************************************************/
stCliente cargarUnCliente(){
    stCliente c;

    c.id = ultimoID();

    do{
        printf("Ingrese el numero de cliente: ");
        scanf("%d", &c.nroCliente);
        if(validaNroCliente(c.nroCliente)){
            printf("\033[1;31m");
            printf("\nEl numero de cliente \"%d\" ya se ha registrado! Ingresa un numero de cliente valido.\n", c.nroCliente);
            printf("\033[0m");
        }
    }while((c.nroCliente < 0 || c.nroCliente > 9999999) || (validaNroCliente(c.nroCliente) == 1));

    printf("\nIngrese el nombre del cliente: ");
    fflush(stdin);
    gets(c.nombre);

    printf("\nIngrese el apellido del cliente: ");
    fflush(stdin);
    gets(c.apellido);

    do{
        printf("\nIngrese el DNI del cliente: ");
        scanf("%d", &c.dni);
        if(validaDNI(c.dni)){
            printf("\033[1;31m");
            printf("\nEl DNI \"%d\" ya se ha registrado! Ingresa un DNI valido.", c.dni);
            printf("\033[0m");
        }
    }while(validaDNI(c.dni));

    do{
        printf("\nIngrese el email del cliente: ");
        fflush(stdin);
        gets(c.email);
        if(validaEmail(c.email) == 0 || validaEmail2(c.email) == 1){
            printf("\033[1;31m");
            printf("\nEl email \"%s\", ya se ha registrado, o es incorrecto! Ingrese un email valido.", c.email);
            printf("\033[0m");
        }
    }while(validaEmail(c.email) == 0 || validaEmail2(c.email) == 1);

    printf("\nIngrese el domicilio del cliente: ");
    fflush(stdin);
    gets(c.domicilio);

    do{
        printf("\nIngrese el numero de celular del cliente: ");
        scanf("%d", &c.movil);
        if(validaMovil(c.movil)){
            printf("\033[1;31m");
            printf("\nEl numero \"%d\" ya se ha registrado! Ingresa un numero valido.", c.movil);
            printf("\033[0m");
        }
    }while(validaMovil(c.movil));

    c.baja = 0;

    return c;
}

/*********************************************************************//**
*
* \brief Obtiene el id siguiente al ultimo
* \return el proximo id libre
*
**************************************************************************/
int ultimoID(){
    stCliente c;
    int id = -1;

    FILE *pArchClientes = fopen(ARCH_CLIENTES, "rb");

    if(pArchClientes){
        fseek(pArchClientes, sizeof(stCliente) * (-1), SEEK_END);
        if(fread(&c, sizeof(stCliente), 1, pArchClientes) > 0){
            id = c.id;
        }

        fclose(pArchClientes);
    }

    id++;
    return id;
}


/*********************************************************************//**
*
* \brief Valida si hay algun cliente con el mismo numero de cliente
* \param int nroCliente
* \return int 0 si no existe - 1 si existe
*
**************************************************************************/
int validaNroCliente(int nroCliente){
    stCliente c;
    int flag = 0;

    FILE *pArchClientes = fopen(ARCH_CLIENTES, "rb");

    if(pArchClientes){
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArchClientes) > 0){
            if(c.nroCliente == nroCliente){
                flag = 1;
            }
        }
        fclose(pArchClientes);
    }

    return flag;
}


/*********************************************************************//**
*
* \brief Valida si hay algun cliente con el mismo dni
* \param int dni
* \return int 0 si no existe - 1 si existe
*
**************************************************************************/
int validaDNI(int dni){
    stCliente c;
    int flag = 0;

    FILE *pArchClientes = fopen(ARCH_CLIENTES, "rb");

    if(pArchClientes){
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArchClientes) > 0){
            if(c.dni == dni){
                flag = 1;
            }
        }
        fclose(pArchClientes);
    }

    return flag;
}

/*********************************************************************//**
*
* \brief Valida si existe una @ en un string
* \param char email[]
* \return int 0 si no existe - 1 si existe
*
**************************************************************************/
int validaEmail(char email[]){
    int v = strlen(email);
    int i = 0;
    int flag = 0;

    while(i < v && flag == 0){
        if(email[i] == 64){ // 64 = @
            flag = 1;
        }

        i++;
    }

    return flag;
}

/*********************************************************************//**
*
* \brief Valida si hay algun cliente con el mismo email
* \param char email[]
* \return int 0 si no existe - 1 si existe
*
**************************************************************************/
int validaEmail2(char email[]){
    stCliente c;
    int flag = 0;

    FILE *pArchClientes = fopen(ARCH_CLIENTES, "rb");

    if(pArchClientes){
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArchClientes) > 0){
            if(strcmpi(c.email, email) == 0){
                flag = 1;
            }
        }
        fclose(pArchClientes);
    }

    return flag;
}

/*********************************************************************//**
*
* \brief Valida si hay algun cliente con el mismo movil
* \param int movil
* \return int 0 si no existe - 1 si existe
*
**************************************************************************/
int validaMovil(int movil){
    stCliente c;
    int flag = 0;

    FILE *pArchClientes = fopen(ARCH_CLIENTES, "rb");

    if(pArchClientes){
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArchClientes) > 0){
            if(c.movil == movil){
                flag = 1;
            }
        }
        fclose(pArchClientes);
    }

    return flag;
}

void cargarCliente(){
    char opcion = 's';

    while(opcion == 's'){
        system("cls");
        printf("\tCarga nuevo cliente\n\n");

        guardaClienteArch(cargarUnCliente());

        printf("\nDesea continuar? s/n\n");
        fflush(stdin);
        opcion = getch();
    }
}

/*********************************************************************//**
*
* \brief Guarda un dato de tipo stCliente en un archivo
* \param stCliente c
* \return void
*
**************************************************************************/
void guardaClienteArch(stCliente c){
    FILE *pArchClientes = fopen(ARCH_CLIENTES, "ab");

    if(pArchClientes){
        fwrite(&c, sizeof(stCliente), 1, pArchClientes);
        fclose(pArchClientes);
    }
}

/*********************************************************//**
*
* \brief Funcion que muestra un Cliente
* \param arreglo stCliente
* \return void
*
*************************************************************/
void muestraUnCliente(stCliente c){
    printf("\n -----------------------------------------------------");
    printf("\n  ID:                      %i", c.id);
    printf("\n  Numero de cliente:       %i", c.nroCliente);
    printf("\n  Nombre:                  %s", c.nombre);
    printf("\n  Apellido:                %s", c.apellido);
    printf("\n  DNI:                     %i", c.dni);
    printf("\n  Email:                   %s", c.email);
    printf("\n  Domicilio:               %s", c.domicilio);
    printf("\n  Movil:                   %i", c.movil);
    printf("\n  Baja:                    %i", c.baja);
    printf("\n -----------------------------------------------------\n");
}

void muestraClientes(){
    stCliente c;

    FILE *pArchClientes = fopen(ARCH_CLIENTES, "rb");

    if(pArchClientes){
        while(fread(&c, sizeof(stCliente), 1, pArchClientes) > 0){
            muestraUnCliente(c);
        }

        fclose(pArchClientes);
    }
}

void bajaCliente(){
    stCliente c;
    char opcion;
    int dni;

    do{
        printf("Introduzca el DNI del cliente a dar de baja: ");
        scanf("%d", &dni);

        if(!validaDNI(dni)){
            printf("\033[0;31m\nNo hay ningun cliente registrado con ese DNI! Ingrese uno valido\n\033[0m");
        }else{
            muestraUnCliente(buscaClienteDNI(ARCH_CLIENTES, dni));

            printf("Estas seguro que deseas dar de baja este cliente? s/n ");
            fflush(stdin);
            opcion = getch();

            if(opcion == 's'){
                modifRegistroBaja(buscaClienteDNI(ARCH_CLIENTES, dni));
                verde("\nHas dado de baja al cliente sastifactoriamente.\n");
            }else{
                rojo("\nNo se ha dado de baja el cliente!\n");
            }
        }

    }while(!validaDNI(dni));

}

/*********************************************************//**
*
* \brief Funcion que muestra un Cliente
* \param char archivo[]
* \param int dni
* \return stCliente
*
*************************************************************/
stCliente buscaClienteDNI(char archivo[], int dni){
    stCliente c;
    int flag = 0;

    FILE *pArchClientes = fopen(archivo, "rb");

    if(pArchClientes){
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArchClientes) > 0){
            if(c.dni == dni){
                flag = 1;
            }
        }
        fclose(pArchClientes);
    }

    return c;
}

/*********************************************************//**
*
* \brief Busca la posicion de la id introducida
* \param int id
* \return la posicion de la id pasada por parametro
*
*************************************************************/
int buscaPosicion(int id){
    stCliente c;
    int pos = -1;

    FILE *pArchClientes = fopen(ARCH_CLIENTES,"rb");

    if(pArchClientes){
        while(pos == -1 && fread(&c, sizeof(stCliente), 1, pArchClientes) > 0){
            if(c.id == id){
                pos = ftell(pArchClientes)/sizeof(stCliente)-1;
            }
        }
        fclose(pArchClientes);
    }

    return pos;
}

/*********************************************************//**
*
* \brief Da de baja al cliente pasado por parametro
* \param stCliente c
* \return void
*
*************************************************************/
void modifRegistroBaja(stCliente c){
    int pos = buscaPosicion(c.id);

    FILE *pArchClientes = fopen(ARCH_CLIENTES, "r+b");

    if(pArchClientes){
        fseek(pArchClientes, sizeof(stCliente)*pos, SEEK_SET);
        c.baja = 1;
        fwrite(&c, sizeof(stCliente), 1, pArchClientes);

        fclose(pArchClientes);
    }
}




/*********************************************************//**
*
* \brief Transforma el texto en rojo
* \param char texto[]
* \return void
*
*************************************************************/
void rojo(char texto[]){
    printf("\033[0;31m%s\033[0m", texto);
}

/*********************************************************//**
*
* \brief Transforma el texto en verde
* \param char texto[]
* \return void
*
*************************************************************/
void verde(char texto[]){
    printf("\033[0;32m%s\033[0m", texto);
}
