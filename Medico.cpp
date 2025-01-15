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
        std::cerr << "Error al abrir el archivo de m�dicos." << std::endl;
        return;
    }

    std::string nombre, dni;

    std::cout << "Ingrese el nombre del m�dico: ";
    std::getline(std::cin, nombre);

    std::cout << "Ingrese el DNI del m�dico: ";
    std::getline(std::cin, dni);

    if (!validarDatos(nombre, dni)) {
        std::cerr << "Datos inv�lidos. Intente nuevamente." << std::endl;
        return;
    }

    int id = generarId("medicos.csv");
    archivo << id << "," << nombre << "," << dni << "\n";
    archivo.close();

    std::cout << "M�dico registrado correctamente con ID " << id << "." << std::endl;
}

int Medico::buscar() {
    std::ifstream archivo("medicos.csv");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo de m�dicos." << std::endl;
        return -1;
    }

    std::string criterio;
    std::cout << "Ingrese el DNI o nombre del m�dico a buscar: ";
    std::getline(std::cin, criterio);

    std::string linea;
    bool encontrado = false;
    int medicoId = -1;

    while (std::getline(archivo, linea)) {
        if (linea.empty() || linea.find("id") == 0) {
            continue; // Ignora la cabecera
        }

        if (linea.find(criterio) != std::string::npos) {
            std::cout << "M�dico encontrado: " << linea << std::endl;
            std::stringstream ss(linea);
            std::string idStr;
            std::getline(ss, idStr, ',');
            medicoId = std::stoi(idStr);
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron m�dicos con el criterio dado." << std::endl;
    }

    archivo.close();
    return medicoId;
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
