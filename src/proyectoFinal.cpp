#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct Vertice {
    float x, y, z;
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
        archivo.seekg(0, ios::beg);
    
        numVertices = tamanoArchivo / sizeof(Vertice);
        if (numVertices <= 0 || numVertices > 1000) {
            cout << "Error: Número de vértices inválido.\n";
            return;
        }
        vertices = new Vertice[numVertices];
        archivo.read(reinterpret_cast<char*>(vertices), sizeof(Vertice) * numVertices);
    } else {
        numVertices = 0;
        char linea[100];
        while (archivo.getline(linea, 100)) {
            numVertices++;
        }

        archivo.clear();
        archivo.seekg(0);
        vertices = new Vertice[numVertices];
        int indx = 0;

        while (archivo.getline(linea, 100) && indx < numVertices) {
            float x = 0, y = 0, z = 0;
            char* token = strtok(linea, " ");
            while (token) {
                if (strchr(token, 'X')) x = atof(token + 2);
                else if (strchr(token, 'Y')) y = atof(token + 2);
                else if (strchr(token, 'Z')) z = atof(token + 2);
                token = strtok(NULL, " ");
            }
            vertices[indx++] = {x, y, z};
        }
    }

    archivo.close();
    cout << "Archivo cargado correctamente. Se encontraron " << numVertices << " vértices.\n";
    for (int i = 0; i < numVertices; i++) {
        cout << "(" << vertices[i].x << ", " << vertices[i].y << ")\n";
    }
}

int main() {
    int opcion;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Cargar archivo de vértices\n";
        cout << "2. Mostrar vértices\n";
        cout << "3. Salir\n";
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
                cout << "Saliendo...\n";
                liberarMemoria();
                break;
            default:
                cout << "Opción inválida, intente de nuevo.\n";
        }
    } while (opcion != 3);

    return 0;
}

