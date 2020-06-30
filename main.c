#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

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
#define MAX_CLIENTES 9999
#define MAX_CONSUMOS 9999
#define LETRA_ENIE 164

#define ARCH_CLIENTES "archClientes.dat"
#define ARCH_CLIENTESALTA "archClientesAlta.dat"
#define ARCH_CLIENTESBAJA "archClientesBaja.dat"
#define ARCH_CONSUMOS "archConsumos.dat"

//MENUS
void menuPrincipal();
void menuClientes();
void textoMenuClientes();
void menuConsumos();
void textoMenuConsumos();

//CARGA DE CLIENTES + VALIDACIONES
stCliente cargarUnCliente();
int ultimoID();
int validaDNI(char archivo[], int dni);
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
int buscarClienteDNI(char archivo[]);
stCliente buscaClienteDNI(char archivo[], int dni);
int buscaPosicion(int id);

//MODIFICAR CLIENTES
void menuModifCliente(int dni);
void textoMenuModifClientes();
void modifRegistro(stCliente c);
void cambiarNombre(stCliente c);
void cambiarApellido(stCliente c);
void cambiarEmail(stCliente c);
void cambiarDomicilio(stCliente c);
void cambiarMovil(stCliente c);
void modifCliente();

//ORDENAR CLIENTES ALTA
void clientesBajaAlta();
int pasarArchivoArreglo(char archivo[], stCliente array[], int dim);
void menuMostrarCliAct();
void textoMenuMostrarCliAct();
void mostrarClientes(stCliente array[], int v);
void intercambiaClientes(stCliente *a, stCliente *b);
void ordenarCliDNI(stCliente array[], int v);
void ordenarCliApellido(stCliente array[], int v);

//ORDENAR CLIENTES BAJA
void mostrarCliBajaEmail();
void ordenarCliBajaEmail(stCliente array[], int v);

//ALTA DE CONSUMO
int ultimoIDCons();
void muestraUnConsumo(stConsumos cons);
stConsumos cargaUnConsumo();
int validaIDCliente(char archivo[], int id);
void cargarConsumo();
void guardaConsumoArch(stConsumos cons);
void muestraConsumos();

//BAJA CONSUMO
void buscarConsumos();
int buscaPosicionCons(int id);
void modifRegistroCons(stConsumos cons);
int buscaIDCons();
int consumoEncontrado(int anio, int mes, int dia);
stConsumos buscaConsumoID(int id);

//MODIFICACION DE CONSUMO
void modifConsumo();
void cambiarConsumo(stConsumos cons);

//ORDENA UN CONSUMO POR ID
int pasarArchivoArregloCons(stConsumos array[], int dim);
void ordenarCons();
void intercambiaConsumos(stConsumos *a, stConsumos *b);
void ordenarConsID(stConsumos array[], int v);
void mostrarArrayCons(stConsumos array[], int v);

//COLORES
void rojo(char texto[]);
void verde(char texto[]);
void amarillo(char texto[]);


