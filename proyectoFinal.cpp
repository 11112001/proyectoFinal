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
        archivo.seekg(0, ios::beg);  //reinicio del puntero

        numVertices = tamanoArchivo / sizeof(Vertice);
        if (numVertices <= 0 || numVertices > 1000) {
            cout << "Error: Número de vértices inválido.\n";
            return;
        }

        vertices = new Vertice[numVertices];
        archivo.read(reinterpret_cast<char*>(vertices), sizeof(Vertice) * numVertices);

        if (archivo.gcount() != sizeof(Vertice) * numVertices) {
            cout << "Error: No se leyeron todos los datos esperados.\n";
            delete[] vertices;
            vertices = nullptr;
            return;
        }
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
            float x = 0, y = 0;

            char* token = strtok(linea, " ");
            while (token) {
                if (strchr(token, 'X')) x = atof(token + 2);
                else if (strchr(token, 'Y')) y = atof(token + 2);
                token = strtok(NULL, " ");
            }

            vertices[indx++] = {x, y};
        }
    }

    archivo.close();
    cout << "Archivo cargado correctamente. Se encontraron " << numVertices << " vértices.\n";
    for (int i = 0; i < numVertices; i++) {
        cout << "(" << vertices[i].x << ", " << vertices[i].y << ")\n";
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

void unirVerticesManual() {
    if (!matrizAristas) {
        cout << "Error: Primero debe generar la matriz de adyacencia.\n";
        return;
    }

    int v1, v2;
    cout << "Ingrese el índice del primer vértice: ";
    cin >> v1;
    cout << "Ingrese el índice del segundo vértice: ";
    cin >> v2;

    v1 -=1;
    v2 -=1;

    if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices) {
        cout << "Error: Índices fuera de rango.\n";
        return;
    }

    *(matrizAristas[v1] + v2) = 1;
    *(matrizAristas[v2] + v1) = 1;

    cout << "Se ha unido el vértice " << v1 << " con el vértice " << v2 << ".\n";

    cout << "\nMatriz de Adyacencia actualizada:\n";
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cout << *(matrizAristas[i] + j) << " ";
        }
        cout << "\n";
    }
}

void generarArchivoOBJ() {
    ofstream archivoOBJ("salida.obj");
    
    if (!archivoOBJ) {
        cout << "Error: No se pudo abrir el archivo para escribir.\n";
        return;
    }

    for (int i = 0; i < numVertices; i++) {
        archivoOBJ << "v " << vertices[i].x << " " << vertices[i].y << " 0\n";
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            if (matrizAristas[i][j] == 1) {
                archivoOBJ << "l " << i + 1 << " " << j + 1 << "\n"; // +1 para que empiece desde el índice 1
            }
        }
    }

    archivoOBJ.close();
    cout << "Archivo .obj generado correctamente como 'salida.obj'.\n";
}


int main() {
    int opcion;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Cargar archivo de vértices\n";
        cout << "2. Mostrar vértices\n";
        cout << "3. Unir vértices y generar matriz\n";
        cout << "4. Unir vértices manualmente\n";
        cout << "5. Generar archivo .obg \n";
        cout << "6. Salir\n";
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
                unirVerticesManual();
                break;
            case 5:
                generarArchivoOBJ();
                break;
            case 6:
                cout << "Saliendo...\n";
                liberarMemoria();
                break;
            default:
                cout << "Opción inválida, intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}
