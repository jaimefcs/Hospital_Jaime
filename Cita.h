#ifndef CITA_H
#define CITA_H

#include <string>

class Cita {
public:
    static void inicializarArchivo();
    static void asignar();
    static int buscar();
private:
    static int generarId(const std::string& archivo);
    static bool validarDatos(int pacienteId, int medicoId, const std::string& fecha);
};

#endif
