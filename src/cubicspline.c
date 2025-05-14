#include "cubicspline.h"

Spline InitSpline(double *x, double *y, int n)
{
    Spline spline;
    spline.size = n;
    spline.x = x;
    spline.y = y;

    spline.a = (double *)malloc(n * sizeof(double));
    spline.b = (double *)malloc((n - 1) * sizeof(double));
    spline.c = (double *)malloc(n * sizeof(double));
    spline.d = (double *)malloc((n - 1) * sizeof(double));
    spline.h = (double *)malloc((n - 1) * sizeof(double));

    for (int i = 0; i < n; i++)
        spline.a[i] = y[i];

    for (int i = 0; i < n - 1; i++)
    {
        spline.h[i] = x[i + 1] - x[i];
        // printf("%f ",spline.h[i]);
    }
    // printf("\n----\n");

    double **A = CalcA(spline.h, n);
    double *B = CalcB(spline.h, spline.a, n);

    // Solve Ac = B using Gaussian elimination
    gaussianElimination(A, B, spline.c, n);


    for (int i = 0; i < n - 1; i++)
    {
        spline.d[i] = (spline.c[i + 1] - spline.c[i]) / (3.0 * spline.h[i]);
        spline.b[i] = (spline.a[i + 1] - spline.a[i]) / spline.h[i] - (spline.h[i] * (spline.c[i + 1] + 2.0 * spline.c[i])) / 3.0;
    }

    // Free allocated memory for A and B
    for (int i = 0; i < n; i++)
        free(A[i]);
    free(A);
    free(B);

    return spline;
}

double **CalcA(double *h, int n)
{
    double **A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        A[i] = (double *)calloc(n, sizeof(double));
    }

    A[0][0] = 1.0;
    for (int i = 0; i < n - 1; i++)
    {
        if (i != (n - 2))
            A[i + 1][i + 1] = 2.0 * (h[i] + h[i + 1]);

        A[i + 1][i] = h[i];
        A[i][i + 1] = h[i];
    }

    A[0][1] = 0.0;
    A[n - 1][n - 2] = 0.0;
    A[n - 1][n - 1] = 1.0;

    return A;
}

double *CalcB(double *h, double *a, int n)
{
    double *B = (double *)calloc(n, sizeof(double));
    for (int i = 0; i < n - 2; i++)
    {
        B[i + 1] = 3.0 * (a[i + 2] - a[i + 1]) / h[i + 1] - 3.0 * (a[i + 1] - a[i]) / h[i];
    }
    return B;
}

short SearchIndex(double *x, int n, double data)
{
    int low = 0, high = n - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (x[mid] == data)
            return mid;
        else if (x[mid] < data)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low - 1;
}

double CalcSpline(double t, Spline *spline)
{
    if (t < spline->x[0] || t > spline->x[spline->size - 1])
        return 0.0;

    int i = SearchIndex(spline->x, spline->size, t);
    double dx = t - spline->x[i];
    return spline->a[i] + spline->b[i] * dx + spline->c[i] * dx * dx + spline->d[i] * dx * dx * dx;
}

double Calcd(double t, Spline *spline)
{
    if (t < spline->x[0] || t > spline->x[spline->size - 1])
    return 0.0;

    int i = SearchIndex(spline->x, spline->size, t);
    double dx = t - spline->x[i];
    return spline->b[i] + 2.0 * spline->c[i] * dx + 3.0 * spline->d[i] * dx * dx;
}

double Calcdd(double t, Spline *spline)
{
    if (t < spline->x[0] || t > spline->x[spline->size - 1])
    return 0.0;

    int i = SearchIndex(spline->x, spline->size, t);
    double dx = t - spline->x[i];
    return 2.0 * spline->c[i] + 6.0 * spline->d[i]* dx;
}

Spline2D InitSpline2D(double *x, double *y, int n)
{
    Spline2D spline;
    spline.size = n;
    spline.s = CalcS(x, y, n);
    spline.sx = InitSpline(spline.s, x, n);
    spline.sy = InitSpline(spline.s, y, n);
    return spline;
}

double *CalcS(double *x, double *y, int n)
{
    double *s = (double *)malloc(n * sizeof(double));
    s[0] = 0.0;
    for (int i = 1; i < n; i++)
    {
        double dx = x[i] - x[i - 1];
        double dy = y[i] - y[i - 1];
        s[i] = s[i - 1] + sqrt(dx * dx + dy * dy);
    }
    return s;
}

void CalcPosition(double s, Spline2D *spline, double *rx, double *ry)
{
    *rx = CalcSpline(s, &spline->sx);
    *ry = CalcSpline(s, &spline->sy);
}

void CalcCurvature(Spline2D *spline, double t, double *curv)
{
    double dx = Calcd(t, &spline->sx);
    double ddx = Calcdd(t, &spline->sx);
    double dy = Calcd(t, &spline->sy);
    double ddy = Calcdd(t, &spline->sy);

    *curv = (ddy * dx - ddx * dy) / (dx * dx + dy * dy);
}

void CalcYaw(Spline2D *spline, double t, double *yaw)
{
    *yaw = atan2(Calcd(t, &spline->sy), Calcd(t, &spline->sx));
}

void FreeSpline(Spline *spline)
{
    free(spline->a);
    free(spline->b);
    free(spline->c);
    free(spline->d);
    free(spline->h);
}

void FreeSpline2D(Spline2D *spline)
{
    free(spline->s);
    FreeSpline(&spline->sx);
    FreeSpline(&spline->sy);
}

// int main()
// {
//     FILE *fp = fopen("cubicspline.csv", "w");
//     if (fp == NULL)
//     {
//         printf("Error opening file!\n");
//         return -1;
//     }
//     fprintf(fp, "rx,ry,ryaw,rk\n");

//     printf("Spline 2D test\n");

//     double x[] = {-2.5, 0.0, 2.5, 5.0, 7.5, 3.0, -1.0};
//     double y[] = {0.7, -6, 5, 6.5, 0.0, 5.0, -2.0};
//     int n = sizeof(x) / sizeof(double);

//     Spline2D spline = InitSpline2D(x, y, n);

//     double s_max = spline.s[n-1];

//     int num_points = (int)(s_max / 0.1)+1;
//     double *s = (double *)malloc(num_points * sizeof(double));

//     double rx, ry, ryaw, rk;
//     for (int i = 0; i < num_points; i++)
//     {
//         s[i] = i * 0.1;
//         printf("%lf ",s[i]);
//         CalcPosition(s[i], &spline, &rx, &ry);
//         CalcYaw(&spline, s[i],&ryaw);
//         CalcCurvature(&spline, s[i], &rk);
//         fprintf(fp, "%lf, %lf, %lf, %lf\n", rx, ry, ryaw, rk);
//     }

//     fclose(fp);
//     free(s);
//     FreeSpline2D(&spline);
//     return 0;
// }