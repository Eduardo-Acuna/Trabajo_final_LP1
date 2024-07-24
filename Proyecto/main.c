#include "head.h"


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

