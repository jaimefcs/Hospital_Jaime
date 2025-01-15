#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>

class Paciente {
public:
    static void inicializarArchivo();
    static void registrar();
    static int buscar();
    static void modificar(int id);
private:
    static int generarId(const std::string& archivo);
    static bool validarDatos(const std::string& nombre, const std::string& dni);
};

#endif
