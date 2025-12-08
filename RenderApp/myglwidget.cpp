#include "myglwidget.h"
#include <QDebug>
#include <QMatrix4x4>

MyGLWidget::MyGLWidget(QWidget *parent):QOpenGLWidget(parent), m_programScene(nullptr), m_programFilter(nullptr)
{
    qDebug() << "Cargando Clase...!";
}



MyGLWidget::~MyGLWidget()
{
    makeCurrent();                                                                                                      // para tener el contexto
    delete m_programScene;                                                                                              // para liberar la memoria del Shader 1
    delete m_programFilter;                                                                                             // para liberar la memoria del Shader 2
    delete m_fbo;                                                                                                       // para liberar la memoria del fbo
    m_vboTriangulo.destroy();                                                                                           // para liberar la memoria del buffer de la gpu (datos crudos del triangulo)
    m_vaoTriangulo.destroy();                                                                                           // para liberar la memoria del vao (instrucciones para el shader del triangulo)
    m_vboPantalla.destroy();                                                                                            // para liberar la memoria del buffer de la gpu (datos crudos de la textura)
    m_vaoPantalla.destroy();                                                                                            // para liberar la memoria del vao (instruciones para el shader de la textura)
    doneCurrent();
}



void MyGLWidget::initializeGL()
{

    initializeOpenGLFunctions();                                                                                        // inicializamos las funciones openGL. Esto carga los drivers de la tarjeta gráfica

    float verticesTriangulo[] =                                                                                         // creamos el array que contendrá los datos de vertices del triangulo y de los colores por vertice.
    {
    // X,    Y,    Z      R,   G,   B
     0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };


    m_programScene = new QOpenGLShaderProgram();                                                                        // creamos el objeto que contendrá los shaders para dibujar el triangulo.


    /* -- AGREGAMOS / PROGRAMAMOS LOS SHADERS PARA NUESTRO TRIANGULO -- */

    m_programScene->addShaderFromSourceCode(QOpenGLShader::Vertex,                                                      // agregamos el vertex shader (posición y colores)
                                            "#version 330 core\n"
                                            "layout(location = 0) in vec3 posTriangulo;\n"

                                            "layout(location = 1) in vec3 colorVertices;\n"
                                            "out vec4 colorToFragment;\n"
                                            "uniform mat4 matrizTransformacion;\n"                                      // variabla uniform tipo matriz 4x4 para la rotación del triangulo
                                            "uniform vec3 mod_colorTriangulo;\n"

                                            "void main() {\n"
                                            "   gl_Position = matrizTransformacion * vec4(posTriangulo, 1.0);\n"        // multiplicación matriz * vector para posición final.
                                            "   vec3 colorMezclado = colorVertices * mod_colorTriangulo;\n"
                                            "   colorToFragment = vec4(colorMezclado, 1.0);\n"
                                            "}");

    m_programScene->addShaderFromSourceCode(QOpenGLShader::Fragment,                                                    // agregamos el fragment shader (coloreo de pixeles)
                                            "#version 330 core\n"
                                            "in vec4 colorToFragment;\n"
                                            "out vec4 colorTriangulo;\n"

                                            "void main() {\n"
                                            "   colorTriangulo = vec4(colorToFragment);\n"
                                            "}");


    m_programScene->link();                                                                                             // enlazamos los shaders para el Triangulo (Inter-Shader Linking)


        if(!m_programScene->isLinked())                                                                                 // comprobamos que los shaders de escena hayan linkeado correctamente
        {
            qDebug() << "Error Shader Scene:" << m_programScene->log();
        }
        else
        {
            qDebug() << "Shader Scene, creado correctamente";
        }

    m_programScene->bind();                                                                                             // activamos el programa de shaders para el Triangulo


    /* --- CREAMOS Y ACTIVAMOS EL VAO (HOW TO PARA DIBUJAR EL TRIANGULO),
    LUEGO EL VBO (BUFFER PARA DATA DE VERTICES E INFO DEL COLOR DEL TRIANGULO  --- */

    m_vaoTriangulo.create();                                                                                            // creamos vao con howto para triangulo
    m_vaoTriangulo.bind();                                                                                              // activamos vao.

    m_vboTriangulo.create();                                                                                            // creamos vbo para almacenar datos posición y color triangulo
    m_vboTriangulo.bind();                                                                                              // activamos vbo
    m_vboTriangulo.allocate(verticesTriangulo,sizeof(verticesTriangulo));                                               // asignamos los datos "crudos" al vbo y el tamaño del buffer (el mismo de los datos)


    /* -- HABILITAMOS EL "SLOT" 0 PARA LA ENTRADA DE DATOS DE POSICIÓN DEL TRIANGULO AL VERTEX SHADER,
    Y LAS INSTRUCCIONES PARA OBTENER BYTE CORRESPONDIENTES -- */

    m_programScene->enableAttributeArray(0);                                                                            // para datos de vertices del triangulo
    m_programScene->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(float));                                             // "3 posiciones por vertice, lee desde la posición 0, salta 6 posiciones para rescatar la data del siguiente vertice".


    /* -- HABILITAMOS EL "SLOT" 1 PARA LA ENTRADA DE DATOS DEL COLOR DEL TRIANGULO AL VERTEX SHADER,
    Y LAS INSTRUCCIONES PARA OBTENER LOS BYTES CORRESPONDIENTES --- */

    m_programScene->enableAttributeArray(1);                                                                            // para datos de color del triangulo
    m_programScene->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(float), 3, 6*sizeof(float));                               // "3 posiciones por color, lee desde la posicion 3, salta 6 posiciones para rescatar la data el siguiente color.


    m_vboTriangulo.release();                                                                                           // se liberan las instancias..
    m_vaoTriangulo.release();
    m_programScene->release();


    float verticesPantalla[] =
    {                                                                                                                   // creamos el array que contiene los vertices de la pantalla que contendrá el triangulo
    // X      Y      U    V
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f, 1.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, 0.0f, 1.0f
    };


     /* -- AGREGAMOS / PROGRAMAMOS LOS SHADERS PARA LA PANTALLA QUE CONTENDRÁ EL TRIANGULO -- */

    m_programFilter = new QOpenGLShaderProgram();                                                                       // creamos la instancia del programa de shaders para el filtro.

    m_programFilter->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                            "#version 330 core\n"
                                            "layout(location = 0) in vec2 posPantalla;\n"
                                            "layout(location = 1) in vec2 coordFiltro;\n"
                                            "out vec2 uvFiltro;\n"

                                            "void main() {\n"
                                            "   gl_Position = vec4(posPantalla, 0.0, 1.0);\n"
                                            "   uvFiltro = coordFiltro;\n"
                                            "}");

    m_programFilter->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                             "#version 330 core\n"
                                             "in vec2 uvFiltro;\n"
                                             "out vec4 colorFiltro;\n"
                                             "uniform sampler2D screenTexture;\n"

                                             "void main() {\n"
                                             "   vec4 pixelColor = texture(screenTexture, uvFiltro);\n"
                                             "   colorFiltro = vec4(1.0 - pixelColor.r, 1.0 - pixelColor.g, 1.0 - pixelColor.b, 1.0);\n"
                                             "}");

    m_programFilter->link();                                                                                            // enlazamos los shaders para la pantalla (Inter-Shader Linking)


    if(!m_programFilter->isLinked())                                                                                    // comprobamos que los shaders de escena esten correctamente linkeados.
    {
        qDebug() << "Error Shader Filter:" << m_programFilter->log();
    }
    else
    {
        qDebug() << "Shader Filter, creado correctamente";
    }

    m_programFilter->bind();                                                                                            // activamos el programa de shaders de la pantalla

    m_vaoPantalla.create();                                                                                             // creamos vao con howto para dibjar pantalla
    m_vaoPantalla.bind();                                                                                               // activamos vao

    m_vboPantalla.create();                                                                                             // creamos vbo para almacenar array pantalla
    m_vboPantalla.bind();                                                                                               // activamos vbo
    m_vboPantalla.allocate(verticesPantalla, sizeof(verticesPantalla));                                                 // asignamos los datos crudos del array de pantalla.

    /* -- HABILITAMOS EL "SLOT" 0 PARA LA ENTRADA DE DATOS DE POSICIÓN PANTALLA AL VERTEX SHADER,
    Y GENERAMOS LAS INSTRUCCIONES PARA OBTENER LOS BYTES CORRESPONDIENTES -- */

    m_programFilter->enableAttributeArray(0);
    m_programFilter->setAttributeBuffer(0, GL_FLOAT, 0, 2, 4 * sizeof(float));



    /* -- HABILITAMOS EL "SLOT" 1 PARA LA ENTRADA DE DATOS DE FILTRO AL VERTEX SHADER,
    Y GENERAMOS LAS INSTRUCCIONES PARA OBTENER LOS BYTES CORRESPONDIENTES -- */

    m_programFilter->enableAttributeArray(1);
    m_programFilter->setAttributeBuffer(1, GL_FLOAT, 2 * sizeof(float), 2, 4 * sizeof(float));


    m_vaoPantalla.release();
    m_vboPantalla.release();
    m_programFilter->release();

    /* -- FBO ("LIENZO INVISIBLE DONDE SE DIBUJARÁ EL TRIANGULO -- */

    m_fbo = new QOpenGLFramebufferObject(1024,1024,QOpenGLFramebufferObject::CombinedDepthStencil);                     // creamos el objeto FBO donde se renderizara el triangulo (lienzo virtual).


        if(!m_fbo->isValid())                                                                                           // comprobamos que el fbo se cree correctamente.
        {
            qDebug() << "ERROR CRÍTICO: El FBO no es válido";
        }
        else
        {
            qDebug() << "FBO válido";
        }

}



