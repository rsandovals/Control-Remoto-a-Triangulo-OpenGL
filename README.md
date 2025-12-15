# 🎮 Sistema de Control Remoto de Renderizado 3D (OpenGL + TCP/UDP)

![Estado del Proyecto](https://img.shields.io/badge/Estado-Terminado-success)
![Qt Version](https://img.shields.io/badge/Qt-6.7-green)
![Lenguaje](https://img.shields.io/badge/C%2B%2B-17-blue)
![Plataforma](https://img.shields.io/badge/Plataforma-Windows%20%7C%20Linux-lightgrey)

Una demostración técnica de arquitectura distribuida **Cliente-Servidor** para el control en tiempo real de gráficos acelerados por hardware. El proyecto consta de dos aplicaciones independientes que se comunican mediante protocolos de red híbridos (TCP y UDP).

---

## 🚀 Características Principales

### 🖥️ RenderApp (Servidor de Visualización)
* **Motor Gráfico:** Implementación personalizada sobre `QOpenGLWidget` utilizando **OpenGL Moderno** (Core Profile).
* **Pipeline Programable:** Uso de **Shaders GLSL** (Vertex & Fragment) para efectos visuales.
* **Render-to-Texture (FBO):** Generación de texturas en tiempo real mediante *Framebuffer Objects* para post-procesamiento.
* **Transformaciones:** Rotación, Escalado (Zoom) y Colorización dinámica mediante matrices `QMatrix4x4`.
* **Servidor Híbrido:** Capacidad de escucha simultánea o selectiva en puertos TCP y UDP.

### 🎛️ ControlApp (Cliente de Mando)
* **Interfaz de Control:** UI intuitiva con Sliders, Diales y validación de estados.
* **Protocolo Personalizado:** Implementación de un protocolo de texto ligero (`CLAVE:VALOR`) para la transmisión de comandos.
* **Manejo de Redes:**
    * **TCP:** Conexión fiable con detección de timeouts y reconexión.
    * **UDP:** Envío de datagramas de alta velocidad ("Fire and Forget") para actualizaciones fluidas.
* **Feedback Visual:** Sistema de Logs con *timestamp* y barra de estado con notificaciones ricas (HTML).
* **Estilo:** Interfaz personalizada mediante **Qt Style Sheets (QSS)** con efectos de relieve y temas visuales.

---

## 🛠️ Tecnologías Utilizadas

| Categoría | Componentes Clave |
| :--- | :--- |
| **Core C++** | POO, Señales y Slots, Gestión de Memoria, Punteros Inteligentes. |
| **Gráficos 3D** | `QOpenGLWidget`, `QOpenGLShaderProgram`, `QOpenGLFramebufferObject`, `glDrawArrays`. |
| **Redes** | `QTcpServer`, `QTcpSocket`, `QUdpSocket`, `QNetworkDatagram`. |
| **Interfaz (GUI)** | `QMainWindow`, `QSlider`, `QDial`, `QTextEdit`, `QStatusBar`. |
| **Estilos** | CSS/QSS, Pseudo-estados (`:disabled`, `:pressed`), Diseño Responsivo. |

---

## 🔧 Instalación y Compilación

### Requisitos Previos
* **Qt Framework 6.x** (o superior).
* Compilador C++ compatible (MSVC 2019+ en Windows, GCC en Linux).
* Librerías OpenGL (en Linux: `sudo apt install libgl1-mesa-dev`).

### Pasos
1.  Clonar el repositorio:
    ```bash
    git clone [https://github.com/rsandovals/Control-Remoto-a-Triangulo-OpenGL.git](https://github.com/rsandovals/Control-Remoto-a-Triangulo-OpenGL.git)
    ```
2.  Abrir el proyecto en **Qt Creator**:
    * Para compilar todo junto, abrir el archivo `TodoElSistema.pro` (si usas Subdirs).
    * O abrir individualmente `RenderApp/RenderApp.pro` y `ControlApp/ControlApp.pro`.
3.  Compilar y Ejecutar (Ctrl+R).

---

## 📖 Cómo Usar

1.  Inicie **RenderApp**.
2.  Seleccione el protocolo de escucha (TCP o UDP) y haga clic en **"Iniciar Servidor"**.
3.  Inicie **ControlApp**.
4.  Seleccione el mismo protocolo y haga clic en **"Conectar"**.
5.  ¡Juegue con los controles!
    * 🎨 **RGB Fondo:** Cambia el color del lienzo.
    * 🔺 **RGB Triángulo:** Tinta el objeto 3D.
    * 🔄 **Rotación:** Gira el objeto sobre su eje Z.
    * 🔍 **Zoom:** Acerca o aleja la cámara virtual.

---

## 📸 Capturas de Pantalla

*(Aquí puedes subir un par de imágenes de tus ventanas funcionando)*

---

**Autor:** Rodrigo Sandoval.  
Desarrollado como proyecto de demostración de competencias en C++ y Qt Framework.
