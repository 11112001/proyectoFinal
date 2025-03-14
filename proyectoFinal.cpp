#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct Vertice {
    float x, y;
};

// Variable global para almacenar el nombre del archivo
char nombreArchivo[50];
Vertice* vertices = nullptr;
int numVertices = 0;
int** matrizAristas = nullptr;

const char* obtenerExtension(const char* nombre)
{
    const char* punto = strrchr(nombre, '.');
    return (punto) ? punto + 1 : "";
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

void cargarArchivo() {
    cout << "Ingrese el nombre del archivo de vértices (.txt o .bin): ";
    char nombreEntrada[50];
    cin >> nombreEntrada;

    const char* extension = obtenerExtension(nombreEntrada);
    bool esBinario = (strcmp(extension, "bin") == 0);

    if (esBinario) {
        strcpy(nombreArchivo, "bin/");
    } else {
        strcpy(nombreArchivo, "data/");
    }
    strcat(nombreArchivo, nombreEntrada);
    cout << "Archivo seleccionado: " << nombreArchivo << endl;
}

void mostrarVertices() {
    if (!nombreArchivo[0]) {
        cout << "Error: No hay archivo cargado.\n";
        return;
    }

    const char* extension = obtenerExtension(nombreArchivo);
    bool esBinario = (strcmp(extension, "bin") == 0);

    ifstream archivo(nombreArchivo, esBinario ? ios::binary : ios::in);
    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo.\n";
        return;
    }

    liberarMemoria();

    if (esBinario) {
        archivo.seekg(0, ios::end);
        int tamanoArchivo = archivo.tellg();
        archivo.seekg(0, ios::beg);  //reinicio del mlprido puntero

        numVertices = tamanoArchivo / sizeof(Vertice);
        if (numVertices <= 0 || numVertices > 1000) {
            cout << "Error: Número de vértices inválido.\n";
            return;
        }

        vertices = new Vertice[numVertices];
        archivo.read(reinterpret_cast<char*>(vertices), sizeof(Vertice) * numVertices);

        // Se revisa si se leyeron todos los datos
        if (archivo.gcount() != sizeof(Vertice) * numVertices) {
            cout << "Error: No se leyeron todos los datos esperados.\n";
            delete[] vertices;
            vertices = nullptr;
            return;
        }
    }


    archivo.close();
    cout << "Archivo cargado correctamente. Se encontraron " << numVertices << " vértices.\n";
    for (int i = 0; i < numVertices; i++) {
        cout << "(" << vertices[i].x << ", " << vertices[i].y << ")\n"; //aritmetica
    }
}

void unirVertices() {
    liberarMemoria();
    
    if (numVertices < 2) {
        cout << "Error: Se necesitan al menos dos vértices para unir.\n";
        return;
    }
    
    matrizAristas = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        matrizAristas[i] = new int[numVertices]{};
    }
    
    for (int i = 0; i < numVertices - 1; i++) {
        *(matrizAristas[i] + (i + 1)) = 1;
        *(matrizAristas[i + 1] + i) = 1;
    }
    
    *(matrizAristas[numVertices - 1]) = 1;
    *(matrizAristas[0] + (numVertices - 1)) = 1;
    
    cout << "\nMatriz de Adyacencia generada:\n";
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cout << *(matrizAristas[i] + j) << " ";
        }
        cout << "\n";
    }
}

int main() {
    int opcion;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Cargar archivo de vértices\n";
        cout << "2. Mostrar vértices\n";
        cout << "3. Unir vértices y generar matriz\n";
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
    } while (opcion != 4);

    return 0;
}