void MyGLWidget::paintGL()
{
    /* -- PREPARAMOS EL AREA DE DIBUJO DEL FBO Y DIBUJAMOS EN ÉL-- */

    m_fbo->bind();                                                                                                      // activamos el fbo
    glViewport(0,0, m_fbo->width(),m_fbo->height());                                                                    // definimos la región rectangular donde se dibujará el contenido OpenGL
    glClearColor(m_colorFiltro.x(), m_colorFiltro.y(), m_colorFiltro.z(), 1.0f);                                        // ahora el color de fondo del FBO que será controlable de manera externa..
    glClear(GL_COLOR_BUFFER_BIT);                                                                                       // borramos el buffer de color de la ventana, para llenarlo con el color azul definido en el paso anterior.

    m_programScene->bind();                                                                                             // activamos el programa de los shader y el vao para dibujar el triangulo en el fbo

    QMatrix4x4 matriz;                                                                                                  // creamos la matriz, para calculo de la rotación del triangulo usando la matriz de 4x4
    matriz.setToIdentity();                                                                                             // ponemos a la matriz en estado "por defecto"
    matriz.rotate(m_rotacion, 0.0f, 0.0f, 1.0f);                                                                        // calculamos la rotación usando como variable de entrada el valor de m_rotación y setando como eje de rotación Z.
    matriz.scale(m_zoom);                                                                                               // cambiamos la escala del triangulo a modo de zoom in-out.
    m_programScene->setUniformValue("matrizTransformacion", matriz);                                                    // seteamos el valor de entrada a la variable uniform matrizTransformacion del vertex shader del triangulo.
    m_programScene->setUniformValue("mod_colorTriangulo", m_colorTriangulo);                                            // seteamos el valor de entrada a la variabla uniform mod_tinteTriangulo del vertex shader del triangulo.

    m_vaoTriangulo.bind();                                                                                              // activamos vao
    glDrawArrays(GL_TRIANGLES,0,3);                                                                                     // dibujamos triangulo en el FBO.
    m_vaoTriangulo.release();                                                                                           // liberamos vao
    m_programScene->release();                                                                                          // liberamos shaders

    m_fbo->release();                                                                                                   // liberamos el fbo para continuar con el dibujo de la pantalla


    /* -- DIBUJAMOS PANTALLA (REGIÓN DONDE SE MONTARÁ EL CUADRADO CON EL TRIANGULO INTERIOR) -- */

    glViewport(0, 0, width(), height());                                                                                // definimos la región donde se dibujará la escena (cuadrado que contendrá textura traida desde el fbo).
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);                                                                               // pintaremos blanco el fondo (zona externa al cuadrado que contiene la textura traida desde el fbo).
    glClear(GL_COLOR_BUFFER_BIT);                                                                                       // limpiamos buffer de color para aplicar el fondo blanco.


    /* -- ACTIVAMOS EL PROGRAMA DE LOS SHADERS DE FILTRO Y EL VAO,
    ESTE ÚLTIMO PARA EJECUTAR LAS INSTRUCCIONES DE ARMADO DE LA VENTANA QUE CONTENDRÁ LA TEXTURA GENERADA EN EL FBO (COLOR FONDO + TRIANGULO) -- */

    m_programFilter->bind();                                                                                            // activamos shaders
    m_vaoPantalla.bind();                                                                                               // activamos vao

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_fbo->texture());                                                                     // activa la "ranura" o unidad de textura 2D y la conecta a la imagen generada en el fbo (triangulo + fondo)
    m_programFilter->setUniformValue("screenTexture", 0);                                                               // la variable global screenTexture (shader) buscará la textura en la ranura 0.

    glDrawArrays(GL_TRIANGLES, 0, 6);                                                                                   // dibujamos el cuadrado de la pantalla (2 triangulos)

    m_vaoPantalla.release();                                                                                            // liberamos el vao
    m_programFilter->release();                                                                                         // liberamos el programa de shader del cuadrado contenedor de la textura (triangulo + fondo).
}



void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}


    /* -- FUNCIONES PARA HACER QUE EL DINBUJO SEA CONTROLABLE (ROTACIÓN, ZOOM, CAMBIO DE COLORES) -- */

void MyGLWidget::setRotation(float angulo)                                                                              // mediante esta función se podrá rotar el triangulo.
{
    m_rotacion = angulo;
    update();
}



void MyGLWidget::setColorFiltro(float r, float g, float b)                                                              // mediante esta función se podrá cambiar el color del fondo del triangulo.
{
    m_colorFiltro = QVector3D(r, g, b);
    update();
}



void MyGLWidget::setZoom(float zoom)                                                                                    // mediante esta función se podrá realizar zoom in-out al triangulo.
{
    m_zoom = zoom;
    update();
}



void MyGLWidget::setColorTriangulo(float r, float g, float b)                                                           // mediante esta función se podria cambiar el color del triangulo
{
    m_colorTriangulo = QVector3D(r,g,b);
    update();

}
