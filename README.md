                                                           ___  _                _
                                           _              / __)(_)              | |
 ____    ____   ___   _   _   ____   ____ | |_    ___    | |__  _  ____    ____ | |
|  _ \  / ___) / _ \ | | | | / _  ) / ___)|  _)  / _ \   |  __)| ||  _ \  / _  || |
| | | || |    | |_| || |_| |( (/ / ( (___ | |__ | |_| |  | |   | || | | |( ( | || |
| ||_/ |_|     \___/  \__  | \____) \____) \___) \___/   |_|   |_||_| |_| \_||_||_|
|_|                  (____/

## 🚀 Descripción:
Este proyecto en C++ permite cargar, leer y mostrar archivos de vértices en formatos .txt y .bin.
Se encarga de interpretar coordenadas en un espacio tridimensional y almacenarlas en estructuras dinámicas para su posterior procesamiento. (por ahora)

## 📍 Versión Proyecto:
**0.2.9**
Log: Los principales cambios se hicieron en mostrar vertices. Dónde leía con normalidad los archivos .txt pero al momento de leer .bin, explotaba. Afortunadamente se logró corregir

**0.3.0**
_14/03/2025/14:46_
Log: Se le ha agregado la función "unirVertices" que servirá para mostrar y unir los vertices. 

**0.3.1**
_14/03/2025/17:33_
log: Se ha arreglado la lectura de archivos binarios, solo estaba leyendo dos vertices. El problema, era una variable Z en la estructura. Al elminarse, permitió recorrer las lineas con normalidad, la Z estaba ocupando espacio valioso.

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
- [ ] Unir vértices secuencialmente  
- [ ] Unir vértices manualmente  
- [ ] Generar archivo .obj
- [ ] Subir la documentación.



## 📌 Autor
- Yeo - Desarrollador
- Año : 2025
- 🔗 GitHub: 11112001


## 📌 Fun Fact.
-Borré todo por accidente :D
- Se ha creado un "respaldo". En caso que el folder manage salga mal.
- El manage de carpeta ha sido más complejo de lo que esperé. (

# proyectoFinal