int main(){
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
                modifCliente(); // ACA IRIA LA MODIFICACION DEL CLIENTE
            break;
            case 'd':
                menuMostrarCliAct(); // ACA SE MOSTRARIAN SOLO LOS CLIENTES ACTIVOS
            break;
            case 'e':
                mostrarCliBajaEmail(); // ACA SE MOSTRARIAN SOLO LOS CLIENTES INACTIVOS
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
    printf("d) Listar clientes activos.\n");
    printf("e) Listar clientes inactivos ordenados por email.\n");
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
                cargarConsumo(); // ACA EL ALTA DEL CONSUMO
            break;
            case 'b':
                buscarConsumos();   // ACA IRIA LA BAJA DEL CONSUMO
            break;
            case 'c':
                modifConsumo();    // ACA IRIA LA MODIFICACION DEL CONSUMO
            break;
            case 'd':
                ordenarCons(); // ACA SE MOSTRARIAN EL LISTADO DE CONSUMOS
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
        if(validaDNI(ARCH_CLIENTES, c.dni)){
            printf("\033[1;31m");
            printf("\nEl DNI \"%d\" ya se ha registrado! Ingresa un DNI valido.", c.dni);
            printf("\033[0m");
        }
    }while(validaDNI(ARCH_CLIENTES, c.dni));

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
int validaDNI(char archivo[], int dni){
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

void muestraClientes(char archivo[]){
    stCliente c;

    FILE *pArchClientes = fopen(archivo, "rb");

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
    int dni = buscarClienteDNI(ARCH_CLIENTES);

    printf("Estas seguro que deseas dar de baja este cliente? s/n ");
    fflush(stdin);
    opcion = getch();

    if(opcion == 's'){
        c = buscaClienteDNI(ARCH_CLIENTES, dni);
        c.baja = 1;
        modifRegistro(c);
        verde("\nHas dado de baja al cliente sastifactoriamente.\n");
        }else{
            rojo("\nNo se ha dado de baja el cliente!\n");
        }
}

/*********************************************************//**
*
* \brief Funcion que busca un cliente por DNI y lo muestra
* \param char archivo[]
* \return dni
*
*************************************************************/
int buscarClienteDNI(char archivo[]){
    int dni;

    do{
        printf("Introduzca el DNI del cliente: ");
        scanf("%d", &dni);

        if(!validaDNI(archivo, dni)){
            printf("\033[0;31m\nNo hay ningun cliente registrado con ese DNI! Ingrese uno valido\n\033[0m");
        }else{
            muestraUnCliente(buscaClienteDNI(archivo, dni));
        }
    }while(!validaDNI(archivo, dni));

    return dni;
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

void modifCliente(){
    char opcion;
    int dni = buscarClienteDNI(ARCH_CLIENTES);

    amarillo("Estas seguro que deseas modificar este cliente? s/n ");
    fflush(stdin);
    opcion = getch();

    if(opcion == 's'){
        printf("\t\n\nQue deseas editar del cliente?: ");

        menuModifCliente(dni);

        verde("\nHas modificado este cliente sastifactoriamente.\n");
        }else{
            rojo("\nNo se ha modificado el cliente!\n");
        }
}

/*********************************************************//**
*
* \brief Menu que modifica clientes
* \param stCliente c
* \return void
*
*************************************************************/
void menuModifCliente(int dni){
    char opcion;

    stCliente c = buscaClienteDNI(ARCH_CLIENTES, dni);

    do{
        system("cls");
        muestraUnCliente(c);
        textoMenuModifClientes();
        opcion = getch();

        switch(opcion){
            case 'a':
                cambiarNombre(c);
            break;
            case 'b':
                cambiarApellido(c);
            break;
            case 'c':
                cambiarEmail(c);
            break;
            case 'd':
                cambiarDomicilio(c);
            break;
            case 'e':
                cambiarMovil(c);
            break;
        }

        system("pause");
    }while(opcion != ESC);
}

void textoMenuModifClientes(){
    printf("\n\n");
    printf("a) Modificar nombre.\n");
    printf("b) Modificar apellido.\n");
    printf("c) Modificar email.\n");
    printf("d) Modificar domicilio.\n");
    printf("e) Modificar movil.\n");
    printf("\n\n");
    printf("Presiona ESC para salir...\n");
}

/*********************************************************//**
*
* \brief Cambia el nombre de un cliente
* \param stCliente c
* \return void
*
*************************************************************/
void cambiarNombre(stCliente c){
    char nombre[30];

    printf("\nIngrese su nuevo nombre: ");
    fflush(stdin);
    gets(nombre);

    strcpy(c.nombre, nombre);
    modifRegistro(c);
}

/*********************************************************//**
*
* \brief Cambia el apellido de un cliente
* \param stCliente c
* \return void
*
*************************************************************/
void cambiarApellido(stCliente c){
    char apellido[30];

    printf("\nIngrese su nuevo apellido: ");
    fflush(stdin);
    gets(apellido);

    strcpy(c.apellido, apellido);
    modifRegistro(c);
}

/*********************************************************//**
*
* \brief Cambia el email de un cliente
* \param stCliente c
* \return void
*
*************************************************************/
void cambiarEmail(stCliente c){
    char email[30];

    do{
        printf("\nIngrese su nuevo email: ");
        fflush(stdin);
        gets(email);

        if(validaEmail(email) == 0 || validaEmail2(email) == 1){
            printf("\033[1;31m");
            printf("\nEl email \"%s\", ya se ha registrado, o es incorrecto! Ingrese un email valido.", email);
            printf("\033[0m");
        }
    }while(validaEmail(email) == 0 || validaEmail2(email) == 1);

    strcpy(c.email, email);

    modifRegistro(c);
}

/*********************************************************//**
*
* \brief Cambia el domicilio de un cliente
* \param stCliente c
* \return void
*
*************************************************************/
void cambiarDomicilio(stCliente c){
    char domicilio[45];

    printf("\nIngrese el nuevo domicilio: ");
    fflush(stdin);
    gets(domicilio);

    strcpy(c.domicilio, domicilio);

    modifRegistro(c);
}

/*********************************************************//**
*
* \brief Cambia el movil de un cliente
* \param stCliente c
* \return void
*
*************************************************************/
void cambiarMovil(stCliente c){
    int movil;

    printf("\nIngrese el nuevo movil: ");
    scanf("%d", &movil);

    c.movil = movil;

    modifRegistro(c);
}

/*********************************************************//**
*
* \brief Modifica el cliente pasado por parametro
* \param stCliente c
* \return void
*
*************************************************************/
void modifRegistro(stCliente c){
    int pos = buscaPosicion(c.id);

    FILE *pArchClientes = fopen(ARCH_CLIENTES, "r+b");

    if(pArchClientes){
        fseek(pArchClientes, sizeof(stCliente)*pos, SEEK_SET);
        fwrite(&c, sizeof(stCliente), 1, pArchClientes);

        fclose(pArchClientes);
    }
}

void menuMostrarCliAct(){
    char opcion;
    stCliente clientes[MAX_CLIENTES];
    clientesBajaAlta();
    int vClientes = pasarArchivoArreglo(ARCH_CLIENTESALTA, clientes, MAX_CLIENTES);

    do{
        system("cls");
        textoMenuMostrarCliAct();
        opcion = getch();

        switch(opcion){
            case 'a':
                ordenarCliDNI(clientes, vClientes);
                mostrarClientes(clientes, vClientes);
            break;
            case 'b':
                ordenarCliApellido(clientes, vClientes);
                mostrarClientes(clientes, vClientes);
            break;
            case 'c':
                system("cls");
                buscarClienteDNI(ARCH_CLIENTESALTA);
            break;
        }

        system("pause");
    }while(opcion != ESC);
}

void textoMenuMostrarCliAct(){
    printf("\t Mostrar clientes");
    printf("\n\n");
    printf("a) Mostrar clientes activos ordenados por DNI.\n");
    printf("b) Mostrar clientes activos ordenados por Apellido.\n");
    printf("c) Buscar un cliente activo por DNI y mostrarlo.\n");
    printf("\n\n");
    printf("Presiona ESC para salir...\n");
}

void clientesBajaAlta(){
    stCliente c;

    FILE *pArchClientes = fopen(ARCH_CLIENTES, "rb");
    FILE *pArchClientesAlta = fopen(ARCH_CLIENTESALTA, "wb");
    FILE *pArchClientesBaja = fopen(ARCH_CLIENTESBAJA, "wb");

    if(pArchClientes && pArchClientesAlta && pArchClientesBaja){
        while(fread(&c, sizeof(stCliente), 1, pArchClientes) > 0){
            if(c.baja){
                fwrite(&c, sizeof(stCliente), 1, pArchClientesBaja);
            }
            else{
                fwrite(&c, sizeof(stCliente), 1, pArchClientesAlta);
            }
        }

        fclose(pArchClientes);
        fclose(pArchClientesAlta);
        fclose(pArchClientesBaja);
    }
}

/*********************************************************//**
*
* \brief Pasa un archivo a un arreglo
* \param char archivo[]
* \param stCliente array[]
* \param int dim
* \return Validos del arreglo
*
*************************************************************/
int pasarArchivoArreglo(char archivo[], stCliente array[], int dim){
    stCliente c;
    int i = 0;

    FILE *pArchCliente = fopen(archivo, "rb");

    if(pArchCliente){
        while(i < dim && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0){
            array[i] = c;
            i++;
        }

        fclose(pArchCliente);
    }

    return i;
}

/*********************************************************//**
*
* \brief Muestra clientes de un arreglo
* \param stCliente array[]
* \param int v
* \return void
*
*************************************************************/
void mostrarClientes(stCliente array[], int v){
    system("cls");
    printf("\t\tLista de Clientes:\n\n");

    for(int i=0;i<v;i++){
        muestraUnCliente(array[i]);
    }
}

/*********************************************************//**
*
* \brief Intercambia clientes de lugar
* \param stCliente *a
* \param stCliente *b
* \return void
*
*************************************************************/
void intercambiaClientes(stCliente *a, stCliente *b){
    stCliente aux;

    aux = *a;
    *a = *b;
    *b = aux;
}

/*********************************************************//**
*
* \brief Ordena los clientes activos por dni
* \param stCliente array[]
* \param int v
* \return void
*
*************************************************************/
void ordenarCliDNI(stCliente array[], int v){
     for(int i=0;i<v;i++){
        for(int j=i+1;j<v;j++){
            if(array[i].dni > array[j].dni){
                intercambiaClientes(&array[i], &array[j]);
            }
        }
    }
}

/*********************************************************//**
*
* \brief Ordena los clientes activos por apellido
* \param stCliente array[]
* \param int v
* \return void
*
*************************************************************/
void ordenarCliApellido(stCliente array[], int v){
     for(int i=0;i<v;i++){
        for(int j=i+1;j<v;j++){
            if(strcmpi(array[i].apellido, array[j].apellido) > 0){
                intercambiaClientes(&array[i], &array[j]);
            }
        }
    }
}

void mostrarCliBajaEmail(){
    stCliente clientesBaja[MAX_CLIENTES];
    clientesBajaAlta();
    int vClientesBaja = pasarArchivoArreglo(ARCH_CLIENTESBAJA, clientesBaja, MAX_CLIENTES);

    ordenarCliBajaEmail(clientesBaja, vClientesBaja);
    mostrarClientes(clientesBaja, vClientesBaja);

}

/*********************************************************//**
*
* \brief Ordena los clientes dados de baja por email
* \param stCliente array[]
* \param int v
* \return void
*
*************************************************************/
void ordenarCliBajaEmail(stCliente array[], int v){
    for(int i=0;i<v;i++){
        for(int j=i+1;j<v;j++){
            if(strcmpi(array[i].email, array[j].email) > 0){
                intercambiaClientes(&array[i], &array[j]);
            }
        }
    }
}

///*  ACA TERMINA LA SECCION DE CLIENTES  *///

/*********************************************************//**
*
* \brief Busca el ultimo id libre de un archivo
* \return id
*
*************************************************************/
int ultimoIDCons(){
    stConsumos cons;
    int id = -1;

    FILE *pArchConsumos = fopen(ARCH_CONSUMOS, "rb");

    if(pArchConsumos){
        fseek(pArchConsumos, sizeof(stConsumos) * (-1), SEEK_END);
        if(fread(&cons, sizeof(stConsumos), 1, pArchConsumos) > 0){
            id = cons.id;
        }

        fclose(pArchConsumos);
    }

    id++;
    return id;
}

/*********************************************************//**
*
* \brief Muestra un consumo
* \param stConsumos cons
* \return void
*
*************************************************************/
void muestraUnConsumo(stConsumos cons){
    printf("\n -----------------------------------------------------");
    printf("\n  ID del consumo:          %i", cons.id);
    printf("\n  ID de cliente:           %i", cons.idCliente);
    printf("\n  A%co:                     %d", LETRA_ENIE, cons.anio);
    printf("\n  Mes:                     %d", cons.mes);
    printf("\n  Dia:                     %d", cons.dia);
    printf("\n  Datos Consumidos:        %i", cons.datosConsumidos);
    printf("\n  Baja:                    %i", cons.baja);
    printf("\n -----------------------------------------------------\n");
}

/*********************************************************//**
*
* \brief Carga un consumo
* \return stConsumos
*
*************************************************************/
stConsumos cargaUnConsumo(){
    stConsumos cons;
    time_t sisTime;     //time_t es un typedef, asigno una varible de este tipo (sisTime);
    struct tm *tiempo;     //Creo un puntero a la estructura tm, (ya definida en time.h).

    time(&sisTime);     //time obtiene el tiempo del sistema y se lo pasa a la direccion de sisTime.
    tiempo=localtime(&sisTime);     //Convierte los valores de sisTime a compatibles con la estructura tm y luego asigno ese valor a tiempo.

    int anio = (tiempo->tm_year) + 1900;
    int mes = (tiempo->tm_mon) + 1;
    int dia = tiempo->tm_mday;

    cons.id = ultimoIDCons();

    do{
        printf("Ingrese la ID del cliente a cargar el consumo: ");
        scanf("%d", &cons.idCliente);
        if((cons.idCliente < 0) || (cons.idCliente >= ultimoID()) || (validaIDCliente(ARCH_CLIENTESALTA, cons.idCliente) == 0)){
            printf("\033[1;31m");
            printf("\nLa ID \"%d\" no existe o esta ingresando un cliente dado de baja! Ingresa una ID valida.\n", cons.idCliente);
            printf("\033[0m");
        }
    }while(cons.idCliente < 0 || cons.idCliente >= ultimoID() || (validaIDCliente(ARCH_CLIENTESALTA, cons.idCliente) == 0));

    cons.anio = anio;
    cons.mes = mes;
    cons.dia = dia;

    printf("\nIngrese los datos consumidos por el usuario (mb): ");
    scanf("%d", &cons.datosConsumidos);

    cons.baja = 0;

    return cons;
}

/*********************************************************************//**
*
* \brief Valida si hay algun cliente con el mismo ID
* \param int id
* \return int 0 si no existe - 1 si existe
*
**************************************************************************/
int validaIDCliente(char archivo[], int id){
    stCliente c;
    int flag = 0;

    FILE *pArchClientes = fopen(archivo, "rb");

    if(pArchClientes){
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArchClientes) > 0){
            if(c.id == id){
                flag = 1;
            }
        }
        fclose(pArchClientes);
    }

    return flag;
}

