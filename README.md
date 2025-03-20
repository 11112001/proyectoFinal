                                                           ___  _                _
                                           _              / __)(_)              | |
 ____    ____   ___   _   _   ____   ____ | |_    ___    | |__  _  ____    ____ | |
|  _ \  / ___) / _ \ | | | | / _  ) / ___)|  _)  / _ \   |  __)| ||  _ \  / _  || |
| | | || |    | |_| || |_| |( (/ / ( (___ | |__ | |_| |  | |   | || | | |( ( | || |
| ||_/ |_|     \___/  \__  | \____) \____) \___) \___/   |_|   |_||_| |_| \_||_||_|
|_|                  (____/

## 🚀 Descripción:
El proyecto "Gestión y Manipulación de Vértices en un Espacio 2D" es una aplicación interactiva desarrollada en C++ que permite a los usuarios cargar, visualizar, manipular y exportar un conjunto de vértices en un espacio bidimensional. A través de un menú interactivo en la consola, los usuarios pueden trabajar con datos geométricos almacenados en archivos de texto o binarios, representando figuras y relaciones entre puntos en un plano 2D.

El objetivo principal de este proyecto es ofrecer una herramienta sencilla y eficaz para gestionar vértices de figuras geométricas, representar sus conexiones a través de una matriz de adyacencia y exportar estos datos a un formato estándar de la industria, el .obj, utilizado en programas de modelado 3D como Blender o AutoCAD.

## 📍 Versión Proyecto:
**0.2.9**
Log: Los principales cambios se hicieron en mostrar vertices. Dónde leía con normalidad los archivos .txt pero al momento de leer .bin, explotaba. Afortunadamente se logró corregir

**0.5.0**
_14/03/2025/14:46_
Log: Se le ha agregado la función "unirVertices" que servirá para mostrar y unir los vertices. 

**0.5.1**
_14/03/2025/17:33_
log: Se ha arreglado la lectura de archivos binarios, solo estaba leyendo dos vertices. El problema, era una variable Z en la estructura. Al elminarse, permitió recorrer las lineas con normalidad, la Z estaba ocupando espacio valioso.

**0.6.0**
_14/03/2025_
log: Se le ha agregado una nueva función para unir vertices manualmente (unirVerticesManual), desafortunadamente no entendí como unir vertices.

**0.6.1**
_??/03/2025_ 00:27
log: Se ha creado un while nuevo, para que pueda saltar lineas al momento de abrir los archivos .TXT (antes no servía la lecutra lol)

**0.6.2**
_18/03/2025_ 00:37
log: Se ha corregido el unir vertices manualmente. Se ha agregado un v1 -= 1, v2=1. Restamos 1 al índice ingresado por el usuario para que el primer vértice corresponda con el índice 0 de la matriz, el segundo con el índice 1, y así sucesivamente

**1.0.0**
_18/03/2025_ 2:00 
log: Se ha agregado la última función. El programa funciona!!!! ESTA ES LA VERSION FINAL

**1.0.1**
_18/03/2025_ 10:05
log: Se ha agregado la documentación. 

**2.0.0**
_20/03/2025_ 1:23 
log1: Se ha mejorado la forma en que se manejan las estructuras, se corrigió la notación bidimensional de arrays tradicional para dar paso a Apuntadores 
log2: Se hicieron ajustes para que el .obj sea leído y escrito correctamente.

## 🛠️ Tecnologías Utilizadas
- ✅ C++
- ✅Librerías estándar (iostream, fstream, cstring)
- ✅ Git/GitHub

## 📂 Estructura del Repositorio
📂 main
- ┣ 📂 bin        # Archivos binarios de datos
- ┣ 📂 data       # Datos en formato de texto
- ┣ 📂 src        # Código fuente
- ┣ 📂 docs       # Documentación del proyecto
- ┗ 📄 README.md  # Descripción del proyecto


## 🔧 Cómo Compilar y Ejecutar
1. Clona este repositorio:  
   ```bash
   git clone https://github.com/11112001/proyectoFinal.git

⚠️ **Advertencia**: Odio CodeBlocks. Esta parte va por si son normales como yo y usan cualquier otra cosa que no sea 
codeblocks o google.

2. Descargar GCC (Gnu Compiler Collection)
3. g++ (nombre programa).cpp .o (ejecutable)
4. ./(ejecutable)

## 🚀 To-Do (Mejoras Futuras)
- [x] Cargar archivo de vértices  
- [x] Mostrar vértices  
- [x] Mostrar matriz  
- [x] Unir vértices secuencialmente  
- [x] Unir vértices manualmente  
- [x] Generar archivo .obj
- [x] Subir la documentación.



## 📌 Autor
- Yeo - Desarrollador
- Año : 2025
- 🔗 GitHub: 11112001
- 🔗 ig: yeo._ing

## 📌 Fun Fact.
-Borré todo por accidente :D
- Se ha creado un "respaldo". En caso que el folder manage salga mal.
- El manage de carpeta ha sido más complejo de lo que esperé. (

# proyectoFinal
