# include "head.h"

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
    //limpiar_pantalla();
}

// Limpia la pantalla de la consola, preparando para mostrar nueva información.
void limpiar_pantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