void cargarConsumo(){
    char opcion = 's';

    while(opcion == 's'){
        system("cls");
        printf("\tCarga nuevo consumo\n\n");

        guardaConsumoArch(cargaUnConsumo());

        printf("\nDesea continuar? s/n\n");
        fflush(stdin);
        opcion = getch();
    }
}

/*********************************************************************//**
*
* \brief Guarda un dato de tipo stConsumo en un archivo
* \param stConsumo cons
* \return void
*
**************************************************************************/
void guardaConsumoArch(stConsumos cons){
    FILE *pArchConsumos = fopen(ARCH_CONSUMOS, "ab");

    if(pArchConsumos){
        fwrite(&cons, sizeof(stConsumos), 1, pArchConsumos);
        fclose(pArchConsumos);
    }
}

void muestraConsumos(){
    stConsumos cons;

    FILE *pArchConsumos = fopen(ARCH_CONSUMOS, "rb");

    if(pArchConsumos){
        while(fread(&cons, sizeof(stConsumos), 1, pArchConsumos) > 0){
            muestraUnConsumo(cons);
        }

        fclose(pArchConsumos);
    }
}

void buscarConsumos(){
    char opcion;
    int anio, mes, dia, id;
    stConsumos cons;

    printf("Ingresar a%co del consumo: ", LETRA_ENIE);
    scanf("%d", &anio);

    do{
        printf("\nIngresar mes del consumo: ");
        scanf("%d", &mes);

        if(mes < 1 || mes > 12){
            rojo("Introduzca un mes valido!");
        }
    }while(mes < 1 || mes > 12);

    do{
        printf("\nIngresar dia del consumo: ");
        scanf("%d", &dia);

        if(dia < 1 || dia > 31){
            rojo("Introduzca un dia valido!");
        }
    }while(dia < 1 || dia > 31);

    if(consumoEncontrado(anio, mes, dia) != 0){
        id = buscaIDCons();
        cons = buscaConsumoID(id);

        system("cls");
        muestraUnConsumo(cons);
        amarillo("Estas seguro que deseas modificar este consumo? s/n ");
        fflush(stdin);
        opcion = getch();

        if(opcion == 's'){
            cons.baja = 1;
            modifRegistroCons(cons);

            verde("\nHas modificado este consumo sastifactoriamente.\n");
            }else{
                rojo("\nNo se ha modificado el consumo!\n");
            }

    }else{
        rojo("\nNo se han encontrado consumos para la fecha introducida\n");
    }
}

