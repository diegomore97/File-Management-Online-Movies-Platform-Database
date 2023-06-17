//Numero confidencial del gerente: 12345
//Contraseña del Gerente: 12345
//Modificar numero y clave en la linea 1911

#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix)||defined(__unix__)||defined(__unix)||defined(__APPLE__)||defined(__MACH__)
#define CLEAR "clear"
#else
#error "SO no soportado para limpiar pantalla"
#endif

#define TAMANO_CADENA 30
#define TECLA_RETROCESO 8
#define PRIMER_CARACTER_ASCII 32
#define TOTAL_ADMINISTRADORES 100
#define TOTAL_CLIENTES 100
#define TOTAL_PELICULAS 100
#define TAMANO_SINOPSIS 100
#define TOTAL_ATRIBUTOS_ADMINISTRADORES 6
#define TOTAL_ATRIBUTOS_CLIENTES 5
#define ENTER 13
#define NOMBRE_LEIDO 1
#define CORREO_LEIDO 2
#define CLAVE_LEIDA 3
#define NUM_TARJETA_LEIDA 4
#define SUSCRIBCION_LEIDA 5
#define NUM_TRABAJADOR_LEIDO 2
#define DOMICILIO_LEIDO 4
#define TELEFONO_LEIDO 5
#define SUELDO_LEIDO 6
#define PUESTO_LEIDO 7
#define ACTORES_LEIDOS 2
#define GENERO_LEIDO 3
#define SINOPSIS_LEIDA 4
#define DURACION_LEIDA 5
#define TOTAL_PELICULAS_PARA_DESCARGAR 100
#define TIPO_PELI_LEIDO 6
#define TOTAL_ATRIBUTOS_PELICULAS 6

typedef enum {basico,premium} tipoMembresia;
typedef enum {falso,verdadero} booleano;
typedef enum {normal,estreno} tipoPelicula;

typedef struct
{
    char numTrabajador[TAMANO_CADENA+1];
    char clave [TAMANO_CADENA+1];
    char nombre[TAMANO_CADENA+1];
    char domicilio[TAMANO_CADENA+1];
    char telefono[TAMANO_CADENA+1];
    long int sueldo;
} admin;

typedef struct
{
    char nombre[TAMANO_CADENA+1];
    char clave [TAMANO_CADENA+1];
    char correo[TAMANO_CADENA+1];
    char numTarjetaCredito[TAMANO_CADENA+1];
    tipoMembresia membresia;
} cliente;

typedef struct
{
    char nombre[TAMANO_CADENA+1];
    char actores [TAMANO_CADENA+1];
    char genero [TAMANO_CADENA+1];
    char sinopsis [TAMANO_SINOPSIS+1];
    float duracion;
    tipoPelicula tipo;
} registro;

//Variables para la manipulacion de registros
admin administradores[TOTAL_ADMINISTRADORES];
cliente clientes[TOTAL_CLIENTES];
registro peliculas[TOTAL_PELICULAS];
int cuentaClientes;
int cuentaAdministradores;
int cuentaPeliculas;
//Funciones generales del programa
int opcionesMenuPrincipal();
void imprimirError();
void imprimirTitulo();
int opcionesMenuSesion();
void ocultarClave(char *clave);
void pausa();
void inicializarRegistros();
void bienvenida();

//Funciones para la manipulacion de registros de peliculas
void menuPelicula();
void pedirDatosPelicula(int i);
void altaPelicula();
void cargarDatosPeliculas();
void reproducirPelicula(int numPelicula);
void modificarPelicula();
void bajaPelicula();
void listarPeliculas();
void buscarPelicula();
booleano coincideNombrePelicula(char *nombrePelicula);
int damePosicionPelicula(char* nombrePelicula);
void guardarArchivoPelicula();
int opcionesMenuPelicula();
void mostrarDatosPelicula(int i);

//Funciones para la manipulacion de registros de clientes
void pedirDatosCliente(int i);
booleano datosCorrectosClientes(char *correo, char *clave);
void altaCliente();
void modificarCliente();
void bajaCliente();
void inicioSesionCliente();
void cargarDatosClientes();
void menuCliente(char* correo);
int queClienteIngreso(char *correoIniciado);
void mostrarDatosCliente(int i);
void listarClientes();
void buscarCliente();
booleano coincideCorreoCliente(char *correoCliente);
int damePosicionCliente(char* correoCliente);
int opcionesMenuCliente();
void menuAdminClientes();
void menuClientePremium();
void menuClienteBasico();
void guardarArchivoCliente();

//Funciones para la manipulacion de registros de trabajadores
void pedirDatosEmpleado(int i);
void menuAdministrador();
void inicioSesionEmpleado();
void menuGerente();
void menuTrabajador();
void cargarDatosadministradores();
void altaTrabajador();
int queTrabajadorIngreso(char *numTrabajador);
void modificarTrabajador();
void bajaTrabajador();
void listarTrabajadores();
void buscarTrabajador();
void mostrarDatosTrabajador(int i);
booleano coincideNumeroTrabajador(char *numTrabajador);
int damePosicionTrabajador(char* numTrabajador);
int opcionesMenuGerente();
booleano datosCorrectosGerente(char *num, char *clave);
void guardarArchivoTrabajador();
void inicioSesionGerente();
booleano datosCorrectosadministradores(char *numTrabajador, char *clave);
int opcionesMenuTrabajador();

void imprimirError()
{
    printf("\n\nHas ingresado una opcion no valida!\n\n");
}

int opcionesMenuPrincipal()
{
    int opcion;
    fflush(stdin);
    printf("1. Registrarse\n\n");
    printf("2. Iniciar Sesion\n\n");
    printf("3. Salir\n\n");
    printf("Opcion: ");
    scanf("%d",&opcion);
    while(opcion<0&&opcion>3)
    {
        printf("\n\nHas ingresado una opcion no valida!\n\n");
        printf("1. Registrarse\n\n");
        printf("2. Iniciar Sesion\n\n");
        printf("Opcion (1 / 2): ");
        scanf("%d",&opcion);
    }

    return opcion;
}

