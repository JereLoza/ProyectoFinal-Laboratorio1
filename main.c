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

void menuPrincipal();
void menuClientes();
void textoMenuClientes();
void menuConsumos();
void textoMenuConsumos();
stCliente cargarUnCliente();
int ultimoID();
int validaDNI(int dni);
int validaEmail(char email[]);
int validaEmail2(char email[]);
int validaMovil(int movil);
void cargarCliente();
void guardaClienteArch(stCliente c);
void muestraUnCliente(stCliente c);
void muestraClientes();


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
                muestraClientes(); // ACA IRIA LA BAJA DEL CLIENTE
            break;
            case 'c':
                //cargaDeDatos(); // ACA IRIA LA MODIFICACION DEL CLIENTE
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

stCliente cargarUnCliente(){
    stCliente c;

    c.id = ultimoID();

    do{
        printf("Ingrese el numero de cliente: ");
        scanf("%d", &c.nroCliente);
        if(validaNroCliente(c.nroCliente)){
            printf("\nEl numero de cliente \"%d\" ya se ha registrado! Ingresa un numero de cliente valido.\n", c.nroCliente);
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
            printf("\nEl DNI \"%d\" ya se ha registrado! Ingresa un DNI valido.", c.dni);
        }
    }while(validaDNI(c.dni));

    do{
        printf("\nIngrese el email del cliente: ");
        fflush(stdin);
        gets(c.email);
        if(validaEmail(c.email) == 0 || validaEmail2(c.email) == 1){
            printf("\nEl email \"%s\", ya se ha registrado, o es incorrecto! Ingrese un email valido.", c.email);
        }
    }while(validaEmail(c.email) == 0 || validaEmail2(c.email) == 1);

    printf("\nIngrese el domicilio del cliente: ");
    fflush(stdin);
    gets(c.domicilio);

    do{
        printf("\nIngrese el numero de celular del cliente: ");
        scanf("%d", &c.movil);
        if(validaMovil(c.movil)){
            printf("\nEl numero \"%d\" ya se ha registrado! Ingresa un numero valido.", c.movil);
        }
    }while(validaMovil(c.movil));

    c.baja = 0;

    return c;
}

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

void guardaClienteArch(stCliente c){
    FILE *pArchClientes = fopen(ARCH_CLIENTES, "ab");

    if(pArchClientes){
        fwrite(&c, sizeof(stCliente), 1, pArchClientes);
        fclose(pArchClientes);
    }
}

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
/*
void bajaCliente(){
    int pos;

    do{
        system("cls");
        printf("Introduzca la ID del cliente a dar de baja: ");
        scanf("%d", &pos);

        if(pos > ultimoID()){
            printf("\nNo hay ningun cliente registrado con esa ID! Ingrese una valida");
        }else{
            buscaClienteID(ARCH_CLIENTES, pos);

        }

    }while(pos > ultimoID());

}

void buscaClienteID(char archivo[], int pos){
    stCliente c;
    int flag = 0;

    FILE *pArchClientes = fopen(archivo, "rb");

    if(pArchClientes){
        while(flag == 0 && fread(&c, sizeof(stCliente), 1, pArchClientes) > 0){
            if(pos == c.id){
                flag = 1;
            }
        }
        fclose(pArchClientes);
    }

    muestraUnCliente(c);
}

void confirmaBaja(){
    char opcion;

    printf("Esta seguro que desea dar de baja al cliente? s/n");
    opcion = getch();

    if(opcion == 's'){

    }
}
*/
