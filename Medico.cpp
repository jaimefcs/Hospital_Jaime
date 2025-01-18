#include "Medico.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Medico::inicializarArchivo() {
    std::ofstream archivo("medicos.csv", std::ios::app);
    if (archivo.tellp() == 0) {
        archivo << "id,nombre,dni\n"; // Cabecera del archivo
    }
    archivo.close();
}

void Medico::registrar() {
    std::ofstream archivo("medicos.csv", std::ios::app);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de médicos." << std::endl;
        return;
    }

    std::string nombre, dni;

    std::cout << "Ingrese el nombre del médico: ";
    std::getline(std::cin, nombre);

    std::cout << "Ingrese el DNI del médico: ";
    std::getline(std::cin, dni);

    if (!validarDatos(nombre, dni)) {
        std::cerr << "Datos inválidos. Intente nuevamente." << std::endl;
        return;
    }

    int id = generarId("medicos.csv");
    archivo << id << "," << nombre << "," << dni << "\n";
    archivo.close();

    std::cout << "Médico registrado correctamente con ID " << id << "." << std::endl;
}

int Medico::buscar() {
    std::ifstream archivo("medicos.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de médicos." << std::endl;
        return -1;
    }

    std::string criterio;
    std::cout << "Ingrese el DNI o nombre del médico a buscar: ";
    std::getline(std::cin, criterio);

    std::string linea;
    bool encontrado = false;
    int medicoId = -1;

    while (std::getline(archivo, linea)) {
        if (linea.empty() || linea.find("id") == 0) {
            continue; // Ignora la cabecera
        }

        if (linea.find(criterio) != std::string::npos) {
            std::cout << "Médico encontrado: " << linea << std::endl;
            std::stringstream ss(linea);
            std::string idStr;
            std::getline(ss, idStr, ',');
            medicoId = std::stoi(idStr);
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron médicos con el criterio dado." << std::endl;
    }

    archivo.close();
    return medicoId;
}

void Medico::modificar(int id) {
    std::ifstream archivoEntrada("medicos.csv");
    if (!archivoEntrada) {
        std::cerr << "Error al abrir el archivo de médicos." << std::endl;
        return;
    }

    std::ofstream archivoSalida("medicos_temp.csv");
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

            std::cout << "Ingrese el nuevo nombre del médico: ";
            std::getline(std::cin, nombre);

            std::cout << "Ingrese el nuevo DNI del médico: ";
            std::getline(std::cin, dni);

            if (!validarDatos(nombre, dni)) {
                std::cerr << "Datos inválidos. No se realizaron cambios." << std::endl;
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
        std::remove("medicos.csv");
        std::rename("medicos_temp.csv", "medicos.csv");
        std::cout << "Médico modificado correctamente." << std::endl;
    }
    else {
        std::remove("medicos_temp.csv");
        std::cerr << "Médico no encontrado." << std::endl;
    }
}

int Medico::generarId(const std::string& archivo) {
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

bool Medico::validarDatos(const std::string& nombre, const std::string& dni) {
    return !nombre.empty() && !dni.empty();
}
