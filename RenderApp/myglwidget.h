#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QDebug>

// #include <QOpenGLShader>


class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MyGLWidget(QWidget *parent=nullptr);

    ~MyGLWidget();                                                  // hacemos implicito el destructor para limpiar memoria GPU

private:
    QOpenGLShaderProgram *m_programScene;                           // objeto par dibujar el triangulo

    QOpenGLShaderProgram *m_programFilter;                          // objeto para efecto B/N

    QOpenGLFramebufferObject *m_fbo;                                // objeto para el fbo

    QOpenGLBuffer m_vboTriangulo;                                   // buffer vbo para el triangulo

    QOpenGLVertexArrayObject m_vaoTriangulo;                        // vao con instrucciones para el triangulo

    QOpenGLBuffer m_vboPantalla;                                    // buffer vbo para la textura

    QOpenGLVertexArrayObject m_vaoPantalla;                         // vao con instrucciones para la textura.

    float m_rotacion = 0.0f;                                        // variable para modificar el ángulo del triangulo.Valor por defecto 0.0 (en reposo)

    QVector3D m_colorFiltro = QVector3D((125.0f/255.0f), (125.0f/255.0f), (125.0f/255.0f));          // variable que permitirá modificar el color del fondo triangulo con valor por defecto (fondo gris)

    float m_zoom = 1.0f;                                            // variable para modificar el valor de zoom al triangulo.

    QVector3D m_colorTriangulo = QVector3D(1.0f, 1.0f, 1.0f);       // variable para modificar color interior del triangulo con valor por defecto.

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;


public slots:                                                       // creamos 2 slots para recibir ordenes...
    void setRotation(float angulo);                                 // mediante este slot recibimos y ejecutamos la rotación del triangulo.
    void setColorFiltro(float r, float g, float b);                 // mediante este slot recibimos los datos del color nuevo del fondo del triangulo y ejecutamos el cambio.
    void setZoom(float zoom);                                       // mediante este slot recibimos el valor de zoom y ejecutamos el cambio.
    void setColorTriangulo(float r, float g, float b);              // mediante este slot recibimos los datos del color nuevo del interior del triangulo y ejecutamos el cambio.

};

#endif // MYGLWIDGET_H