void imprimirTitulo()
{
    printf("\t\t\t***i-PELIs***\n\n");
}

int opcionesMenuSesion()
{
    int opcion;
    fflush(stdin);
    system(CLEAR);
    printf("\t\t\t***Iniciar Sesion***\n\n");
    printf("1. Iniciar sesion como Gerente\n");
    printf("2. Iniciar Sesion como Empleado\n");
    printf("3. Iniciar sesion como Cliente\n\n");
    printf("Opcion: ");
    scanf("%d",&opcion);
    while(opcion<0&&opcion>3)
    {
        printf("\n\nHas ingresado una opcion no valida!\n\n");
        printf("1. Iniciar sesion como Gerente\n");
        printf("2. Iniciar Sesion como Empleado\n");
        printf("3. Iniciar sesion como Cliente\n\n");
        printf("Opcion: ");
        scanf("%d",&opcion);
    }
    return opcion;
}

int main()
{
    bienvenida();
    inicializarRegistros();
    cargarDatosClientes();
    cargarDatosadministradores();
    cargarDatosPeliculas();
    fflush(stdin);
    int opcion;
    do
    {
        imprimirTitulo();
        opcion=opcionesMenuPrincipal();

        switch(opcion)
        {
        case 1:
            system(CLEAR);
            altaCliente();
            break;

        case 2:
            switch(opcionesMenuSesion())
            {
            case 1:
                inicioSesionGerente();
                break;

            case 2:
                inicioSesionEmpleado();
                break;

            case 3:
                inicioSesionCliente();

            default:
                imprimirError();
                break;
            }

            break;
        default:
            imprimirError();
            break;
        }
        system(CLEAR);
    }
    while(opcion!=3);
    return 0;
}
void pausa()
{
    printf("\n\nPresiona Enter para continuar...");
    getch();
}
void ocultarClave(char *clave)
{
    fflush(stdin);
    int i=0;
    printf("Ingresa tu clave: ");
    while(clave[i]!=ENTER)
    {
        clave[i]=getch();
        if(clave[i]>PRIMER_CARACTER_ASCII && i<TAMANO_CADENA)
        {
            putchar('*');
            i++;
        }
        else if(clave[i]==TECLA_RETROCESO && i>0)
        {
            putchar(TECLA_RETROCESO);
            putchar(' ');
            putchar(TECLA_RETROCESO);
            i--;
        }
    }
    clave[i]='\0';
    printf("\n");
}
void inicioSesionCliente()
{
    system(CLEAR);
    char correoIniciado[TAMANO_CADENA];
    char clave [TAMANO_CADENA+1];
    fflush(stdin);
    printf("Ingresa tu correo: ");
    gets(correoIniciado);
    fflush(stdin);
    ocultarClave(clave);
    while(strcmp(correoIniciado,"\0")==0)
    {
        printf("\n\nOpcion no valida!\n\n");
        fflush(stdin);
        printf("Ingresa tu correo: ");
        gets(correoIniciado);
        fflush(stdin);
        ocultarClave(clave);

    }
    while(!datosCorrectosClientes(correoIniciado,clave))
    {
        printf("\n\nLos datos ingresados no fueron correctos intentalo nuevamente\n\n");
        fflush(stdin);
        printf("Ingresa tu correo: ");
        gets(correoIniciado);
        fflush(stdin);
        ocultarClave(clave);
        while(strcmp(correoIniciado,"\0")==0)
        {
            printf("\n\nOpcion no valida!\n\n");
            fflush(stdin);
            printf("Ingresa tu correo: ");
            gets(correoIniciado);
            fflush(stdin);
            ocultarClave(clave);
        }
    }
    pausa();
    menuCliente(correoIniciado);
    pausa();
}

booleano datosCorrectosClientes(char *correo, char *clave)
{
    booleano datosEncontrados;
    int i;
    for(i=0; i<TOTAL_CLIENTES; i++)
    {

        if(strcmp(correo,clientes[i].correo)==0&&strcmp(clave,clientes[i].clave)==0)
        {
            datosEncontrados=verdadero;
            break;
        }
        else
        {
            datosEncontrados=falso;
        }
    }
    if(datosEncontrados)
    {
        return verdadero;

    }
    else
    {
        return falso;
    }
}

booleano datosCorrectosadministradores(char *numTrabajador, char *clave)
{
    int i;

    booleano datosEncontrados;
    for(i=0; i<TOTAL_ADMINISTRADORES; i++)
    {

        if(strcmp(numTrabajador,administradores[i].numTrabajador)==0&&
                strcmp(clave,administradores[i].clave)==0)
        {
            datosEncontrados=verdadero;
            break;
        }
        else
        {
            datosEncontrados=falso;
        }
    }
    if(datosEncontrados)
    {
        return verdadero;

    }
    else
    {
        return falso;
    }
}

void pedirDatosCliente(int i)
{
    int opcion;
    fflush(stdin);
    printf("***Ingresa los datos***\n\n");
    printf("Nombre: ");
    gets(clientes[i].nombre);
    fflush(stdin);
    printf("Correo: ");
    gets(clientes[i].correo);
    fflush(stdin);
    ocultarClave(clientes[i].clave);
    fflush(stdin);
    printf("Ingresa el numero de tarjeta de credito: ");
    gets(clientes[i].numTarjetaCredito);
    fflush(stdin);
    printf("\n\nQue tipo de membrecia desea adquirir: \n");
    printf("1. Basico\n");
    printf("2. Premium\n\n");
    printf("Opcion (1 / 2): ");
    scanf("%d",&opcion);
    while(opcion<0||opcion>2)
    {
        printf("\n\nHas ingresado una opcion no valida!\n\n");
        printf("\n\nQue tipo de membrecia desea adquirir: \n\n");
        printf("1. Basico\n\n");
        printf("2. Premium\n\n");
        printf("Opcion (1 / 2): ");
        scanf("%d",&opcion);
    }
    if(opcion==1)
    {
        clientes[i].membresia=basico;
    }

    else if(opcion==2)
    {
        clientes[i].membresia=premium;
    }
}

