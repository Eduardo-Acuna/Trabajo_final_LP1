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