/*********************************************************//**
*
* \brief Pide que el usuario ingrese una ID
* \return id
*
*************************************************************/
int buscaIDCons(){
    int id;

    do{
        printf("Que consumo desea buscar? (Intruducir ID del consumo): ");
        scanf("%d", &id);

        if(id > ultimoIDCons()){
            rojo("Introduce una ID valida!");
        }
    }while(id > ultimoIDCons());

    return id;
}

/*********************************************************//**
*
* \brief Busca la posicion de la id introducida
* \param int id
* \return la posicion de la id pasada por parametro
*
*************************************************************/
int buscaPosicionCons(int id){
    stConsumos cons;
    int pos = -1;

    FILE *pArchConsumos = fopen(ARCH_CONSUMOS,"rb");

    if(pArchConsumos){
        while(pos == -1 && fread(&cons, sizeof(stConsumos), 1, pArchConsumos) > 0){
            if(cons.id == id){
                pos = ftell(pArchConsumos)/sizeof(stConsumos)-1;
            }
        }
        fclose(pArchConsumos);
    }

    return pos;
}

/*********************************************************//**
*
* \brief Modifica el cliente pasado por parametro
* \param stConsumos cons
* \return void
*
*************************************************************/
void modifRegistroCons(stConsumos cons){
    int pos = buscaPosicionCons(cons.id);

    FILE *pArchConsumos = fopen(ARCH_CONSUMOS, "r+b");

    if(pArchConsumos){
        fseek(pArchConsumos, sizeof(stConsumos)*pos, SEEK_SET);
        fwrite(&cons, sizeof(stConsumos), 1, pArchConsumos);

        fclose(pArchConsumos);
    }
}

