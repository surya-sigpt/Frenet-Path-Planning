#ifndef UTILIS_H
#define UTILIS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define M_PI 3.14159265358979323846

void gaussianElimination(double **A, double *B, double *X, const short size);

#endif