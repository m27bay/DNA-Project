#pragma once

#include <stdlib.h>

typedef struct sequence_s {
    char* chaine;
    u_int8_t taille;
} sequence_t;

typedef struct distance_s {
    sequence_t s, s2;
    float dist;
} distance_t;

void afficherSequence(const sequence_t* tableauSequence, const u_int8_t taille);
void libereSequence(sequence_t* tableauSequence, const u_int8_t taille);