void pedirDatosEmpleado(int i)
{
    fflush(stdin);
    printf("***Ingresa los datos***\n\n");
    printf("Nombre: ");
    gets(administradores[i].nombre);
    fflush(stdin);
    printf("Ingresa el numero de trabajador: ");
    gets(administradores[i].numTrabajador);
    fflush(stdin);
    ocultarClave(administradores[i].clave);
    fflush(stdin);
    printf("Ingresa tu domicilio: ");
    gets(administradores[i].domicilio);
    fflush(stdin);
    printf("Ingresa tu telefono: ");
    gets(administradores[i].telefono);
    fflush(stdin);
    printf("Ingresa el sueldo: ");
    scanf("%ld",&administradores[i].sueldo);
}

void inicioSesionEmpleado()
{
    system(CLEAR);
    char clave [TAMANO_CADENA+1];
    char numTrabajadorIniciado[TAMANO_CADENA];
    fflush(stdin);
    printf("Ingresa tu Numero de empleado: ");
    gets(numTrabajadorIniciado);
    fflush(stdin);
    ocultarClave(clave);
    while(strcmp(numTrabajadorIniciado,"\0")==0)
    {
        printf("\n\nOpcion no valida!\n\n");
        fflush(stdin);
        printf("Ingresa tu Numero de empleado: ");
        gets(numTrabajadorIniciado);
        fflush(stdin);
        ocultarClave(clave);

    }
    while(!datosCorrectosadministradores(numTrabajadorIniciado,clave))
    {
        printf("\n\nLos datos ingresados no fueron correctos intentalo nuevamente\n\n");
        fflush(stdin);
        printf("Ingresa tu numero de empleado: ");
        gets(numTrabajadorIniciado);
        fflush(stdin);
        ocultarClave(clave);
        while(strcmp(numTrabajadorIniciado,"\0")==0)
        {
            printf("\n\nOpcion no valida!\n\n");
            fflush(stdin);
            printf("Ingresa tu Numero de empleado: ");
            gets(numTrabajadorIniciado);
            fflush(stdin);
            ocultarClave(clave);

        }
    }
    pausa();
    menuTrabajador();
}

void cargarDatosClientes()
{
    FILE *lecturaClientes;

    booleano sinRegistros=verdadero;
    lecturaClientes=fopen("clientes.txt","r");

    int i=0;
    int lineasLeidas=0;
    char comprobador[TAMANO_CADENA+1];

    if(lecturaClientes!=NULL)
    {

        while(fgets(comprobador,sizeof(comprobador),lecturaClientes)!=NULL)
        {

            strtok(comprobador,"\n");
            lineasLeidas++;

            if(lineasLeidas==NOMBRE_LEIDO)
            {
                strcpy(clientes[i].nombre,comprobador);
            }

            if(lineasLeidas==CLAVE_LEIDA)
            {
                strcpy(clientes[i].clave,comprobador);
            }

            if(lineasLeidas==CORREO_LEIDO)
            {
                strcpy(clientes[i].correo,comprobador);
            }

            if(lineasLeidas==NUM_TARJETA_LEIDA)
            {
                strcpy(clientes[i].numTarjetaCredito,comprobador);
            }
            if(lineasLeidas==SUSCRIBCION_LEIDA)
            {
                if(strcmp(comprobador,"basico")==0)
                {

                    clientes[i].membresia=basico;
                }

                else if(strcmp(comprobador,"premium")==0)
                {
                    clientes[i].membresia=premium;
                }
            }
            if(lineasLeidas==TOTAL_ATRIBUTOS_CLIENTES)
            {
                i++;
                cuentaClientes++;
                sinRegistros=falso;
                lineasLeidas=0;
            }

        }

        if(!sinRegistros)
        {
            printf("Se han cargado %d registos de clientes!\n\n",cuentaClientes);
        }
    }

    else
    {
        printf("No se pudo leer el archivo o aun no se ha registrado a ningun cliente!\n\n");

    }
    fclose(lecturaClientes);
}

void cargarDatosPeliculas()
{
    FILE *lecturaPeliculas;

    booleano sinRegistros=verdadero;
    lecturaPeliculas=fopen("peliculas.txt","r");

    int i=0;
    int lineasLeidas=0;
    char comprobador[TAMANO_CADENA+1];

    if(lecturaPeliculas!=NULL)
    {

        while(fgets(comprobador,sizeof(comprobador),lecturaPeliculas)!=NULL)
        {

            strtok(comprobador,"\n");
            lineasLeidas++;

            if(lineasLeidas==NOMBRE_LEIDO)
            {
                strcpy(peliculas[i].nombre,comprobador);
            }

            if(lineasLeidas==ACTORES_LEIDOS)
            {
                strcpy(peliculas[i].actores,comprobador);
            }

            if(lineasLeidas==GENERO_LEIDO)
            {
                strcpy(peliculas[i].genero,comprobador);
            }

            if(lineasLeidas==SINOPSIS_LEIDA)
            {
                strcpy(peliculas[i].sinopsis,comprobador);
            }

            if(lineasLeidas==DURACION_LEIDA)
            {
                peliculas[i].duracion=atoi(comprobador);
            }

            if(lineasLeidas==TIPO_PELI_LEIDO)
            {
                if(strcmp(comprobador,"normal")==0)
                {

                    peliculas[i].tipo=normal;
                }

                else if(strcmp(comprobador,"estreno")==0)
                {
                    peliculas[i].tipo=estreno;
                }
            }
            if(lineasLeidas==TOTAL_ATRIBUTOS_PELICULAS)
            {
                i++;
                cuentaPeliculas++;
                sinRegistros=falso;
                lineasLeidas=0;
            }

        }

        if(!sinRegistros)
        {
            printf("Se han cargado %d registros de peliculas!\n\n",cuentaPeliculas);
            pausa();
        }
    }

    else
    {
        printf("No se pudo leer el archivo o aun no se ha registrado ninguna pelicula!\n\n");
        pausa();

    }
    fclose(lecturaPeliculas);
    system(CLEAR);
}


