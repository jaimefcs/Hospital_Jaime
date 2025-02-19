#include "Reporte.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

void Reporte::menuReportes() {
    int opcion;
    do {
        std::cout << "\n--- Menú Reportes ---\n";
        std::cout << "1. Mostrar todas las citas\n";
        std::cout << "2. Mostrar citas por médico\n";
        std::cout << "0. Volver al Menú Principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            reporteTodasLasCitas();
            break;
        case 2:
            reporteCitasPorMedico();
            break;
        case 0:
            std::cout << "Volviendo al Menú Principal...\n";
            break;
        default:
            std::cout << "Opción inválida. Intente nuevamente.\n";
        }
    } while (opcion != 0);
}

void Reporte::reporteTodasLasCitas() {
    std::ifstream archivoCitas("citas.csv");
    if (!archivoCitas) {
        std::cerr << "Error al abrir el archivo de citas.\n";
        return;
    }

    std::string linea;
    std::cout << "\n--- Reporte de Todas las Citas ---\n";
    bool hayCitas = false;

    while (std::getline(archivoCitas, linea)) {
        if (linea.find("id_cita") == 0) continue; // Ignorar la cabecera
        std::cout << linea << "\n";
        hayCitas = true;
    }

    if (!hayCitas) {
        std::cout << "No hay citas registradas.\n";
    }

    archivoCitas.close();
}

void Reporte::reporteCitasPorMedico() {
    std::ifstream archivoCitas("citas.csv");
    std::ifstream archivoMedicos("medicos.csv");

    if (!archivoCitas || !archivoMedicos) {
        std::cerr << "Error al abrir los archivos necesarios.\n";
        return;
    }

    std::map<int, std::string> medicos;  // ID del médico -> Nombre del médico
    std::map<int, std::vector<std::string>> citasPorMedico;

    std::string linea;

    // Leer médicos
    while (std::getline(archivoMedicos, linea)) {
        if (linea.find("id") == 0) continue; // Ignorar la cabecera
        std::stringstream ss(linea);
        std::string idStr, nombre;
        std::getline(ss, idStr, ',');
        std::getline(ss, nombre, ',');
        medicos[std::stoi(idStr)] = nombre;
    }

    // Leer citas
    while (std::getline(archivoCitas, linea)) {
        if (linea.find("id_cita") == 0) continue; // Ignorar la cabecera
        std::stringstream ss(linea);
        std::string idCita, pacienteId, medicoId, fecha, urgencia;
        std::getline(ss, idCita, ',');
        std::getline(ss, pacienteId, ',');
        std::getline(ss, medicoId, ',');
        std::getline(ss, fecha, ',');
        std::getline(ss, urgencia);

        int idMedico = std::stoi(medicoId);
        std::string citaInfo = "ID Cita: " + idCita + ", Paciente ID: " + pacienteId + ", Fecha: " + fecha + ", Urgencia: " + urgencia;
        citasPorMedico[idMedico].push_back(citaInfo);
    }

    archivoCitas.close();
    archivoMedicos.close();

    std::cout << "\n--- Reporte de Citas por Médico ---\n";
    for (const auto& [idMedico, citas] : citasPorMedico) {
        std::cout << "Médico: " << medicos[idMedico] << " (ID: " << idMedico << ")\n";
        for (const auto& cita : citas) {
            std::cout << "  " << cita << "\n";
        }
        std::cout << "\n";
    }
}
