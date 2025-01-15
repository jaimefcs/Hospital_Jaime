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
        std::cerr << "Datos inv�lidos. Intente nuevamente." << std::endl;
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

void Paciente::modificar(int id) {
    std::ifstream archivoEntrada("pacientes.csv");
    if (!archivoEntrada) {
        std::cerr << "Error al abrir el archivo de pacientes." << std::endl;
        return;
    }

    std::ofstream archivoSalida("pacientes_temp.csv");
    if (!archivoSalida) {
        std::cerr << "Error al crear el archivo temporal." << std::endl;
        return;
    }

    std::string linea;
    bool encontrado = false;

    while (std::getline(archivoEntrada, linea)) {
        std::stringstream ss(linea);
        std::string idStr;
        std::getline(ss, idStr, ',');

        if (idStr == std::to_string(id)) {
            encontrado = true;
            std::string nombre, dni;

            std::cout << "Ingrese el nuevo nombre del paciente: ";
            std::getline(std::cin, nombre);

            std::cout << "Ingrese el nuevo DNI del paciente: ";
            std::getline(std::cin, dni);

            if (!validarDatos(nombre, dni)) {
                std::cerr << "Datos inv�lidos. No se realizaron cambios." << std::endl;
                return;
            }

            archivoSalida << id << "," << nombre << "," << dni << "\n";
        }
        else {
            archivoSalida << linea << "\n";
        }
    }

    archivoEntrada.close();
    archivoSalida.close();

    if (encontrado) {
        std::remove("pacientes.csv");
        std::rename("pacientes_temp.csv", "pacientes.csv");
        std::cout << "Paciente modificado correctamente." << std::endl;
    }
    else {
        std::remove("pacientes_temp.csv");
        std::cerr << "Paciente no encontrado." << std::endl;
    }
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
