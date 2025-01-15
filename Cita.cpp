#include "Cita.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Cita::inicializarArchivo() {
    std::ofstream archivo("citas.csv", std::ios::app);
    if (archivo.tellp() == 0) {
        archivo << "id,paciente_id,medico_id,fecha\n"; // Cabecera del archivo
    }
    archivo.close();
}

void Cita::asignar() {
    std::ofstream archivo("citas.csv", std::ios::app);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de citas." << std::endl;
        return;
    }

    int pacienteId, medicoId;
    std::string fecha;

    std::cout << "Ingrese el ID del paciente: ";
    std::cin >> pacienteId;

    std::cout << "Ingrese el ID del médico: ";
    std::cin >> medicoId;

    std::cout << "Ingrese la fecha de la cita (YYYY-MM-DD): ";
    std::cin >> fecha;

    if (!validarDatos(fecha, pacienteId, medicoId)) {
        std::cerr << "Datos inválidos. Intente nuevamente." << std::endl;
        return;
    }

    int id = generarId("citas.csv");
    archivo << id << "," << pacienteId << "," << medicoId << "," << fecha << "\n";
    archivo.close();

    std::cout << "Cita asignada correctamente con ID " << id << "." << std::endl;
}

int Cita::buscar() {
    std::ifstream archivo("citas.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de citas." << std::endl;
        return -1;
    }

    std::string criterio;
    std::cout << "Ingrese el ID del paciente, médico o la fecha de la cita a buscar: ";
    std::cin.ignore(); // Ignora el salto de línea previo
    std::getline(std::cin, criterio);

    std::string linea;
    bool encontrado = false;
    int citaId = -1;

    while (std::getline(archivo, linea)) {
        if (linea.empty() || linea.find("id") == 0) {
            continue; // Ignora la cabecera
        }

        if (linea.find(criterio) != std::string::npos) {
            std::cout << "Cita encontrada: " << linea << std::endl;
            std::stringstream ss(linea);
            std::string idStr;
            std::getline(ss, idStr, ',');
            citaId = std::stoi(idStr);
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron citas con el criterio dado." << std::endl;
    }

    archivo.close();
    return citaId;
}

int Cita::generarId(const std::string& archivo) {
    std::ifstream entrada(archivo);
    std::string linea;
    int ultimoId = 0;

    while (std::getline(entrada, linea)) {
        if (linea.empty() || linea.find("id") == 0) {
            continue; // Ignora la cabecera
        }

        std::stringstream ss(linea);
        std::string id;
        std::getline(ss, id, ',');
        if (!id.empty()) {
            ultimoId = std::stoi(id);
        }
    }

    return ultimoId + 1;
}

bool Cita::validarDatos(const std::string& fecha, int pacienteId, int medicoId) {
    return !fecha.empty() && pacienteId > 0 && medicoId > 0;
}
