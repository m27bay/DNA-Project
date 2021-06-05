#pragma once

#include "lire.h"
#include "../include/struct.h"

float tableauDistance[5][5] = 
    { {0, 2, 1, 2, 1.5},
      {2, 0, 2, 1, 1.5},
      {1, 2, 0, 2, 1.5},
      {2, 1, 2, 0, 1.5},
      {1.5, 1.5, 1.5, 1.5, 0} };

void afficherSequence(const sequence_t* tableauSequence, const int8_t taille);
void libereSequence(sequence_t* tableauSequence, const int8_t taille);
u_int8_t calculDistanceEdition(const sequence_t s, const sequence_t s2);