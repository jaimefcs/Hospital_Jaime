#include <iostream>
#include "Medico.h"
#include "Paciente.h"
#include "Cita.h"
#include "Reporte.h"

void menuPrincipal();

int main() {
    // Inicializamos los archivos de médicos, pacientes y citas al inicio
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
        std::cout << "3. Modificar Médico\n";
        std::cout << "4. Registrar Paciente\n";
        std::cout << "5. Buscar Paciente\n";
        std::cout << "6. Modificar Paciente\n";
        std::cout << "7. Asignar Cita\n";
        std::cout << "8. Buscar Cita\n";
        std::cout << "9. Reportes\n";  // NUEVA OPCIÓN: REPORTES
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore(); // Ignorar el salto de línea después de ingresar un número

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
        case 3: {
            int id;
            std::cout << "Ingrese el ID del médico a modificar: ";
            std::cin >> id;
            std::cin.ignore();
            Medico::modificar(id);
            break;
        }
        case 4:
            Paciente::registrar();
            break;
        case 5: {
            int id = Paciente::buscar();
            if (id != -1) {
                std::cout << "ID del paciente encontrado: " << id << std::endl;
            }
            break;
        }
        case 6: {
            int id;
            std::cout << "Ingrese el ID del paciente a modificar: ";
            std::cin >> id;
            std::cin.ignore();
            Paciente::modificar(id);
            break;
        }
        case 7:
            Cita::asignar();
            break;
        case 8: {
            int id = Cita::buscar();
            if (id != -1) {
                std::cout << "ID de la cita encontrada: " << id << std::endl;
            }
            break;
        }
        case 9: {
            Reporte::menuReportes();
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
