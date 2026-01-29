# Minishell - 42

*Este proyecto ha sido creado como parte del currículo de 42 por **aleconst** y **alejandj**.*

## 📝 Descripción

**Minishell** es un proyecto que consiste en la creación de una shell básica, una interfaz de línea de comandos que actúa como intermediaria entre el usuario y el sistema operativo. El objetivo principal es replicar el comportamiento básico de **Bash**, permitiendo al usuario interactuar con el sistema mediante una interfaz de línea de comandos robusta y funcional.

### ⚙️ Funcionalidades principales
* **Prompt interactivo:** Muestra una línea de espera lista para recibir comandos.
* **Ejecución de binarios:** Busca y ejecuta programas mediante la variable `PATH` o rutas específicas.
* **Built-ins:** Implementación propia de comandos esenciales: `echo`, `cd`, `pwd`, `export`, `unset`, `env` y `exit`.
* **Pipelines (`|`):** Redirección de la salida de un comando a la entrada del siguiente.
* **Redirecciones:** Manejo de entrada/salida mediante `<`, `>`, `>>` y el modo `<<` (here-doc).
* **Variables de Entorno:** Gestión y expansión de variables (incluyendo `$?` para el estado de salida).
* **Señales:** Gestión correcta de interrupciones como `Ctrl-C`, `Ctrl-D` y `Ctrl-\`.

---

## 🚀 Instrucciones

### 📋 Requisitos previos
El proyecto utiliza la librería **GNU Readline**. Asegúrate de tenerla instalada en tu sistema (en sistemas basados en Debian/Ubuntu se instala así):

```bash
sudo apt-get install libreadline-dev
```

### 🛠️ Compilación e Instalación
1. #### Clona este repositorio:
```bash
git clone https://github.com/AlejandroJimenez16/MiniShell.git
```

2. #### Compila el proyecto usando el Makefile:
```bash
make
```

### ⌨️ Ejecución
Una vez compilado el binario, puedes iniciar la shell ejecutando:
```bash
./minishell
```
Para salir de la shell, puedes usar el comando *exit* o presionar *Ctrl-D*.

---

## 📚 Recursos
### 📒 Referencias
Para el desarrollo de este proyecto se han consultado las siguientes fuentes clásicas:

* [GNU Bash Manual](https://www.gnu.org/software/bash/manual/): Referencia principal para replicar el comportamiento estándar.

* [Man pages (Linux Programmer's Manual)](https://www.man7.org/linux/man-pages/man1/man.1.html): Documentación técnica de funciones clave como `fork`, `execve`, `waitpid`, `pipe`, `dup2` y `signal`.

### 🤖 Uso de Inteligencia Artificial (IA)
En el desarrollo de este proyecto, se ha utilizado Inteligencia Artificial de la siguiente manera:

* **Depuración de memoria**: Se utilizó IA para analizar trazas complejas de Valgrind e identificar el origen de fugas de memoria (*leaks*).
* **Generación de casos de prueba**: La IA fue utilizada para generar casos de prueba con casos extremos (*edge cases*), combinaciones inusuales de *tokens*, y sintaxis inválida para asegurar la robustez del código.
---
