#include <iostream>
#include <fstream>
#include <string.h> 
using namespace std;

// Variable global para almacenar el nombre del archivo
char nombreArchivo[50];

// Estructura para almacenar un vértice
struct Vertice {
    float x, y, z;
};

// Variables globales
Vertice* vertices = nullptr;
int numVertices = 0;

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

// Función para cargar el archivo
void cargarArchivo() {
    cout << "Ingrese el nombre del archivo de vértices (.txt o .bin): ";
    cin >> nombreArchivo; // Guardamos el nombre en la variable global

    // Llamamos a la función para analizar si es .txt o .bin.
    const char* extension = obtenerExtension(nombreArchivo);
    bool esBinario = (strcmp(extension, "bin") == 0);

    if (esBinario) {
        cout << "Es binario.\n";
    } else {
        cout << "Es texto.\n";
    }
}

// Función para mostrar los vértices
void mostrarVertices() {
    // Utilizamos la variable global nombreArchivo
    const char* extension = obtenerExtension(nombreArchivo);
    bool esBinario = (strcmp(extension, "bin") == 0);

    ifstream archivo;
    if (esBinario) {
        archivo.open(nombreArchivo, ios::binary);
    } else {
        archivo.open(nombreArchivo);
    }
     /*
    Esta secuencia if es interesante. Revisa si el archivo es binario y
    lo abre como abriría un binario. De lo contrario (else) lo abrirá como un .txt
    */


    if (!archivo) {
        cout << "Sorry bro, el archivo no existe :)\n";
        return;
    }

    // Liberar memoria en caso de datos previamente cargados
    if (vertices) {
        delete[] vertices;
        vertices = nullptr;
    }

    // Leer número de vértices
    if (esBinario) {

        /*
        reinterpret_cast<char*> convierte la dirección de numVertices a un puntero char*  
            para que read() lo entienda.
        sizeof (int) cuenta exactamente 4 bytes (tamaño del int lol) desde el archivo.
        */
        archivo.read(reinterpret_cast<char*>(&numVertices), sizeof(int));
    } else {
        numVertices = 0;
        char linea[100];
        
        while (archivo.getline(linea, 100)) {
            //Cuenta la cantidad de vertices.
            numVertices++; 
        }
        
        // Crear un arreglo dinámico de vértices
        vertices = new Vertice[numVertices];
        
        // Limpiar indicadores de error y volver al inicio del archivo
        archivo.clear();
        archivo.seekg(0);

        // Variable temporal para llenar el arreglo vertices[]
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
            /*
            El if de arriba también es interesante. usamos strtok para separar espcios.archivo
            Segundo: Atof(token + 2) -> Convierte en float el valor que esté después de X, Y o Z;
            */

            vertices[indx] = {x, y, z};
            indx++;
        }
    }

    archivo.close();
    cout << "Archivo cargado correctamente. Se encontraron " << numVertices << " vértices.\n";
}

// Función principal con el menú
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
                break;
            default:
                cout << "Opción inválida, intente de nuevo.\n";
        }
    } while (opcion != 3);

    return 0;
}