void cargarDatosadministradores()
{
    FILE *lecturaadministradores;

    booleano sinRegistros=verdadero;
    lecturaadministradores=fopen("trabajadores.txt","r");

    int i=0;
    int lineasLeidas=0;
    char comprobador[TAMANO_CADENA+1];

    if(lecturaadministradores!=NULL)
    {

        while(fgets(comprobador,sizeof(comprobador),lecturaadministradores)!=NULL)
        {

            strtok(comprobador,"\n");
            lineasLeidas++;

            if(lineasLeidas==NOMBRE_LEIDO)
            {
                strcpy(administradores[i].nombre,comprobador);
            }

            if(lineasLeidas==NUM_TRABAJADOR_LEIDO)
            {
                strcpy(administradores[i].numTrabajador,comprobador);
            }

            if(lineasLeidas==CLAVE_LEIDA)
            {
                strcpy(administradores[i].clave,comprobador);
            }

            if(lineasLeidas==DOMICILIO_LEIDO)
            {
                strcpy(administradores[i].domicilio,comprobador);
            }
            if(lineasLeidas==TELEFONO_LEIDO)
            {
                strcpy(administradores[i].telefono,comprobador);
            }
            if(lineasLeidas==SUELDO_LEIDO)
            {
                administradores[i].sueldo=atoi(comprobador);
            }

            if(lineasLeidas==TOTAL_ATRIBUTOS_ADMINISTRADORES)
            {
                i++;
                cuentaAdministradores++;
                sinRegistros=falso;
                lineasLeidas=0;
            }

        }

        if(!sinRegistros)
        {
            printf("Se han cargado %d registos de administradores!\n\n",cuentaAdministradores);
        }
    }

    else
    {
        printf("No se pudo leer el archivo o aun no se ha registrado a ningun trabajador!\n\n");

    }
    fclose(lecturaadministradores);
}

int queTrabajadorIngreso(char *numTrabajador)
{
    int i;

    for(i=0; i<TOTAL_ADMINISTRADORES; i++)
    {
        if(strcmp(numTrabajador,administradores[i].numTrabajador)==0)
        {
            break;
        }
    }
    return i;
}

int queClienteIngreso(char* correoIniciado)
{
    int i;

    for(i=0; i<TOTAL_CLIENTES; i++)
    {
        if(strcmp(correoIniciado,clientes[i].correo)==0)
        {
            break;
        }
    }
    return i;
}



void altaTrabajador()
{
    if(cuentaAdministradores<TOTAL_ADMINISTRADORES)
    {
        pedirDatosEmpleado(cuentaAdministradores);
        cuentaAdministradores++;
        guardarArchivoTrabajador();
        printf("\n\nRegistro completado!");
    }
    else
    {
        printf("\n\nYa no hay mas espacio de captura!\n\n");
    }
    pausa();
}

void altaCliente()
{
    if(cuentaClientes<TOTAL_CLIENTES)
    {
        pedirDatosCliente(cuentaClientes);
        cuentaClientes++;
        guardarArchivoCliente();
        printf("\n\nRegistro completado!");
    }
    else
    {
        printf("\n\nYa no hay mas espacio de captura!\n\n");
    }
    pausa();
}

void pedirDatosPelicula(int i)
{
    int opcion;
    fflush(stdin);
    printf("Ingrese el nombre de la pelicula: ");
    gets(peliculas[i].nombre);
    fflush(stdin);
    printf("Ingrese los actores: ");
    gets(peliculas[i].actores);
    fflush(stdin);
    printf("Ingrese el genero: ");
    gets(peliculas[i].genero);
    fflush(stdin);
    printf("Ingrese la sinopsis: ");
    gets(peliculas[i].sinopsis);
    fflush(stdin);
    printf("Ingrese la duracion de la pelicula: ");
    scanf("%f",&peliculas[i].duracion);
    fflush(stdin);
    printf("Ingrese el tipo de pelicula: \n\n");
    printf("1. Normal\n\n");
    printf("2. Estreno\n\n");
    printf("Opcion: ");
    scanf("%d",&opcion);
    fflush(stdin);
    while(opcion<0||opcion>2)
    {
        printf("\n\nHas ingresado una opcion no valida!\n\n");
        printf("\n\nIngresa el tipo de pelicula: \n\n");
        printf("1. Normal\n\n");
        printf("2. Estreno\n\n");
        printf("Opcion (1 / 2): ");
        scanf("%d",&opcion);
        fflush(stdin);
    }
    if(opcion==1)
    {
        peliculas[i].tipo=normal;
    }

    else if(opcion==2)
    {
        peliculas[i].tipo=estreno;
    }
}

void altaPelicula()
{
    if(cuentaPeliculas<TOTAL_PELICULAS)
    {
        pedirDatosPelicula(cuentaPeliculas);
        cuentaPeliculas++;
        guardarArchivoPelicula();
        printf("\n\nRegistro completado!");
    }
    else
    {
        printf("\n\nYa no hay mas espacio de captura!\n\n");
    }
    pausa();
}

void limpiarRegistroCliente(int i)
{
    strcpy(clientes[i].correo,"");
    strcpy(clientes[i].clave,"");
    strcpy(clientes[i].nombre,"");
    strcpy(clientes[i].numTarjetaCredito,"");
    clientes[i].membresia=0;
}

void limpiarRegistroPelicula(int i)
{
    strcpy(peliculas[i].nombre,"");
    strcpy(peliculas[i].actores,"");
    strcpy(peliculas[i].genero,"");
    strcpy(peliculas[i].sinopsis,"");
    peliculas[i].duracion=0;
    peliculas[i].tipo=0;
}