/*********************************************************//**
*
* \brief Busca un consumo por su fecha
* \param int anio
* \param int mes
* \param int dia
* \return flag
*
*************************************************************/
int consumoEncontrado(int anio, int mes, int dia){
    stConsumos cons;
    int flag = 0;

    FILE *pArchConsumos = fopen(ARCH_CONSUMOS, "rb");

    if(pArchConsumos){
        while(fread(&cons, sizeof(stConsumos), 1, pArchConsumos) > 0){
            if(cons.anio == anio && cons.mes == mes && cons.dia == dia){
                muestraUnConsumo(cons);
                flag++;
            }
        }
    }

    return flag;
}

/*********************************************************//**
*
* \brief Busca un consumo por su id
* \param int id
* \return stConsumos
*
*************************************************************/
stConsumos buscaConsumoID(int id){
    stConsumos cons;
    int flag = 0;

    FILE *pArchConsumos = fopen(ARCH_CONSUMOS, "rb");

    if(pArchConsumos){
        while(flag == 0 && fread(&cons, sizeof(stConsumos), 1, pArchConsumos) > 0){
            if(cons.id == id){
                flag = 1;
            }
        }
        fclose(pArchConsumos);
    }

    return cons;
}

void modifConsumo(){
    char opcion;
    int id = buscaIDCons();
    muestraUnConsumo(buscaConsumoID(id));

    amarillo("Estas seguro que deseas modificar este consumo? s/n ");
    fflush(stdin);
    opcion = getch();

    if(opcion == 's'){
        cambiarConsumo(buscaConsumoID(id));

        verde("\nHas modificado este consumo sastifactoriamente.\n");
        }else{
            rojo("\nNo se ha modificado el consumo!\n");
        }
}

