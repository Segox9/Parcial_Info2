#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct ID{
    uint16_t ID_sup; //ID del equipo superior al que esta concectado
    uint16_t ID; //ID del equipo
};
struct registro{
    uint64_t eq_nivel_inf; //equipos que se encuentran conectados despues de el equipo actual
    uint64_t type; //tipo del equipo
    uint64_t info;
    struct ID IDs;
    uint16_t *id_inf;
};
typedef struct registro Registro;
/**
 * @brief Esta funcion muestra los IDS de los equipos
 * Muestra el ID del equipo actual, el anterior a este y los siguientes
 * 
 * @param r vector de estructura de equipos
 * @param n tamaño del vector de estructuras
 */
void showIDs(Registro *r, int n);
int countDevices(FILE *f);