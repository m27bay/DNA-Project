#pragma once

#include <stdio.h>
#include <string.h>

#include "../include/struct.h"

#define TAILLECHAINE 256

sequence_t* lireFichier(const char* nomFichier, int8_t* tailleTableau);