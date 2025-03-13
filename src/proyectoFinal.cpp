#include <iostream>
#include <fstream>
#include <string.h> 

using namespace std;

// Variable global para almacenar el nombre del archivo
char nombreArchivo[50];
Vertice* vertices = nullptr;
int numVertices = 0;
int** matrizAristas = nullptr;

// Estructura para almacenar un vértice
struct Vertice {
    float x, y, z;
};

const char* obtenerExtension(const char* nombre) 
{
    //strrchr es una función para buscar la última aparición de un caracter en una cadena.
    const char* punto = strrchr(nombre, '.');

    //Obtiene la extensión del archivo.
    return (punto) ? punto + 1 : "";
    /*
    (punto) - Comprueba si un punto NO es NULL
    ? - forma simplificada de if-else
    "" - si punto es NULL, significa que no hay punto en el nombre del archivo
    */
}

void liberarMemoria() {
    if (vertices) {
        delete[] vertices;
        vertices = nullptr;
    }
    if (matrizAristas) {
        for (int i = 0; i < numVertices; i++) {
            delete[] matrizAristas[i];
        }
        delete[] matrizAristas;
        matrizAristas = nullptr;
    }
}
// Función para cargar el archivo
void cargarArchivo() 
{
    char rutaArchivo[60] = "data/";
    cout << "Ingrese el nombre del archivo de vértices (.txt o .bin): ";
    cin >> nombreArchivo; 

    strcat (rutaArchivo, nombreArchivo);
    const char* extension = obtenerExtension(rutaArchivo);
    bool esBinario = (strcmp(extension, "bin") == 0);

    if (esBinario) {
        cout << "Es binario.\n";
    } else {
        cout << "Es texto.\n";
    }
}

// Función para mostrar los vértices
void mostrarVertices() {
    const char* extension = obtenerExtension(nombreArchivo);
    bool esBinario = (strcmp(extension, "bin") == 0);

    ifstream archivo;
    if (esBinario) {
        archivo.open(nombreArchivo, ios::binary);
    } else {
        archivo.open(nombreArchivo);
    }


    if (!archivo) {
        cout << "Sorry bro, el archivo no existe :)\n";
        return;
    }

    if (vertices) {
        delete[] vertices;
        vertices = nullptr;
    }

    // Leer número de vértices
    if (esBinario) {

        archivo.read(reinterpret_cast<char*>(&numVertices), sizeof(int));
    } else {
        numVertices = 0;
        char linea[100];
        
        while (archivo.getline(linea, 100)) {
            numVertices++; 
        }
        
        vertices = new Vertice[numVertices];
        
        // Limpiar indicadores de error y volver al inicio del archivo
        archivo.clear();
        archivo.seekg(0);

        int indx = 0;
        
        while (archivo.getline(linea, 100)) {
            float x = 0, y = 0, z = 0;

            //Divide "linea" en palabras separadas por espacio,
            char* token = strtok(linea, " ");
            
            while (token) {
                if (strchr(token, 'X')) {
                    x = atof(token + 2);
                } else if (strchr(token, 'Y')) {
                    y = atof(token + 2);
                } else if (strchr(token, 'Z')) {
                    z = atof(token + 2);
                }
                token = strtok(NULL, " ");
            }
            
            vertices[indx] = {x, y, z};
            indx++;
        }
    }

    archivo.close();
    cout << "Archivo cargado correctamente. Se encontraron " << numVertices << " vértices.\n";
    for (int i = 0; i < numVertices; i++)
    {
        cout << "(" << (vertices + i)->x << ", " << (vertices + i)->y << ")\n";
        
    }
}

//Función para unir vertices y mostrar matriz adyacente
void unirVertices()
{
    if(matrizAristas)
    {
        for (int i = 0; i < numVertices; i++)
        {
            delete [] *(matrizAristas + i);
        }
        
        delete [] matrizAristas;
    }

    //crear la matriz dinámica.
    matrizAristas = new int* [numVertices];
    for (int i = 0; i < numVertices - 1; i ++)
    {
        *(matrizAristas + i) = new int[numVertices]{};
    }

    /*
    el {} inicializa el valor de la fila en 0
    El resumen de este for es para recorrer cada FILA de la matriz.
    */

    int* filaActual;

    //conectarmos cada vértice.
    for (int i = 0; i < numVertices - 1; i ++) //recorre hasta el penultimo vertice.
    {
        filaActual = *(matrizAristas + i);
        *(filaActual + (i + 1)) = 1; //filaActual + (i + 1) apunta a la columna i + 1 de la fila actual. coloca un 1, indicando que el vértice i está conectado con i+1
        filaActual = *(matrizAristas + (i + 1));//Ahora filaActual apunta a la siguiente fila (i+1)
        *(filaActual + i) = 1; //filaActual + i apunta a la columna i de la fila i+1
    }

    //conectar el último vértice con el primero. Cerrar ciclos
    filaActual = *(matrizAristas + (numVertices - 1));
    *(filaActual) = 1;
    filaActual = *matrizAristas;
    *(filaActual + (numVertices - 1)) = 1;

    //mostrar la matriz de adyacencia:
    cout <<"\nMatriz generada:\n";
    
    for (int i = 0; i < numVertices; i++)
    {
        filaActual = *(matrizAristas + i);
        for (int j = 0; j < numVertices; j++)
        {
            cout <<*(filaActual + j) << " ";
        }
        cout << "\n";
    }
}



// Función principal con el menú
int main() {
    int opcion;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Cargar archivo de vértices\n";
        cout << "2. Mostrar vértices\n";
        cout << "3. Unir vértices secuencialmente\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cargarArchivo();
                break;
            case 2:
                mostrarVertices();
                break;
            case 3:
                unirVertices();
                break;
            case 4:
                cout << "Saliendo...\n";
                liberarMemoria();
                break;
            default:
                cout << "Opción inválida, intente de nuevo.\n";
        }
    } while (opcion != 3);

    return 0;
}
