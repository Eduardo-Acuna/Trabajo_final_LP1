#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 10
#define MAX_USUARIOS 100
#define MAX_NOMBRE 50

#define OCULTA 0
#define DESCUBIERTA 1
#define BANDERA 2

typedef struct {
    int numUsuario;
    char nombre[MAX_NOMBRE];
    char contrasena[20];
    int partidasJugadas;
    int partidasGanadas;
    int partidasPerdidas;
    int partidasEmpatadas;
    int puntajeTotal;
    int puntajeJugador1;
    int puntajeJugador2;
} Jugador;

typedef struct {
    char nombre[MAX_NOMBRE];
    int puntaje;
} Puntaje;

typedef struct {
    int esMina;
    int minasAdyacentes;
    int estado;
} Celda;

typedef struct {
    int fila;
    int columna;
    int numMinas;
    Celda celdas[MAX_SIZE][MAX_SIZE];
} Tablero;

// Variables globales
Jugador jugadores[MAX_USUARIOS];
int cantidadJugadores = 0;
Jugador jugadorActual;
Tablero tablero;

// Se crea una variable global del tipo Jugador
extern Jugador jugadorActual;

// Función que muestra el inicio del programa
void inicio_programa();

// Funciones del menú principal
void menu_principal();
void mostrar_menu_principal();
int validar_opcion_menu_principal();

// Funciones de la opción de Iniciar Juego
void iniciar_juego();
void guardar_resultado();

// Funciones de la opción de Configuraciones
void mostrar_menu_configuracion();
void cambiar_nombre_de_usuario();
void cambiar_contrasena();

// Funciones de la opción de registro de jugador
void mostrar_menu_registro_jugador();
int validar_menu_registro_jugador();
int buscar_jugador();

void lista_jugadores_mostrar_menu_registro_jugador();
void resgistro_jugador_mostrar_menu_registro_jugador();

// Funciones de la opción de estadística
void mostrar_estadistica();
void mayor_puntaje();
void estadistica_de_usuario();

// Funciones de la opción reglas del juego
void regla_juego();

// Funciones globales que ayudan al programa
void setConsoleUtf8();
void enter_continuar();
void limpiar_pantalla();

// Funciones para el juego
void inicializarTablero(int fila, int columna, int numMinas);
void colocarMinas(int numMinas);
void calcularMinasAdyacentes();
void mostrarTablero();
void descubrirCelda(int x, int y);
void marcarCelda(int x, int y);
int verificarVictoria();
void mostrarPuntaje();
void turnoJugador();
void turnoComputadora();
void mostrarPuntajeJugador1y2();
void mostrarTableroFinal();

// Funciones de gestión de usuarios
void cargarUsuarios();
void guardarUsuarios();
void registrarUsuario();
void actualizarJugadorActual();
int existeUsuario(const char* nombre);


// Función principal del programa
int main() {

    srand(time(NULL));
    setConsoleUtf8();

    //cargarUsuarios(); // Cargar usuarios desde el archivo al inicio

    inicio_programa();

    registrarUsuario();

    //menu_principal();
    actualizarJugadorActual(); // Asegúrate de actualizar los datos del jugador actual antes de guardar
    guardarUsuarios(); // Guardar usuarios antes de finalizar el programa

    return 0;
}




//#########################################################################################
// Función que muestra el inicio del programa y del menú principal
//#########################################################################################

// Esta función inicializa y configura la consola, y luego muestra el menú principal.
void inicio_programa() {
    printf("\n       +---------------------------------------------------------------------------------------------+");
    printf("\n       |                         J U E G O     D E    B U S C A M I N A                              |");
    printf("\n       +---------------------------------------------------------------------------------------------+");
    printf("\n       |                                                                                             |");
    printf("\n       | El juego de Buscaminas es un juego de estrategia que requiere habilidades de logica y       |");
    printf("\n       | deduccion. Los jugadores deben descubrir todas las celdas libres de minas en el tablero     |");
    printf("\n       | utilizando pistas numéricas sobre el número de minas adyacentes. La estrategia consiste     |");
    printf("\n       | en interpretar correctamente estas pistas para evitar descubrir celdas con minas.           |");
    printf("\n       |                                                                                             |");
    printf("\n       +---------------------------------------------------------------------------------------------+\n\n\n\n");

    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           1. INICIAR SESION               |");
    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           2. REGISTRARSE                  |");
    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           0. CERRAR                       |");
    printf("\n                             +-------------------------------------------+");

    int opcion;

    do {
        printf("\n\n       [↵] ELIJA UNA OPCION: ");
        scanf("%d", &opcion);
        if (!(opcion >= 0 && opcion <= 2)) {
            printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
        }
    } while (!(opcion >= 0 && opcion <= 2));

    if (opcion == 1) {
        iniciarSesion();
    } else if (opcion == 2) {
        registrarUsuario();
    } else if (opcion == 0) {
        limpiar_pantalla();
        guardarUsuarios();
        printf("\n                             +-------------------------------------------+");
        printf("\n                             |                                           |");
        printf("\n                             |     ¡Gracias por jugar al Buscaminas!     |");
        printf("\n                             |            Hasta la próxima               |");
        printf("\n                             |                                           |");
        printf("\n                             +-------------------------------------------+");
        exit(0);
    }
}

// Muestra el menú principal en la pantalla, permitiendo al usuario seleccionar entre varias opciones.
void menu_principal() {

    int opcion;

    do {
        mostrar_menu_principal();

        opcion = validar_opcion_menu_principal();
        switch (opcion) {
            case 1:
                iniciar_juego();
                break;
            case 2:
                mostrar_menu_configuracion();
                break;
            case 3:
                mostrar_menu_registro_jugador();
                break;
            case 4:
                mostrar_estadistica();
                break;
            case 5:
                regla_juego();
                break;
            case 6:
                guardarUsuarios();
                inicio_programa();
                break;
            case 0:
                guardarUsuarios();
                printf("\n                             +-------------------------------------------+");
                printf("\n                             |                                           |");
                printf("\n                             |     ¡Gracias por jugar al Buscaminas!     |");
                printf("\n                             |            Hasta la próxima               |");
                printf("\n                             |                                           |");
                printf("\n                             +-------------------------------------------+");
                exit(0);
                break;
        }
    } while( opcion!=0 );
} // fin menu_principal