/*********************************************************//**
*
* \brief Cambia los datos consumidos de un cliente
* \param stConsumos cons
* \return void
*
*************************************************************/
void cambiarConsumo(stConsumos cons){
    int consumo;

    printf("\nIngrese el nuevo consumo: ");
    scanf("%d", &consumo);

    cons.datosConsumidos = consumo;

    modifRegistroCons(cons);
}

/*********************************************************//**
*
* \brief Pasa un archivo a un arreglo de tipo stConsumos
* \param char archivo[]
* \param stConsumos array[]
* \param int dim
* \return Validos del arreglo
*
*************************************************************/
int pasarArchivoArregloCons(stConsumos array[], int dim){
    stConsumos cons;
    int i = 0;

    FILE *pArchConsumos = fopen(ARCH_CONSUMOS, "rb");

    if(pArchConsumos){
        while(i < dim && fread(&cons, sizeof(stConsumos), 1, pArchConsumos) > 0){
            array[i] = cons;
            i++;
        }

        fclose(pArchConsumos);
    }

    return i;
}

void ordenarCons(){
    stConsumos array[MAX_CONSUMOS];
    int vConsumos = pasarArchivoArregloCons(array, MAX_CONSUMOS);

    ordenarConsID(array, vConsumos);
    mostrarArrayCons(array, vConsumos);
}

