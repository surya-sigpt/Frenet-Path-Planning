#ifndef CUBICSPLINE_H
#define CUBICSPLINE_H


#include "utilis.h"

typedef struct 
{
    double *x;
    double *y;
    double *h;
    double *a;
    double *c;
    double *b;
    double *d;
    short size;
}Spline;


Spline InitSpline(double *x, double *y, int n);
void FreeSpline(Spline *spline);
double **CalcA(double *h, int n);
double *CalcB(double *h, double *a, int n);
short SearchIndex(double *x, int n, double data);
double CalcSpline(double t, Spline *spline);
double Calcd(double t, Spline *spline);
double Calcdd(double t, Spline *spline);

typedef struct
{
    double *s;
    Spline sx;
    Spline sy;
    double *ds;
    short size;
}Spline2D;

Spline2D InitSpline2D(double *x, double *y, int n);
void FreeSpline2D(Spline2D *spline);
double *CalcS(double *x, double *y, int n);
void CalcPosition(double s, Spline2D *spline, double *rx, double *ry);
void CalcCurvature(Spline2D *spline, double t, double *curv);
void CalcYaw(Spline2D *spline, double t, double *yaw);


// double *MatrixMultiplication(const double **A, const double *b, const short size);

#endif