// Despliega las opciones disponibles en el menú principal.
void mostrar_menu_principal() {
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                           M E N U     P R I N C I P A L                                     |");
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                                                                                             |");
    printf("\n         |       ( 1 ) Iniciar Juego                                                                   |");
    printf("\n         |       ( 2 ) Configuracion                                                                   |");
    printf("\n         |       ( 3 ) Registro de Jugadores                                                           |");
    printf("\n         |       ( 4 ) Ver Estadistica                                                                 |");
    printf("\n         |       ( 5 ) Regla del Juego                                                                 |");
    printf("\n         |       ( 6 ) Cerrar Sesión                                                                   |");
    printf("\n         |       ( 0 ) Salir                                                                           |");
    printf("\n         |                                                                                             |");
    printf("\n         +---------------------------------------------------------------------------------------------+");
}

// Valida la opción seleccionada por el usuario en el menú principal, asegurando que sea una opción válida.
int validar_opcion_menu_principal() {
    int opcion;
    do {
        printf("\n\n\n         [↵] ELIJA UNA OPCION: ");
        scanf("%d", &opcion);
        if( !(opcion>=0 && opcion<=6)) {
            printf("         [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
        }
    } while( !(opcion>=0 && opcion<=6 ));
    limpiar_pantalla();
    return opcion;
}




//#########################################################################################
// Funciones de la opción de Iniciar Juego
//#########################################################################################

// Inicia una nueva partida del juego, configurando el tablero y registrando los jugadores.
void iniciar_juego() {

    int fila, columna, numMinas, control;

    printf("\n       +---------------------------------------------------------------------------------------------+");
    printf("\n       |                            I N I C I O    D E L    J U E G O                                |");
    printf("\n       +---------------------------------------------------------------------------------------------+");

    do {
        control = 0;
        printf("\n       | Ingrese el tamaño del tablero y la cantidad de minas                                        |");
        printf("\n       +---------------------------------------------------------------------------------------------+");
        printf("\n\t\t (FILA,COLUMNA): ");
        scanf("%d %d", &fila, &columna);
        printf("\t\t Cant. Mina: ");
        scanf("%d", &numMinas);

        if( fila<1 || fila>10 ){
            control = 1;
            limpiar_pantalla();
            printf("\n       +---------------------------------------------------------------------------------------------+");
            printf("\n       |                            I N I C I O    D E L    J U E G O                                |");
            printf("\n       +---------------------------------------------------------------------------------------------+");
            printf("\n       | [↵] VUELVA A INTENTAR. Fila fuera de rango.                                                 |");
            printf("\n       +---------------------------------------------------------------------------------------------+");
        }
        if( columna<1 || columna>10 ){
            control = 1;
            limpiar_pantalla();
            printf("\n       +---------------------------------------------------------------------------------------------+");
            printf("\n       |                            I N I C I O    D E L    J U E G O                                |");
            printf("\n       +---------------------------------------------------------------------------------------------+");
            printf("\n       | [↵] VUELVA A INTENTAR. Columna fuera de rango.                                              |");
            printf("\n       +---------------------------------------------------------------------------------------------+");
        }
        if( numMinas<1 || numMinas>fila*columna-1 ){
            control = 1;
            limpiar_pantalla();
            printf("\n       +---------------------------------------------------------------------------------------------+");
            printf("\n       |                            I N I C I O    D E L    J U E G O                                |");
            printf("\n       +---------------------------------------------------------------------------------------------+");
            printf("\n       | [↵] VUELVA A INTENTAR. Mina fuera de rango.                                                 |");
            printf("\n       +---------------------------------------------------------------------------------------------+");
        }

    } while( control );

    inicializarTablero(fila, columna, numMinas);// Inicializa el tablero con las dimensiones y el número de minas proporcionados.
    limpiar_pantalla();
    jugadorActual.partidasJugadas++; // Incrementa el contador de partidas jugadas del jugador actual.

    while (1) { // Bucle principal del juego.
        mostrarTablero(); // Muestra el tablero actual.
        turnoJugador(); // Ejecuta el turno del jugador.
        turnoComputadora();   // Ejecuta el turno de la computadora.
    }
}

// Ejecuta el turno de la computadora, realizando una acción en el tablero.
void turnoComputadora() {
    int x,y;

    printf("\n\t J U G A D O R    2");

    // Genera coordenadas aleatorias dentro del rango del tablero.
    x = rand()%tablero.fila;
    y = rand()%tablero.columna;

    // Repite mientras la celda seleccionada no esté oculta (para evitar seleccionar una celda ya descubierta).
    while( tablero.celdas[x][y].estado!=OCULTA ){
        x = rand()%tablero.fila;
        y = rand()%tablero.columna;
    }

    // Descubre la celda en las coordenadas seleccionadas.
    printf("\n\t Ingresa las coordenadas (F,C): %d %d", x, y);

    descubrirCelda(x,y);
    //mostrarTablero();

    if (verificarVictoria()) {
        jugadorActual.puntajeJugador2 += 10;
        printf("\n\t Jugador 2 gana 10pts.\n");
        jugadorActual.partidasPerdidas++;
        mostrarTablero();
        printf("\n                             +-----------------------------------------------+");
        printf("\n                             |         G A N O      J U G A D O R   2        |");
        printf("\n                             +-----------------------------------------------+\n\n");
        mostrarTableroFinal();
        actualizarJugadorActual();  // Actualizar datos del jugador actual
        guardarUsuarios();  // Guardar resultado al terminar el juego
        exit(0);
    }
}

// Ejecuta el turno del jugador, permitiéndole realizar una acción en el tablero.
void turnoJugador() {
    int x, y;

    mostrarTablero();

    printf("\n\t J U G A D O R    1");
    printf("\n\t Ingresa las coordenadas (F,C): ");
    scanf("%d %d", &x, &y);

     // Descubre la celda en las coordenadas seleccionadas.
    descubrirCelda(x, y);


    if (verificarVictoria()) {
        printf("\n\t Jugador 1 gana 10pts.\n");
        jugadorActual.puntajeJugador1 += 10;
        jugadorActual.partidasGanadas++;
        jugadorActual.puntajeTotal += 10;
        mostrarTablero();
        printf("\n                             +-----------------------------------------------+");
        printf("\n                             |         G A N O      J U G A D O R   1        |");
        printf("\n                             +-----------------------------------------------+\n\n");
        mostrarTableroFinal(); // Mostrar el tablero final con todas las minas
        actualizarJugadorActual();  // Actualizar datos del jugador actual en el array
        guardarUsuarios();  // Guardar resultado al terminar el juego
        exit(0);
    }
}

// Inicializa el tablero de juego con las dimensiones y número de minas especificados.
void inicializarTablero(int fila, int columna, int numMinas) {
    int i,j;

    tablero.fila=fila;
    tablero.columna=columna;
    tablero.numMinas=numMinas;

    for( i=0 ; i<fila ; i++ ){
        for( j=0 ; j<columna ; j++ ){
            // Inicializa la celda actual:
            tablero.celdas[i][j].esMina=0;// Establece que la celda no contiene una mina.
            tablero.celdas[i][j].minasAdyacentes=0;// Establece el contador de minas adyacentes en 0.
            tablero.celdas[i][j].estado = OCULTA;// Establece el estado inicial de la celda como oculta.
        }
    }

    colocarMinas(numMinas);// Coloca minas en el tablero.
    calcularMinasAdyacentes();// Calcula el número de minas adyacentes para cada celda.
}

// Coloca las minas aleatoriamente en el tablero.
void colocarMinas(int numMinas) {
    int minasColocadas,x,y;

    minasColocadas = 0;

    while( minasColocadas<numMinas ){
        x = rand() % tablero.fila;
        y = rand() % tablero.columna;
        if( !tablero.celdas[x][y].esMina ){
            tablero.celdas[x][y].esMina = 1;
            minasColocadas++;
        }
    }
}

// Calcula el número de minas adyacentes a cada celda del tablero.
void calcularMinasAdyacentes() {
    int i, j, dx ,dy, nx, ny, conteo;

    // Recorre cada celda del tablero
    for( i=0 ; i<tablero.fila ; i++ ){
        for( j=0 ; j<tablero.columna ; j++ ){
            if( !tablero.celdas[i][j].esMina ){// Si la celda actual no es una mina
                conteo = 0;
                for( dx=-1 ; dx<=1 ; dx++ ){
                    for( dy=-1 ; dy<=1 ; dy++ ){
                        // Coordenada x y de la celda adyacente
                        nx = i + dx;
                        ny = j + dy;
                        // Verifica si la celda adyacente está dentro de los límites del tablero y si contiene una mina
                        if( nx>=0 && nx<tablero.fila && ny>=0 && ny<tablero.columna && tablero.celdas[nx][ny].esMina) {
                            conteo++;
                        }
                    }
                }
                // Almacena el conteo de minas adyacentes en la celda actual
                tablero.celdas[i][j].minasAdyacentes = conteo;
            }
        }
    }
}

// Descubre una celda específica del tablero, revelando si contiene una mina o no.
void descubrirCelda(int x, int y){

    if (x < 0 || x >= tablero.fila || y < 0 || y >= tablero.columna || tablero.celdas[x][y].estado == DESCUBIERTA) {
        return;
    }

    tablero.celdas[x][y].estado = DESCUBIERTA;

    if (tablero.celdas[x][y].esMina) {
        printf("\n                             +-------------------------------------------+");
        printf("\n                             |             ¡ B O O O O M !               |");
        printf("\n                             |     P I S A S T E    U N A    M I N A     |");
        printf("\n                             +-------------------------------------------+\n\n");

        jugadorActual.partidasPerdidas++;
        mostrarTableroFinal();

        guardar_resultado();  // Guardar resultado al terminar el juego
        exit(0);
    }

    int dx,dy;
    if( tablero.celdas[x][y].minasAdyacentes==0 ){
        for( dx=-1 ; dx<=1 ; dx++ ){
            for( dy=-1 ; dy<=1 ; dy++ ){
                descubrirCelda(x + dx, y + dy);
            }
        }
    }
}

// Verifica si el jugador ha ganado la partida, comprobando las condiciones de victoria.
int verificarVictoria(){
    int i,j;

    for( i=0 ; i<tablero.fila ; i++ ){
        for( j=0 ; j<tablero.columna ; j++ ){
            if (!tablero.celdas[i][j].esMina && tablero.celdas[i][j].estado != DESCUBIERTA) {
                return 0;
            }
        }
    }
    return 1;
}

// Muestra el estado actual del tablero en la consola.
void mostrarTablero(){

    limpiar_pantalla();

    printf("\n       +---------------------------------------------------------------------------------------------+");
    printf("\n       |                         J U E G O     D E    B U S C A M I N A S                            |");
    printf("\n       +---------------------------------------------------------------------------------------------+\n");

    int i,j;

    printf("\t\t\t\t\t");
    for( j=0 ; j<=tablero.fila ; j++ ){
        printf("+---");
    }
    printf("+\n");

    // Imprime la línea superior de encabezado de columnas
    printf("\t\t\t\t\t|   ");
    for( j=0 ; j<tablero.fila ; j++ ){
        printf("| %d ", j);
    }
    printf("|\n");

    // Imprime la línea de separación después de los encabezados de columnas
    printf("\t\t\t\t\t");
    for( j=0 ; j<=tablero.fila ; j++ ){
        printf("+---");
    }
    printf("+\n");

    // Imprime las filas del tablero
    for( i=0 ; i<tablero.columna ; i++ ){
        printf("\t\t\t\t\t| %d ",i);

        for( j=0 ; j<tablero.fila ; j++ ){
            if (tablero.celdas[i][j].estado == OCULTA) {
                printf("| . ");
            } else if (tablero.celdas[i][j].estado == BANDERA) {
                printf("| 1 ");
            } else if (tablero.celdas[i][j].esMina) {
                printf("| * ");
            } else {
                printf("| 1 ", tablero.celdas[i][j].minasAdyacentes);
            }
        }
        printf("|\n");

        // Imprime la línea de separación entre las filas
        printf("\t\t\t\t\t+---");
        for( j=0 ; j<tablero.fila ; j++ ){
            printf("+---");
        }
        printf("+\n");
    }
}

// Muestra en la consola el lugar de las minas en el tablero.
void mostrarTableroFinal(){

    int i,j;

    printf("\t\t\t\t\t");
    for( j=0 ; j<=tablero.fila ; j++ ){
        printf("+---");
    }
    printf("+\n");

    printf("\t\t\t\t\t|   ");
    for( j=0 ; j<tablero.fila ; j++ ){
        printf("| %d ", j);
    }
    printf("|\n");

    printf("\t\t\t\t\t");
    for( j=0 ; j<=tablero.fila ; j++ ){
        printf("+---");
    }
    printf("+\n");

    for( i=0 ; i<tablero.columna ; i++ ){
        printf("\t\t\t\t\t| %d ", i);
        for( j=0 ; j<tablero.fila ; j++ ){
            if (tablero.celdas[i][j].esMina) {
                printf("| * ");
            } else {
                printf("|   ", tablero.celdas[i][j].minasAdyacentes);
            }
        }
        printf("|\n");

        printf("\t\t\t\t\t");
        for (int j = 0; j <= tablero.fila; j++) {
            printf("+---");
        }
        printf("+\n");
    }
    mostrarPuntajeJugador1y2();

    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           1. JUEGAR DE NUEVO              |");
    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           2. VOLVER A MENU                |");
    printf("\n                             +-------------------------------------------+");

    int opcion;

    do {
        printf("\n\n       [↵] ELIJA UNA OPCION: ");
        scanf("%d", &opcion);
        if (!(opcion > 0 && opcion <= 2)) {
            printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
        }
    } while (!(opcion > 0 && opcion <= 2));

    if (opcion == 1) {
        limpiar_pantalla();
        iniciar_juego();

    }

    if (opcion == 2) {
        limpiar_pantalla();
        menu_principal();

    }
}

// Muestra la puntuación de ambos jugadores (jugador 1 y 2).
void mostrarPuntajeJugador1y2(){
    printf("\n                              P U N T A J E   J U G A D O R   1:  %d", jugadorActual.puntajeJugador1);
    printf("\n                              P U N T A J E   J U G A D O R   2:  %d", jugadorActual.puntajeJugador2);
}

// Función para guardar el resultado en un archivo
void guardar_resultado() {

    FILE *file = fopen("resultado.txt", "a");

    if (file == NULL) {
        printf("No se pudo abrir el archivo de resultados.\n");
        return;
    }

    fprintf(file, "Usuario: %s\n", jugadorActual.nombre);
    fprintf(file, "Partidas Jugadas: %d\n", jugadorActual.partidasJugadas);
    fprintf(file, "Partidas Ganadas: %d\n", jugadorActual.partidasGanadas);
    fprintf(file, "Partidas Perdidas: %d\n", jugadorActual.partidasPerdidas);
    fprintf(file, "Partidas Empatadas: %d\n", jugadorActual.partidasEmpatadas);
    fprintf(file, "Puntaje Total: %d\n", jugadorActual.puntajeTotal);
    fprintf(file, "Puntaje Jugador 1: %d\n", jugadorActual.puntajeJugador1);
    fprintf(file, "Puntaje Jugador 2: %d\n", jugadorActual.puntajeJugador2);
    fclose(file);

    int i;

    // Actualizar la información del jugador de jugadores
    for( i=0 ; i<cantidadJugadores ; i++ ){
        if( jugadores[i].numUsuario==jugadorActual.numUsuario ){
            jugadores[i] = jugadorActual;
            break;
        }
    }

    guardarUsuarios();  // Guardar usuarios al finalizar el resultado
}





//#########################################################################################
// Funciones de gestión de usuarios
//#########################################################################################

// Registra un nuevo usuario, solicitando sus datos y guardándolos en el sistema.
void registrarUsuario() {

    limpiar_pantalla();

    printf("\n       +---------------------------------------------------------------------------------------------+");
    printf("\n       |                       R E G I S T R A R    U S U A R I O                                    |");
    printf("\n       +---------------------------------------------------------------------------------------------+");

    if( cantidadJugadores>=MAX_USUARIOS ){
        printf("\n       Se ha alcanzado el máximo número de usuarios.\n");
        enter_continuar();
        menu_principal();
    }

    Jugador nuevoJugador;
    nuevoJugador.numUsuario = cantidadJugadores + 1;

    printf("\n\n       Nombre de usuario: ");
    scanf("%s", nuevoJugador.nombre);
    printf("       Contraseña: ");
    scanf("%s", nuevoJugador.contrasena);

    nuevoJugador.partidasJugadas = 0;
    nuevoJugador.partidasGanadas = 0;
    nuevoJugador.partidasPerdidas = 0;
    nuevoJugador.partidasEmpatadas = 0;
    nuevoJugador.puntajeTotal = 0;
    nuevoJugador.puntajeJugador1 = 0;
    nuevoJugador.puntajeJugador2 = 0;

    jugadores[cantidadJugadores] = nuevoJugador;
    cantidadJugadores++;
    guardarUsuarios(); // Guardar usuarios inmediatamente después de registrar uno nuevo

    printf("\n\n       Usuario registrado exitosamente.\n");

    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           1. CONTINUAR                    |");
    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           2. VOLVER                       |");
    printf("\n                             +-------------------------------------------+");

    int opcion;

    do{
        printf("\n\n       [↵] ELIJA UNA OPCION: ");
        scanf("%d", &opcion);

        if (!( opcion>0 && opcion<=2 )) {
            printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
        }
    } while (!( opcion>0 && opcion<=2 ));

    if (opcion == 1) {
        limpiar_pantalla();
        menu_principal();
    } else if( opcion==2 ){
        limpiar_pantalla();
        inicio_programa();
    }
}

// Carga los usuarios registrados desde un archivo o base de datos.
void cargarUsuarios() {
    // Abre el archivo "usuarios.txt" en modo binario de lectura
    FILE *file = fopen("usuarios.txt", "rb");

    if (file == NULL) {
        printf("No se pudo abrir el archivo de usuarios.\n");
        return;
    }

    int i;

    // Lee la cantidad de jugadores desde el archivo
    fread(&cantidadJugadores, sizeof(int), 1, file);

    // Lee los datos de cada jugador desde el archivo
    for( i=0 ; i<cantidadJugadores ; i++ ){
        fread(&jugadores[i], sizeof(Jugador), 1, file);
    }

    fclose(file);
}


// Guarda los usuarios registrados en un archivo o base de datos.
void guardarUsuarios() {
    // Abre el archivo "usuarios.txt" en modo binario de escritura
    FILE *file = fopen("usuarios.txt", "wb");

    // Verifica si el archivo se abrió correctamente
    if( file==NULL ){
        printf("\n       No se pudo abrir el archivo de usuarios.\n");
        return;
    }

    actualizarJugadorActual();  // Asegúrate de que los datos actuales del jugador se actualicen
    fwrite(&cantidadJugadores, sizeof(int), 1, file); // Escribe la cantidad de jugadores en el archivo
    fwrite(jugadores, sizeof(Jugador), cantidadJugadores, file); // Escribe los datos de los jugadores en el archivo
    fclose(file); // Cierra el archivo
}


//Maneja el proceso de inicio de sesión de un usuario solicitando el nombre de usuario y la contraseña
void iniciarSesion() {
    limpiar_pantalla();

    char nombre[MAX_NOMBRE];
    char contrasena[20];
    int encontrado = 0;
    int terminar,i;

    printf("\n       +---------------------------------------------------------------------------------------------+");
    printf("\n       |                              I N I C I A R    S E S I O N                                   |");
    printf("\n       +---------------------------------------------------------------------------------------------+");

    printf("\n\n       Nombre de usuario: ");
    scanf("%s", nombre);
    printf("\n       Contraseña: ");
    scanf("%s", contrasena);

    for( i=0 ; i<cantidadJugadores ; i++ ){
        if( strcmp(jugadores[i].nombre, nombre)==0 && strcmp(jugadores[i].contrasena, contrasena)==0 ){
            jugadorActual = jugadores[i];
            encontrado = 1;
            printf("\n\n                              Inicio de sesión exitoso.");
            printf("\n                              Bienvenido, %s!\n", jugadorActual.nombre);

            printf("\n                             +-------------------------------------------+");
            printf("\n                             |           1. CONTINUAR                    |");
            printf("\n                             +-------------------------------------------+");

            int opcion;

            do{
                printf("\n\n       [↵] ELIJA UNA OPCION: ");
                scanf("%d", &opcion);
                if (!(opcion == 1)) {
                    printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
                }
            } while (!(opcion == 1));

            if (opcion == 1) {
                limpiar_pantalla();
                menu_principal();
            }
        }
    }

    if (!encontrado){
        printf("\n                 Nombre de usuario o contraseña incorrectos.\n");

        printf("\n                             +-------------------------------------------+");
        printf("\n                             |           1. INTENTAR DE NUEVO            |");
        printf("\n                             +-------------------------------------------+");
        printf("\n                             |           2. VOLVER                       |");
        printf("\n                             +-------------------------------------------+");

        int opcion;

        do{
            printf("\n\n       [↵] ELIJA UNA OPCION: ");
            scanf("%d", &opcion);
            if (!(opcion > 0 && opcion <= 2)) {
                printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
            }
        }while(!( opcion>0 && opcion<=2 ));

        if (opcion == 1) {
            limpiar_pantalla();
            iniciarSesion();
        }
        if (opcion == 2) {
            limpiar_pantalla();
            inicio_programa();
        }
    }
}

// Verifica si un nombre de usuario ya existe en la lista de jugadores
int existeUsuario(const char* nombre) {
    int i;

    for( i=0 ; i<cantidadJugadores ; i++ ){
        if(strcmp(jugadores[i].nombre, nombre)==0 ){
            return 1; // El nombre de usuario ya existe
        }
    }
    return 0; // El nombre de usuario no existe
}

// Actualiza la información del jugador actual en la lista de jugadores registrados.
void actualizarJugadorActual() {
    int i;

    for( i=0 ; i<cantidadJugadores ; i++ ){
        if (jugadores[i].numUsuario==jugadorActual.numUsuario) {
            jugadores[i]=jugadorActual;
            break;
        }
    }
}




//#########################################################################################
// Funciones de la opción de Configuraciones
//#########################################################################################

// Muestra el menú de configuraciones, permitiendo al usuario cambiar ajustes del juego o del sistema.
void mostrar_menu_configuracion() {
    limpiar_pantalla();

    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                   C O N F I G U R A C I O N    D E    U S U A R I O                         |");
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                                                                                             |");
    printf("\n         |       ( 1 ) Cambiar nombre de usuario                                                       |");
    printf("\n         |       ( 2 ) Cambiar contraseña de usuario                                                   |");
    printf("\n         |       ( 0 ) Volver al menú principal                                                        |");
    printf("\n         |                                                                                             |");
    printf("\n         +---------------------------------------------------------------------------------------------+");

    printf("\n         +------------------+-------------------------------------------------------------------------+");
    printf("\n            USUARIO ACTUAL  |  %s ",jugadorActual.nombre);
    printf("\n         +------------------+-------------------------------------------------------------------------+");

    int opcion;

    do{
        printf("\n\n       [↵] ELIJA UNA OPCION: ");
        scanf("%d", &opcion);

        if (!( opcion>=0 && opcion<=2)) {
            printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
        }
    } while (!( opcion>=0 && opcion<3));


    switch (opcion) {
        case 1:
            cambiar_nombre_de_usuario();
            break;
        case 2:
            cambiar_contrasena();
            break;
        case 0:
            limpiar_pantalla();
            menu_principal();
            break;
    }
}

// Permite al usuario cambiar su nombre de usuario, actualizando la información correspondiente.
void cambiar_nombre_de_usuario() {

    limpiar_pantalla();

    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                   C O N F I G U R A C I O N    D E    U S U A R I O                         |");
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |       ( 1 ) Cambiar nombre de usuario                                                       |");
    printf("\n         +---------------------------------------------------------------------------------------------+\n");

    printf("\n         +---------------------+----------------------------------------------------------------------+");
    printf("\n            NOMBRE DE USUARIO  |  %s ", jugadorActual.nombre);
    printf("\n         +---------------------+----------------------------------------------------------------------+");

    char nuevoNombre[MAX_NOMBRE];
    int i;

    printf("\n         Ingrese el nuevo nombre de usuario: ");
    scanf("%s", nuevoNombre);

    // Verifica si el nuevo nombre de usuario ya existe
    if (existeUsuario(nuevoNombre)) {
        printf("\n         El nombre de usuario ya está en uso.\n         Intente con otro nombre.\n");
        return;
    }

    // Cambia el nombre de usuario
    strcpy(jugadorActual.nombre, nuevoNombre);

    // Actualiza la información del usuario en el de jugadores
    actualizarJugadorActual();

    // Guarda los cambios en el archivo de usuarios
    guardarUsuarios();

    printf("\n         Nombre de usuario cambiado exitosamente.\n");

    printf("\n         +---------------------+----------------------------------------------------------------------+");
    printf("\n            NOMBRE ACTUAL      |  %s ", jugadorActual.nombre);
    printf("\n         +---------------------+----------------------------------------------------------------------+");

    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           1. VOLVER                       |");
    printf("\n                             +-------------------------------------------+");

    int opc;

    do{
        printf("\n\n       [↵] ELIJA UNA OPCION: ");
        scanf("%d", &opc);

        if (!(opc > 0 && opc < 2)) {
            printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
        }
    } while (!(opc > 0 && opc < 2));

    if (opc == 1) {
        limpiar_pantalla();
        mostrar_menu_configuracion();
    }
}

// Permite al usuario cambiar su contraseña, asegurando la seguridad de su cuenta.
void cambiar_contrasena() {

    limpiar_pantalla();

    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                   C O N F I G U R A C I O N    D E    U S U A R I O                         |");
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |       ( 2 ) Cambiar contraseña                                                              |");
    printf("\n         +---------------------------------------------------------------------------------------------+");

    printf("\n         +---------------------+----------------------------------------------------------------------+");
    printf("\n            NOMBRE DE USUARIO  |  %s ", jugadorActual.nombre);
    printf("\n         +---------------------+----------------------------------------------------------------------+");

    char nuevaContrasena[20];

    printf("\n         Ingrese la nueva contraseña: ");
    scanf("%s", nuevaContrasena);

    // Cambia la contraseña
    strcpy(jugadorActual.contrasena, nuevaContrasena);

    // Actualiza la información del usuario de jugadores
    actualizarJugadorActual();

    // Guarda los cambios en el archivo de usuarios
    guardarUsuarios();

    printf("\n         Contraseña cambiada exitosamente.\n");

    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           1. VOLVER                       |");
    printf("\n                             +-------------------------------------------+");

    int opc;

    do{
        printf("\n\n       [↵] ELIJA UNA OPCION: ");
        scanf("%d", &opc);
        if (!( opc>0 && opc<2 )){
            printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
        }
    } while (!( opc>0 && opc<2 ));

    if( opc==1 ){
        limpiar_pantalla();
        mostrar_menu_configuracion();
    }
}





//#########################################################################################
// Funciones de la opción de registro de jugador
//#########################################################################################

// Muestra el menú de configuraciones, permitiendo al usuario cambiar ajustes del juego o del sistema.
void mostrar_menu_registro_jugador() {
    limpiar_pantalla();

    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                     R E G I S T R A R    DE    J U G A D O R E S                            |");
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                                                                                             |");
    printf("\n         |       ( 1 ) Registrar nuevo jugador                                                         |");
    printf("\n         |       ( 2 ) Lista de jugadores                                                              |");
    printf("\n         |       ( 0 ) Volver al menú principal                                                        |");
    printf("\n         |                                                                                             |");
    printf("\n         +---------------------------------------------------------------------------------------------+");

    int opcion;

    do{
        printf("\n\n       [↵] ELIJA UNA OPCION: ");
        scanf("%d", &opcion);
        if (!( opcion>=0 && opcion<=2 )) {
            printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
        }
    } while (!( opcion>=0 && opcion<3 ));

    switch (opcion) {
        case 1:
            resgistro_jugador_mostrar_menu_registro_jugador();
            break;
        case 2:
            lista_jugadores_mostrar_menu_registro_jugador();
            break;
        case 0:
            limpiar_pantalla();
            menu_principal();
            break;
    }
}

// Permite registrar un nuevo jugador desde el menú de registro de jugadores.
void resgistro_jugador_mostrar_menu_registro_jugador(){

    limpiar_pantalla();

    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                     R E G I S T R A R    DE    J U G A D O R E S                            |");
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |       ( 1 ) Registrar nuevo jugador                                                         |");
    printf("\n         +---------------------------------------------------------------------------------------------+\n\n");

    if( cantidadJugadores>=MAX_USUARIOS ){
        printf("\nSe ha alcanzado el máximo número de usuarios.\n");
        return;
    }

    Jugador nuevoJugador;
    nuevoJugador.numUsuario = cantidadJugadores + 1;

    printf("\n\n       Nombre de usuario: ");
    scanf("%s", nuevoJugador.nombre);
    printf("       Contraseña: ");
    scanf("%s", nuevoJugador.contrasena);

    nuevoJugador.partidasJugadas = 0;
    nuevoJugador.partidasGanadas = 0;
    nuevoJugador.partidasPerdidas = 0;
    nuevoJugador.partidasEmpatadas = 0;
    nuevoJugador.puntajeTotal = 0;
    nuevoJugador.puntajeJugador1 = 0;
    nuevoJugador.puntajeJugador2 = 0;

    jugadores[cantidadJugadores] = nuevoJugador;
    cantidadJugadores++;
    guardarUsuarios(); // Guardar usuarios inmediatamente después de registrar uno nuevo

    printf("\n\n       Usuario registrado exitosamente.\n");

    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           1. INICIAR SESIÓN               |");
    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           2. VOLVER                       |");
    printf("\n                             +-------------------------------------------+");

    int opcion;
    do{
        printf("\n\n       [↵] ELIJA UNA OPCION: ");
        scanf("%d", &opcion);

        if (!( opcion>0 && opcion<=2 )) {
            printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
        }
    } while (!( opcion>0 && opcion<=2 ));

    if (opcion == 1) {
        limpiar_pantalla();
        iniciarSesion();
    }

    if (opcion == 2) {
        limpiar_pantalla();
        mostrar_menu_registro_jugador();
    }
}

// Muestra la lista de jugadores registrados en el menú de registro de jugadores.
void lista_jugadores_mostrar_menu_registro_jugador(){
    limpiar_pantalla();
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                     R E G I S T R A R    DE    J U G A D O R E S                            |");
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |       ( 2 ) Lista de jugadores                                                              |");
    printf("\n         +---------------------------------------------------------------------------------------------+\n\n");
    printf("\n         +----+----------------------------------------------------------------------------------------+");
    printf("\n         | N° | NOMBRE DE USUARIO                                                                      |");
    printf("\n         +----+----------------------------------------------------------------------------------------+");

    int i,opc;

    for( i=0 ; i<cantidadJugadores ; i++ ){
        printf("\n           %02d | %s \n",i+1, jugadores[i].nombre);
        printf("         +----+----------------------------------------------------------------------------------------+");

    }

    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           1. VOLVER                       |");
    printf("\n                             +-------------------------------------------+");

    do{
        printf("\n\n       [↵] ELIJA UNA OPCION: ");
        scanf("%d", &opc);

        if (!(opc > 0 && opc < 2)) {
            printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
        }
    } while (!(opc > 0 && opc < 2));

    if (opc == 1) {
        mostrar_menu_registro_jugador();
    }
}





//#########################################################################################
// Funciones de la opción de estadística
//#########################################################################################

// Muestra las estadísticas generales de los jugadores y partidas.
void mostrar_estadistica(){
    limpiar_pantalla();
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                                  E S T A D I S T I C A S                                    |");
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                                                                                             |");
    printf("\n         |       ( 1 ) Mayores puntajes                                                                |");
    printf("\n         |       ( 2 ) Estadistica del usuario                                                         |");
    printf("\n         |       ( 0 ) Volver al menú principal                                                        |");
    printf("\n         |                                                                                             |");
    printf("\n         +---------------------------------------------------------------------------------------------+");

    int opcion;

    do{
        printf("\n\n       [↵] ELIJA UNA OPCION: ");
        scanf("%d", &opcion);

        if (!( opcion>=0 && opcion<=2 )) {
            printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
        }
    } while (!( opcion>=0 && opcion<3 ));

    switch (opcion) {
        case 1:
            mayor_puntaje();
            break;
        case 2:
            estadistica_de_usuario();
            break;
        case 0:
            limpiar_pantalla();
            menu_principal();
            break;
    }
} // fin mostrar_estadistica

// Muestra el mayor puntaje alcanzado por los jugadores.
void mayor_puntaje() {
    limpiar_pantalla();

    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                                  E S T A D I S T I C A S                                    |");
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |       ( 1 ) Mayores puntajes                                                                |");
    printf("\n         +---------------------------------------------------------------------------------------------+\n\n\n");

    FILE *file = fopen("puntajes.txt", "w");// Abre el archivo "puntajes.txt" para escribir.
    // Verifica si el archivo se abrió correctamente.
    if (file == NULL) {
        printf("No se pudo abrir el archivo de puntajes.\n");
        return;
    }

    Puntaje puntajes[MAX_USUARIOS];// Declara estructuras Puntaje para almacenar los puntajes de los jugadores.

    int cont,i,j,opc;
    cont= 0;

    // Copiar los puntajes de los jugadores a la estructura Puntaje
    for( i=0 ; i<cantidadJugadores ; i++ ){
        strcpy(puntajes[cont].nombre, jugadores[i].nombre);
        puntajes[cont].puntaje = jugadores[i].puntajeTotal;
        cont++;
    }

    // Ordenar los puntajes de mayor a menor
    for( i=0 ; i<cont-1 ; i++ ){
        for( j=i+1 ; j<cont ; j++ ){
            if (puntajes[i].puntaje < puntajes[j].puntaje) {
                Puntaje aux = puntajes[i];// Intercambia los puntajes si es necesario.
                puntajes[i] = puntajes[j];
                puntajes[j] = aux;
            }
        }
    }

    // Guardar los puntajes ordenados en el archivo
    for( i=0 ; i<cont ; i++ ){
        fprintf(file, "%s %d\n", puntajes[i].nombre, puntajes[i].puntaje);
    }
    fclose(file);// Cierra el archivo.

    // Mostrar los puntajes
    printf("\n         +-----+--------------------------------+------------------------------------------------------+");
    printf("\n         |  N° |      NOMBRE DE USUARIO         |    PUNTOS                                            |");
    printf("\n         +-----+--------------------------------+------------------------------------------------------+");

    for( i=0 ; i<cont ; i++ ){
        printf("\n           %2d  | %-30s | %6d                                               ", i + 1, puntajes[i].nombre, puntajes[i].puntaje);
        printf("\n         +-----+--------------------------------+------------------------------------------------------+");
    }

    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           1. VOLVER                       |");
    printf("\n                             +-------------------------------------------+");

    do{
        printf("\n\n       [↵] ELIJA UNA OPCION: ");
        scanf("%d", &opc);

        if (!(opc > 0 && opc < 2)) {
            printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
        }
    } while (!(opc>0 && opc<2));

    if (opc == 1) {
        limpiar_pantalla();
        mostrar_estadistica();
    }
}// fin mayor_puntaje()

// Muestra las estadísticas específicas del usuario actual.
void estadistica_de_usuario(){
    limpiar_pantalla();
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                                  E S T A D I S T I C A S                                    |");
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |       ( 2 ) Estadistica de los usuarios                                                     |");
    printf("\n         +---------------------------------------------------------------------------------------------+\n\n\n");

    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n           Nombre de usuario :  %s ", jugadorActual.nombre);
    printf("\n         +---------------------------------------------------------------------------------------------+\n");
    printf("\n           Partidas Jugadas  : %d", jugadorActual.partidasJugadas);
    printf("\n           Partidas Ganadas  : %d", jugadorActual.partidasGanadas);
    printf("\n           Partidas Perdidas : %d", jugadorActual.partidasPerdidas);
    printf("\n           Puntaje Jugador 2 : %d", jugadorActual.puntajeJugador2);
    printf("\n           Puntaje Total     : %d", jugadorActual.puntajeTotal);
    printf("\n\n         +---------------------------------------------------------------------------------------------+\n\n");

    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           1. VOLVER                       |");
    printf("\n                             +-------------------------------------------+");

    int opc;

    do{
        printf("\n\n       [↵] ELIJA UNA OPCION: ");
        scanf("%d", &opc);

        if (!(opc > 0 && opc < 2)) {
            printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
        }
    }while(!( opc>0 && opc<2 ));

    if( opc==1 ) {
        mostrar_estadistica();
    }
}// fin estadistica_de_usuario





//#########################################################################################
// Funciones de la opción reglas del juego
//#########################################################################################

// Muestra las reglas del juego, explicando cómo jugar y las condiciones de victoria.
void regla_juego() {
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                        R E G L A S     D E L    J U E G O                                   |");
    printf("\n         +---------------------------------------------------------------------------------------------+");
    printf("\n         |                                                                                             |");
    printf("\n         | 1. El objetivo del juego es descubrir todas las celdas que no contienen minas.              |");
    printf("\n         |                                                                                             |");
    printf("\n         | 2. El juego se juega en turnos alternos entre el jugador (1) y la computadora (2)           |");
    printf("\n         |                                                                                             |");
    printf("\n         | 3. Si descubres una celda con una mina, pierdes el juego.                                   |");
    printf("\n         |                                                                                             |");
    printf("\n         | 4. Las celdas descubiertas muestran un número que indica cuántas minas hay en las           |");
    printf("\n         |    celdas adyacentes.                                                                       |");
    printf("\n         |                                                                                             |");
    printf("\n         | 5. Puedes marcar las celdas donde crees que hay minas con una bandera.                      |");
    printf("\n         |                                                                                             |");
    printf("\n         | 6. El juego termina cuando se descubren todas las celdas sin minas o cuando se descubre     |");
    printf("\n         |    una mina.                                                                                |");
    printf("\n         |                                                                                             |");
    printf("\n         | 7. En el turno de la computadora, se indicará la posición de la jugada realizada.           |");
    printf("\n         |                                                                                             |");
    printf("\n         | 8. Si el jugador gana, se mostrará un mensaje de victoria junto con la puntuación obtenida. |");
    printf("\n         |                                                                                             |");
    printf("\n         | 9. La celda seleccionada por el jugador se muestra con el valor '1', mientras que las       |");
    printf("\n         |    celdas no descubiertas permanecen ocultas o con su valor original.                       |");
    printf("\n         |                                                                                             |");
    printf("\n         +---------------------------------------------------------------------------------------------+");

    printf("\n                             +-------------------------------------------+");
    printf("\n                             |           1. VOLVER                       |");
    printf("\n                             +-------------------------------------------+");

    int opc;

    do{
        printf("\n\n       [↵] ELIJA UNA OPCION: ");
        scanf("%d", &opc);

        if (!( opc>0 && opc<2 )){
            printf("       [x] ERROR, LA OPCION INGRESADA NO ES VALIDA\n");
        }
    } while (!( opc>0 && opc<2 ));

    if( opc==1 ){
        limpiar_pantalla();
        menu_principal();
    }

}





//#########################################################################################
// Funciones globales que ayudan al programa
//#########################################################################################

// Configura la consola para utilizar UTF-8, asegurando la correcta visualización de caracteres especiales.
void setConsoleUtf8() {
    #ifdef _WIN32
        system("chcp 65001");
    #endif
}

// Espera a que el usuario presione Enter para continuar, pausando la ejecución temporalmente.
void enter_continuar() {
    printf("\n\n   [↵] PRESIONE ENTER PARA CONTINUAR.\n");
    while (getchar() != '\n');
    limpiar_pantalla();
}

// Limpia la pantalla de la consola, preparando para mostrar nueva información.
void limpiar_pantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}





