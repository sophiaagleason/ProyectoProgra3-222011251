# Bitácora — <matrícula>

<!-- Una entrada por sesión de trabajo. -->

## AAAA-MM-DD, HH:MM–HH:MM
- Qué hice:
- Qué falló o me confundió:
- Qué consulté (URL exacta, libro y página, o nombre del profesor):
- Commit(s):

## [2026-10-15]
- Clonación del proyecto, configuración del entorno, manejo de GitHub y modificación de perfiles.
- Inclusión forzada del archivo de carga grande.
- Creación e implementación inicial de la Tabla Hash, junto con la integración de los comandos `INSERT` y `GET` en el Motor.

## [2026-10-17]
- Implementación de la eliminación de registros mediante el comando `DELETE` con liberación de memoria.

## [2026-10-20]
- Finalización de la lógica para `UPDATE` y corrección de errores de sincronización y memoria detectados.

## [2026-10-26]
- Inicio del diseño del Árbol AVL para el índice ordenado.

## [2026-11-03]
- Implementación de la estructura base del Árbol AVL (`AVL.h` y `AVL.cpp`).
- Refactorización de detalles en la clase `AVL` e integración con `Motor.h` y `Motor.cpp`.
- Pruebas de integración del árbol AVL con consultas en el REPL.
- Resolución de problemas de sintaxis y firma modular en la ejecución del comando `RANGE`.