void limpiarRegistroTrabajador(int i)
{
    strcpy(administradores[i].numTrabajador,"");
    strcpy(administradores[i].clave,"");
    strcpy(administradores[i].domicilio,"");
    strcpy(administradores[i].nombre,"");
    strcpy(administradores[i].telefono,"");
    administradores[i].sueldo=0;
}

void inicializarRegistros()
{
    int i;
    for(i=0; i<TOTAL_ADMINISTRADORES; i++)
    {
        limpiarRegistroTrabajador(i);
    }

    for(i=0; i<TOTAL_CLIENTES; i++)
    {
        limpiarRegistroCliente(i);
    }

    for(i=0; i<TOTAL_PELICULAS; i++)
    {
        limpiarRegistroPelicula(i);
    }
}

void guardarArchivoCliente()
{
    int i;
    FILE *escritura;
    escritura=fopen("clientes.txt","w");


    for(i=0; i<cuentaClientes; i++)
    {

        fprintf(escritura,"%s\n",clientes[i].nombre);
        fprintf(escritura,"%s\n",clientes[i].correo);
        fprintf(escritura,"%s\n",clientes[i].clave);
        fprintf(escritura,"%s\n",clientes[i].numTarjetaCredito);
        if(clientes[i].membresia==basico)
        {
            fputs("basico\n",escritura);
        }
        else
        {
            fputs("premium\n",escritura);
        }

    }
    fclose(escritura);
}

void guardarArchivoTrabajador()
{
    FILE *escritura;
    escritura=fopen("trabajadores.txt","w");
    int i;
    for(i=0; i<cuentaAdministradores; i++)
    {
        fprintf(escritura,"%s\n",administradores[i].nombre);
        fprintf(escritura,"%s\n",administradores[i].numTrabajador);
        fprintf(escritura,"%s\n",administradores[i].clave);
        fprintf(escritura,"%s\n",administradores[i].domicilio);
        fprintf(escritura,"%ld\n",administradores[i].sueldo);
        fprintf(escritura,"%s\n",administradores[i].telefono);
    }

    fclose(escritura);
}

void guardarArchivoPelicula()
{
    int i;
    FILE *escritura;
    escritura=fopen("peliculas.txt","w");

    for(i=0; i<cuentaPeliculas; i++)
    {
        fprintf(escritura,"%s\n",peliculas[i].nombre);
        fprintf(escritura,"%s\n",peliculas[i].actores);
        fprintf(escritura,"%s\n",peliculas[i].genero);
        fprintf(escritura,"%s\n",peliculas[i].sinopsis);
        fprintf(escritura,"%f\n",peliculas[i].duracion);

        if(peliculas[i].tipo==normal)
        {
            fputs("normal\n",escritura);
        }
        else
        {
            fputs("estreno\n",escritura);
        }

    }
    fclose(escritura);
}

void bienvenida()
{
    printf("\t\t\t***Bienvenido a la plataforma de peliculas de i-PELIs***\n\n");
    printf("Suscribete a la membresia premium y disfruta de las mejores peliculas de estreno\n\n");
    pausa();
    system(CLEAR);
}

//*************************************************************************************************

void mostrarDatosCliente(int i)
{
    printf("Nombre: %s\n",clientes[i].nombre);
    printf("Correo: %s\n",clientes[i].correo);
    printf("Clave: %s\n",clientes[i].clave);
    printf("Numero de tarjeta de credito: %s\n",clientes[i].numTarjetaCredito);
    if(clientes[i].membresia==basico)
    {
        printf("Tipo de membresia: Basica\n\n");
    }
    else
    {
        printf("Tipo de membresia: Premium\n\n");
    }

}

void mostrarDatosTrabajador(int i)
{
    printf("\n\nNombre: %s\n",administradores[i].nombre);
    printf("Numero de trabajador: %s\n",administradores[i].numTrabajador);
    printf("Clave: %s\n",administradores[i].clave);
    printf("Domicilio: %s\n",administradores[i].domicilio);
    printf("Telefono: %s\n",administradores[i].telefono);
    printf("Suelgo: %ld\n\n",administradores[i].sueldo);
}

void mostrarDatosPelicula(int i)
{

    printf("\tNombre: %s\n",peliculas[i].nombre);
    printf("\tSinopsis: %s\n",peliculas[i].sinopsis);
    printf("\tActores: %s\n",peliculas[i].actores);
    printf("\tGenero: %s\n",peliculas[i].genero);
    printf("\tDuracion: %.2f\n",peliculas[i].duracion);
    if(peliculas[i].tipo==normal)
    {
        printf("\tTipo: Normal\n\n");
    }
    else
    {
        printf("\tTipo: Estreno\n\n");
    }

}

void menuCliente(char *correo)
{
    int i;
    int opcion;
    i=queClienteIngreso(correo);
    do
    {
        system(CLEAR);
        printf("Bienvenido %s",clientes[i].nombre);
        printf("   ****Usuario con suscripcion: ");
        if(clientes[i].membresia==basico)
        {
            printf("Basica");
        }
        else
        {
            printf("Premium");
        }
        printf(" ***\n\n");
        printf("1. Ver peliculas Online\n\n");
        printf("2. Salir\n\n");
        fflush(stdin);
        printf("Opcion: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            system(CLEAR);
        case 1:
            if(clientes[i].membresia==premium)
            {
                menuClientePremium();
            }
            else
            {
                menuClienteBasico();
            }
            break;

        case 2:
            break;

        default:
            imprimirError();
            break;

        }
    }
    while(opcion!=2);
}

void menuTrabajador(char *numTrabajador)
{
    int i;
    int opcion;
    system(CLEAR);
    i=queTrabajadorIngreso(numTrabajador);
    do
    {
        printf("***Bienvenido %s***\n\n",administradores[i].nombre);
        opcion=opcionesMenuTrabajador();

        switch(opcion)
        {
            system(CLEAR);
        case 1:
            menuAdminClientes();
            break;

        case 2:
            menuPelicula();
            break;

        case 3:
            break;

        default:
            imprimirError();
            break;

        }
    }
    while(opcion!=3);
    pausa();
}

