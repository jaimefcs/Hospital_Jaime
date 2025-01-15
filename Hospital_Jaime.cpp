#include <iostream>
#include "Medico.h"
#include "Paciente.h"
#include "Cita.h"

void menuPrincipal();

int main() {
    // Inicializamos los archivos al iniciar el programa
    Medico::inicializarArchivo();
    Paciente::inicializarArchivo();
    Cita::inicializarArchivo();

    // Mostramos el menú principal
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    int opcion;
    do {
        std::cout << "\n--- Menú Principal ---\n";
        std::cout << "1. Registrar Médico\n";
        std::cout << "2. Buscar Médico\n";
        std::cout << "3. Registrar Paciente\n";
        std::cout << "4. Buscar Paciente\n";
        std::cout << "5. Asignar Cita\n";
        std::cout << "6. Buscar Cita\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(); // Ignoramos el salto de línea después de ingresar un número

        switch (opcion) {
        case 1:
            Medico::registrar();
            break;
        case 2: {
            int id = Medico::buscar();
            if (id != -1) {
                std::cout << "ID del médico encontrado: " << id << std::endl;
            }
            break;
        }
        case 3:
            Paciente::registrar();
            break;
        case 4: {
            int id = Paciente::buscar();
            if (id != -1) {
                std::cout << "ID del paciente encontrado: " << id << std::endl;
            }
            break;
        }
        case 5:
            Cita::asignar();
            break;
        case 6: {
            int id = Cita::buscar();
            if (id != -1) {
                std::cout << "ID de la cita encontrada: " << id << std::endl;
            }
            break;
        }
        case 0:
            std::cout << "Saliendo del programa...\n";
            break;
        default:
            std::cout << "Opción inválida. Intente nuevamente.\n";
        }
    } while (opcion != 0);
}
