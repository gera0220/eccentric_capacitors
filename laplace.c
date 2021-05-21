#include <stdio.h>
#include <stdlib.h>

double **crear_grid(int, int);
void **asignar_cf(int, int, double **);
void **ecuacion_laplace(int, int, double **);

int main(int argc, char **args){
    int filas, cols;
    double **u;

    //Guardar datos en laplace.dat
    FILE *output, *output2;			
    output = fopen("laplace.dat", "w");
    output2 = fopen("heatmap/laplace.csv", "w");

    printf("Ingresa el número de saltos en x: ");
    scanf("%d", &cols);
    printf("Ingresa el número de saltos en y: ");
    scanf("%d", &filas);
    
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
    printf("Datos almacenados en laplace.dat y laplace.csv\n");
    fclose(output);
    fclose(output2);
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
    printf("Valor a la izquierda: ");
    scanf("%lf", &l);
    printf("Valor a la derecha: ");
    scanf("%lf", &r);
    printf("Valor abajo: ");
    scanf("%lf", &b);
    printf("Valor arriba: ");
    scanf("%lf", &t);

    for(int j = 0; j < cols; j++){
        u[0][j] = l;
        u[cols - 1][j] = r;
    }

    for(int i = 1; i < filas - 1; i++){
        u[i][filas - 1] = t;
        u[i][0] = b;
    }
}

void **ecuacion_laplace(int filas, int cols, double **u){
    for(int k = 0; k < 1000; k++){
        for(int i = 1; i < cols - 1; i++){
            for(int j = 1; j < filas - 1; j++){
                u[i][j] = 0.25 * (u[i+1][j] + u[i-1][j] + u[i][j+1] + u[i][j-1]);
            }
        } 
    }
}