void menuClientePremium()
{
    system(CLEAR);
    int opcion;
    int i;
    for(i=0; i<cuentaPeliculas; i++)
    {
        printf("%d",i+1);
        mostrarDatosPelicula(i);
    }

    fflush(stdin);
    printf("\n\nEscoge el numero de la pelicula que deseas reproducir: ");
    scanf("%d",&opcion);

    while(opcion>cuentaPeliculas||opcion<0)
    {
        fflush(stdin);
        printf("\n\nEscoge el numero de la pelicula que deseas reproducir: ");
        scanf("%d",&opcion);
    }

    reproducirPelicula(--opcion);
}

void menuClienteBasico()
{
    system(CLEAR);
    int opcion,aux=0;
    int j,i;
    int cuentaPeliculasBasicas=0;
    for(i=0; i<cuentaPeliculas; i++)
    {
        if(peliculas[i].tipo==normal)
        {
            printf("%d",cuentaPeliculasBasicas+1);
            mostrarDatosPelicula(i);
            cuentaPeliculasBasicas++;
        }
    }

    fflush(stdin);
    printf("\n\nEscoge el numero de la pelicula que deseas reproducir: ");
    scanf("%d",&opcion);

    while(opcion>cuentaPeliculasBasicas||opcion<0)
    {
        fflush(stdin);
        printf("\n\nEscoge el numero de la pelicula que deseas reproducir: ");
        scanf("%d",&opcion);
    }

    for(j=0; j<cuentaPeliculas; j++)
    {
        if(peliculas[j].tipo==normal)
        {
            aux++;
            if(aux==opcion)
            {
                break;
            }
        }
    }
    reproducirPelicula(j);
}

void reproducirPelicula(int numPelicula)
{
    system(CLEAR);
    printf("\n\n\n\nReproduciendo pelicula: %s.mp4\n\n",peliculas[numPelicula].nombre);
    pausa();
}

void modificarPelicula()
{
    char nombreBuscar[TAMANO_CADENA];
    fflush(stdin);
    printf("MODIFICAR UNA PELICULA\n\n");
    printf("Ingresa el nombre de la pelicula que deseas modificar: ");
    gets(nombreBuscar);
    if(coincideNombrePelicula(nombreBuscar))
    {
        int i=damePosicionPelicula(nombreBuscar);
        mostrarDatosPelicula(i);
        fflush(stdin);
        printf("***********************************************************************\n\n");
        printf("Nuevos Datos: \n\n");
        pedirDatosPelicula(i);
        guardarArchivoPelicula();
        printf("\nRegistro Modificado!\n");
    }
    else
    {
        printf("\n\nNo se encontro ninguna pelicula con ese nombre!\n");
    }

    pausa();

}

void bajaPelicula()
{
    char nombreBuscar[TAMANO_CADENA];
    fflush(stdin);
    char respuesta;
    printf("DAR DE BAJA UNA PELICULA\n\n");
    printf("Ingresa el nombre de la pelicula que deseas eliminar: ");
    gets(nombreBuscar);
    if(coincideNombrePelicula(nombreBuscar))
    {
        int i=damePosicionPelicula(nombreBuscar);
        mostrarDatosPelicula(i);
        fflush(stdin);
        printf("\nDeseas borrar a esta pelicula (s/n) : ");
        scanf("%c",&respuesta);
        fflush(stdin);
        if(respuesta=='s'||respuesta=='S')
        {
            for(cuentaPeliculas--; i<cuentaPeliculas; i++)
            {
                peliculas[i]=peliculas[i+1];
            }
            guardarArchivoPelicula();
            printf("\nRegistro Eliminado!\n");
        }
        else
        {
            printf("\nRegistro Conservado!\n");
        }
    }
    else
    {
        printf("\n\nNo se encontro ninguna pelicula con ese nombre!\n");
    }

    pausa();

}

void listarPeliculas()
{
    int i;
    if(cuentaPeliculas>0)
    {
        for(i=0; i<cuentaPeliculas; i++)
        {
            mostrarDatosPelicula(i);
        }
    }
    else
    {
        printf("\n\nNo hay ninguna pelicula registrado!\n");
    }

    pausa();
}

void buscarPelicula()
{
    int encontrados=0;
    int i;
    char* patron;
    char nombreBuscar[TAMANO_CADENA];
    fflush(stdin);

    printf("Ingresa el nombre de la pelicula que deseas buscar: ");
    gets(nombreBuscar);

    for(i=0; i<cuentaPeliculas; i++)
    {
        patron=strstr(peliculas[i].nombre,nombreBuscar);
        if (patron!=NULL)
        {
            mostrarDatosPelicula(i);
            printf("\n\n");
            encontrados++;
        }

    }

    if (encontrados)
    {
        printf("Se encontro %d registro(s) con la palabra buscada\n",encontrados);
    }
    else
    {
        printf("No se encontro algun registro con la palabra buscada\n");
    }

    pausa();


}

booleano coincideNombrePelicula(char* nombrePelicula)
{
    booleano coincide=falso;
    int i;

    for(i=0; i<cuentaPeliculas; i++)
    {
        if (strcmp(peliculas[i].nombre,nombrePelicula)==0)
        {
            coincide=verdadero;
            break;
        }
    }

    return coincide;

}

int damePosicionPelicula(char* nombrePelicula)
{
    int posicion;
    int i;

    for(i=0; i<cuentaPeliculas; i++)
    {
        if (strcmp(peliculas[i].nombre,nombrePelicula)==0)
        {
            posicion=i;
            break;
        }
    }

    return posicion;
}

int opcionesMenuPelicula()
{
    fflush(stdin);
    int opcion;
    printf("1. Dar de alta una pelicula\n");
    printf("2. Dar de baja una pelicula\n");
    printf("3. Modificar una pelicula\n");
    printf("4. Buscar una pelicula\n");
    printf("5. Listar peliculas\n");
    printf("6. Salir\n\n");
    printf("Opcion: ");
    scanf("%d",&opcion);
    while(opcion<0||opcion>6)
    {
        fflush(stdin);
        printf("Opcion: ");
        scanf("%d",&opcion);
    }
    system(CLEAR);
    return opcion;
}

