#include "Paciente.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Paciente::inicializarArchivo() {
    std::ofstream archivo("pacientes.csv", std::ios::app);
    if (archivo.tellp() == 0) {
        archivo << "id,nombre,dni\n"; // Cabecera del archivo
    }
    archivo.close();
}

void Paciente::registrar() {
    std::ofstream archivo("pacientes.csv", std::ios::app);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de pacientes." << std::endl;
        return;
    }

    std::string nombre, dni;

    std::cout << "Ingrese el nombre del paciente: ";
    std::getline(std::cin, nombre);

    std::cout << "Ingrese el DNI del paciente: ";
    std::getline(std::cin, dni);

    if (!validarDatos(nombre, dni)) {
        std::cerr << "Datos inválidos. Intente nuevamente." << std::endl;
        return;
    }

    int id = generarId("pacientes.csv");
    archivo << id << "," << nombre << "," << dni << "\n";
    archivo.close();

    std::cout << "Paciente registrado correctamente con ID " << id << "." << std::endl;
}

int Paciente::buscar() {
    std::ifstream archivo("pacientes.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de pacientes." << std::endl;
        return -1;
    }

    std::string criterio;
    std::cout << "Ingrese el DNI o nombre del paciente a buscar: ";
    std::getline(std::cin, criterio);

    std::string linea;
    bool encontrado = false;
    int pacienteId = -1;

    while (std::getline(archivo, linea)) {
        if (linea.empty() || linea.find("id") == 0) {
            continue; // Ignora la cabecera
        }

        if (linea.find(criterio) != std::string::npos) {
            std::cout << "Paciente encontrado: " << linea << std::endl;
            std::stringstream ss(linea);
            std::string idStr;
            std::getline(ss, idStr, ',');
            pacienteId = std::stoi(idStr);
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron pacientes con el criterio dado." << std::endl;
    }

    archivo.close();
    return pacienteId;
}

int Paciente::generarId(const std::string& archivo) {
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

bool Paciente::validarDatos(const std::string& nombre, const std::string& dni) {
    return !nombre.empty() && !dni.empty();
}
