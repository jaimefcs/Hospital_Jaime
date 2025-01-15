#ifndef MEDICO_H
#define MEDICO_H

#include <string>

class Medico {
public:
    static void inicializarArchivo();
    static void registrar();
    static int buscar();
private:
    static int generarId(const std::string& archivo);
    static bool validarDatos(const std::string& nombre, const std::string& dni);
};

#endif