void menuPelicula()
{
    int opcion;
    do
    {
        system(CLEAR);
        printf("ADMINISTRACION DE PELICULAS\n\n");
        opcion=opcionesMenuPelicula();
        switch(opcion)
        {
        case 1:
            altaPelicula();
            break;

        case 2:
            bajaPelicula();
            break;

        case 3:
            modificarPelicula();
            break;

        case 4:
            buscarPelicula();
            break;

        case 5:
            listarPeliculas();
            break;

        case 6:
            break;

        default:
            imprimirError();
            break;
        }

        system(CLEAR);
    }
    while(opcion!=6);

}

int opcionesMenuTrabajador()
{
    fflush(stdin);
    int opcion;
    printf("1. Administracion de clientes\n");
    printf("2. Administracion de Peliculas\n");
    printf("3. Salir\n\n");
    printf("Opcion: ");
    scanf("%d",&opcion);
    while(opcion<0||opcion>3)
    {
        fflush(stdin);
        printf("Opcion: ");
        scanf("%d",&opcion);
    }
    system(CLEAR);
    return opcion;
}

void modificarCliente()
{
    char correoBuscar[TAMANO_CADENA];
    fflush(stdin);
    printf("MODIFICAR UN CLIENTE\n\n");
    printf("Ingresa el correo del cliente que deseas modificar: ");
    gets(correoBuscar);
    if(coincideCorreoCliente(correoBuscar))
    {
        int i=damePosicionCliente(correoBuscar);
        mostrarDatosCliente(i);
        fflush(stdin);
        printf("***********************************************************************\n\n");
        printf("Nuevos Datos: \n\n");
        pedirDatosCliente(i);
        guardarArchivoCliente();
        printf("\nRegistro Modificado!\n");
    }
    else
    {
        printf("\n\nNo se encontro ningun cliente con ese correo!\n");
    }

    pausa();
}
void bajaCliente()
{
    char correoBuscar[TAMANO_CADENA];
    fflush(stdin);
    char respuesta;
    printf("DAR DE BAJA UN CLIENTE\n\n");
    printf("Ingresa el correo del que deseas eliminar: ");
    gets(correoBuscar);
    if(coincideCorreoCliente(correoBuscar))
    {
        int i=damePosicionCliente(correoBuscar);
        mostrarDatosCliente(i);
        fflush(stdin);
        printf("\nDeseas borrar a este cliente (s/n) : ");
        scanf("%c",&respuesta);
        fflush(stdin);
        if(respuesta=='s'||respuesta=='S')
        {
            for(cuentaClientes--; i<cuentaClientes; i++)
            {
                clientes[i]=clientes[i+1];
            }
            guardarArchivoCliente();
            printf("\nRegistro Eliminado!\n");
        }
        else
        {
            printf("\nRegistro Conservado!\n");
        }
    }
    else
    {
        printf("\n\nNo se encontro ningun cliente con ese correo!\n");
    }

    pausa();

}
void listarClientes()
{
    int i;
    if(cuentaClientes>0)
    {
        for(i=0; i<cuentaClientes; i++)
        {
            mostrarDatosCliente(i);
        }
    }
    else
    {
        printf("\n\nNo hay ningun cliente registrado!\n");
    }

    pausa();

}
void buscarCliente()
{
    int encontrados=0;
    int i;
    char* patron;
    char nombreBuscar[TAMANO_CADENA];
    fflush(stdin);

    printf("Ingresa el nombre del cliente que deseas buscar: ");
    gets(nombreBuscar);

    for(i=0; i<cuentaClientes; i++)
    {
        patron=strstr(clientes[i].nombre,nombreBuscar);
        if (patron!=NULL)
        {
            mostrarDatosCliente(i);
            printf("\n\n");
            encontrados++;
        }

    }

    if (encontrados)
    {
        printf("Se encontro %d registro(s) con la palabra buscada\n",encontrados);
    }
    else
    {
        printf("No se encontro algun registro con la palabra buscada\n");
    }

    pausa();

}

booleano coincideCorreoCliente(char *correoCliente)
{
    int i;
    booleano coincide=falso;

    for(i=0; i<cuentaClientes; i++)
    {
        if(strcmp(correoCliente,clientes[i].correo)==0)
        {
            coincide=verdadero;
            break;
        }
    }

    return coincide;
}

int damePosicionCliente(char* correoCliente)
{
    int i;
    int posicion;

    for(i=0; i<cuentaClientes; i++)
    {
        if(strcmp(correoCliente,clientes[i].correo)==0)
        {
            posicion=i;
            break;
        }
    }

    return posicion;

}

int opcionesMenuCliente()
{
    fflush(stdin);
    int opcion;
    printf("1. Dar de alta un cliente\n");
    printf("2. Dar de baja un cliente\n");
    printf("3. Modificar un cliente\n");
    printf("4. Buscar un cliente\n");
    printf("5. Listar clientes\n");
    printf("6. Salir\n\n");
    printf("Opcion: ");
    scanf("%d",&opcion);
    while(opcion<0||opcion>6)
    {
        fflush(stdin);
        printf("Opcion: ");
        scanf("%d",&opcion);
    }
    system(CLEAR);
    return opcion;

}
void menuAdminClientes()
{
    int opcion;
    do
    {
        system(CLEAR);
        printf("ADMINISTRACION DE CLIENTES\n\n");
        opcion=opcionesMenuCliente();
        switch(opcion)
        {
        case 1:
            altaCliente();
            break;

        case 2:
            bajaCliente();
            break;

        case 3:
            modificarCliente();
            break;

        case 4:
            buscarCliente();
            break;

        case 5:
            listarClientes();
            break;

        case 6:
            break;

        default:
            imprimirError();
            break;
        }

        system(CLEAR);
    }
    while(opcion!=6);

}