/*********************************************************//**
*
* \brief Intercambia los consumos de lugar
* \param *stConsumos *a
* \param *stConsumos *b
* \return void
*
*************************************************************/
void intercambiaConsumos(stConsumos *a, stConsumos *b){
    stConsumos aux;

    aux = *a;
    *a = *b;
    *b = aux;
}

/*********************************************************//**
*
* \brief Ordena un arreglo de consumos por ID
* \param stConsumos array[]
* \param int v
* \return void
*
*************************************************************/
void ordenarConsID(stConsumos array[], int v){
     for(int i=0;i<v;i++){
        for(int j=i+1;j<v;j++){
            if(array[i].idCliente > array[j].idCliente){
                intercambiaConsumos(&array[i], &array[j]);
            }
        }
    }
}

/*********************************************************//**
*
* \brief Muestra consumos de un arreglo
* \param stConsumos array[]
* \param int v
* \return void
*
*************************************************************/
void mostrarArrayCons(stConsumos array[], int v){
    printf("\t\tLista de Consumos:\n\n");

    for(int i=0;i<v;i++){
        muestraUnConsumo(array[i]);
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
    printf("\033[1;31m%s\033[0m", texto);
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

/*********************************************************//**
*
* \brief Transforma el texto en amarillo
* \param char texto[]
* \return void
*
*************************************************************/
void amarillo(char texto[]){
    printf("\033[0;33m%s\033[0m", texto);
}
