﻿# CMakeList.txt: proyecto de CMake para Hospital_Jaime, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

# Habilite Recarga activa para los compiladores de MSVC si se admiten.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Hospital_Jaime")

# Agregue un origen al ejecutable de este proyecto.
add_executable (Hospital_Jaime "Hospital_Jaime.cpp" "Hospital_Jaime.h" "Medico.cpp" "Medico.h" "Paciente.cpp" "Paciente.h" "Cita.h" "Cita.cpp" "Reporte.h" "Reporte.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Hospital_Jaime PROPERTY CXX_STANDARD 20)
endif()

# TODO: Agregue pruebas y destinos de instalación si es necesario.