void menuGerente()
{
    int opcion;
    do
    {
        system(CLEAR);
        printf("ADMINISTRACION DE TRABAJADORES\n\n");
        opcion=opcionesMenuGerente();
        switch(opcion)
        {
        case 1:
            altaTrabajador();
            break;

        case 2:
            bajaTrabajador();
            break;

        case 3:
            modificarTrabajador();
            break;

        case 4:
            buscarTrabajador();
            break;

        case 5:
            listarTrabajadores();
            break;

        case 6:
            break;

        default:
            imprimirError();
            break;
        }
        system(CLEAR);
    }
    while(opcion!=6);

}


void modificarTrabajador()
{
    char buscarNumero[TAMANO_CADENA];
    fflush(stdin);
    printf("MODIFICAR UN TRABAJADOR\n\n");
    printf("Ingresa el numero del trabajador que deseas modificar: ");
    gets(buscarNumero);
    if(coincideNumeroTrabajador(buscarNumero))
    {
        int i=damePosicionTrabajador(buscarNumero);
        mostrarDatosTrabajador(i);
        fflush(stdin);
        printf("***********************************************************************\n\n");
        printf("Nuevos Datos: \n\n");
        pedirDatosEmpleado(i);
        guardarArchivoTrabajador();
        printf("\nRegistro Modificado!\n");
    }
    else
    {
        printf("\n\nNo se encontro ningun empleado con ese numero!\n");
    }

    pausa();

}


void bajaTrabajador()
{
    char buscarNumero[TAMANO_CADENA];
    fflush(stdin);
    char respuesta;
    printf("DAR DE BAJA UN TRABAJADOR\n\n");
    printf("Ingresa el numero del trabajador que deseas eliminar: ");
    gets(buscarNumero);
    if(coincideNumeroTrabajador(buscarNumero))
    {
        int i=damePosicionTrabajador(buscarNumero);
        mostrarDatosTrabajador(i);
        fflush(stdin);
        printf("\nDeseas borrar a este empleado (s/n) : ");
        scanf("%c",&respuesta);
        fflush(stdin);
        if(respuesta=='s'||respuesta=='S')
        {
            for(cuentaAdministradores--; i<cuentaAdministradores; i++)
            {
                administradores[i]=administradores[i+1];
            }
            guardarArchivoTrabajador();
            printf("\nRegistro Eliminado!\n");
        }
        else
        {
            printf("\nRegistro Conservado!\n");
        }
    }
    else
    {
        printf("\n\nNo se encontro ningun empleado con ese numero!\n");
    }

    pausa();

}


void listarTrabajadores()
{
    int i;
    if(cuentaAdministradores>0)
    {
        for(i=0; i<cuentaAdministradores; i++)
        {
            mostrarDatosTrabajador(i);
        }
    }
    else
    {
        printf("\n\nNo hay ningun empleado registrado!\n");
    }

    pausa();

}


void buscarTrabajador()
{
    int encontrados=0;
    int i;
    char* patron;
    char nombreBuscar[TAMANO_CADENA];
    fflush(stdin);

    printf("Ingresa el nombre del empleado que deseas buscar: ");
    gets(nombreBuscar);

    for(i=0; i<cuentaAdministradores; i++)
    {
        patron=strstr(administradores[i].nombre,nombreBuscar);
        if (patron!=NULL)
        {
            mostrarDatosTrabajador(i);
            printf("\n\n");
            encontrados++;
        }

    }

    if (encontrados)
    {
        printf("Se encontro %d registro(s) con la palabra buscada\n",encontrados);
    }
    else
    {
        printf("No se encontro algun registro con la palabra buscada\n");
    }

    pausa();

}


booleano coincideNumeroTrabajador(char *numTrabajador)
{
    int i;
    booleano coincide=falso;

    for(i=0; i<cuentaAdministradores; i++)
    {
        if(strcmp(numTrabajador,administradores[i].numTrabajador)==0)
        {
            coincide=verdadero;
            break;
        }
    }

    return coincide;

}


int damePosicionTrabajador(char* numTrabajador)
{
    int i;
    int posicion;

    for(i=0; i<cuentaAdministradores; i++)
    {
        if(strcmp(numTrabajador,administradores[i].numTrabajador)==0)
        {
            posicion=i;
            break;
        }
    }

    return posicion;

}


int opcionesMenuGerente()
{
    fflush(stdin);
    int opcion;
    printf("1. Dar de alta a un empleado\n");
    printf("2. Dar de baja a un empleado\n");
    printf("3. Modificar a un empleado\n");
    printf("4. Buscar a un empleado\n");
    printf("5. Listar empleados\n");
    printf("6. Salir\n\n");
    printf("Opcion: ");
    scanf("%d",&opcion);
    while(opcion<0||opcion>6)
    {
        fflush(stdin);
        printf("Opcion: ");
        scanf("%d",&opcion);
    }
    system(CLEAR);
    return opcion;
}

void inicioSesionGerente()
{
    system(CLEAR);
    fflush(stdin);
    char numero[TAMANO_CADENA];
    char clave [TAMANO_CADENA];

    printf("Ingresa el numero confidencial del gerente ");
    printf("(se encuentra en la primera linea del codigo): ");
    gets(numero);
    fflush(stdin);
    ocultarClave(clave);
    fflush(stdin);

    while(!datosCorrectosGerente(numero,clave))
    {
        printf("\n\nLos datos no coinciden, intentalo de nuevo...\n\n");
        printf("Ingresa el numero confidencial del gerente ");
        printf("(se encuentra en la primera linea del codigo): ");
        gets(numero);
        fflush(stdin);
        ocultarClave(clave);
        fflush(stdin);
    }

    pausa();
    menuGerente();
    pausa();

}

booleano datosCorrectosGerente(char* num, char* clave)
{
    booleano coincide=falso;

    char numeroGerente[]="12345";
    char claveGerente[]="12345";

    if(strcmp(num,numeroGerente)==0||strcmp(clave,claveGerente)==0)
    {
        coincide=verdadero;
    }

    return coincide;
}
