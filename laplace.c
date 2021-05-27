#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **crear_grid(int, int);
void **asignar_cf(int, int, double **);
void **ecuacion_laplace(int, int, double **);
double transformada(double, double, double, double);
double valor_z(double, double);
void condiciones_capacitores(double, double);
void mostrar_matriz(int, int, double **);
void llenar_matriz(int, int, double **);

int main(int argc, char **args){
    int filas, cols;
    double **u, r1, r2, h1, h2;

    //Crear archivos para datos en laplace.dat y laplace.csv
    FILE *output, *output2, *output3;			
    output = fopen("laplace.dat", "w");
    output2 = fopen("laplace.csv", "w");

    printf("Ingresa el radio interno: ");
    scanf("%lf", &r1);
    printf("¿Dónde está centrado?: ");
    scanf("%lf", &h1);
    printf("Ingresa el radio externo: ");
    scanf("%lf", &r2);
    printf("¿Dónde está centrado?: ");
    scanf("%lf", &h2);

    condiciones_capacitores(r1, h1);
    condiciones_capacitores(r2, h2);

    cols = filas = (int) round(transformada(r1, r2, h1, h2)); //Igualar a las filas es momentáneo... Creo
    
    //El +1 es debido a que el número de líneas en el grid es uno más que la divisiones
    u = crear_grid(filas + 1, cols + 1);

    asignar_cf(filas + 1, cols + 1, u);

    ecuacion_laplace(filas + 1, cols + 1, u);

    //Almacenar datos para gnuplot 3D
    for(int i = 0; i < cols + 1; i++){
        for(int j = 0; j < filas + 1; j++){
            fprintf(output, "%f\n", u[i][j]);
            fprintf(output2, "%f\n", u[i][j]);
        }
        fprintf(output, "\n");
        fprintf(output2, "\n");
    }
    printf("Archivos guardados.\n");
}

void condiciones_capacitores(double r, double h){
    if(r != h){
        printf("Error: Uno de los capacitores no es tangente al eje de las ordenadas.\n");
        exit(-1);
    }else if(h <= 0){
        printf("Error: uno de los capacitores está centrado en z = 0 o está en el eje negativo.\n");
        exit(-1);
    }
}

double valor_z(double r, double h){
    double z1, z2;
    z1 = 0.5 * (2 * h + sqrt(pow(2 * h, 2) - 4 * (pow(h, 2) - pow(r, 2))));
    return z1;
}

double transformada(double r1, double r2, double h1, double h2){
    double w1, w2;
    w1 = 1 / valor_z(r1, h1);
    w2 = 1 / valor_z(r2, h2);
    return 100 * (w1 - w2);
}

double **crear_grid(int filas, int columnas){
    double **grid;
    grid = calloc(filas, sizeof(double *));  
    for(int i = 0; i < filas; i++){
        grid[i] = calloc(columnas, sizeof(double *));
    }
    return grid;
}

void **asignar_cf(int filas, int cols, double **u){
    double l, r, b, t;

    printf("Ingresa las condiciones de frontera\n");
    printf("Valor del capacitor interno: ");
    scanf("%lf", &r);
    printf("Valor del capacitor externo: ");
    scanf("%lf", &l); 

    for(int j = 0; j < cols; j++){
        u[0][j] = l;
        u[cols - 1][j] = r;
    }
}

void **ecuacion_laplace(int filas, int cols, double **u){
    for(int k = 0; k < 1000; k++){
        for(int i = 1; i < cols - 1; i++){
            for(int j = 0; j < filas; j++){
                u[i][j] = 0.25 * (u[i+1][j] + u[i-1][j] + u[i][j+1] + u[i][j-1]);
            }
        } 
    }
}

void mostrar_matriz(int filas, int columnas, double **u_inversa){
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            printf("\t%7.2lf", u_inversa[i][j]);
        }
    putchar('\n');
    }
}

void llenar_matriz(int filas, int columnas, double **v){
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            v[i][j] = 0;
        }
    }
}
