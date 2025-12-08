#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>                                                                           // para conexiones sobre TCP
#include <QUdpSocket>                                                                           // para conexiones sobre UDP
#include <QDateTime>                                                                            // nos permite obtener hh:mm:ss para el log.

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket *m_socketTCP = nullptr;
    QUdpSocket *m_socketUDP = nullptr;

private slots:

    void on_btnConectar_clicked(bool checked);
    void onConectado();                                                                         // función modifica estado de widgets al conectar.
    void onDesconectado();                                                                      // función modifica estado de widgets al desconectar.
    void enviarColor();                                                                         // función que envia cambios de color. Se activará al mover cualquie slider de color.
    void enviarRotacion();                                                                      // función que envía cambios de angulo de figura. Se activará al mover el díal.
    void enviarColorTriangulo();                                                                // función que envia cambio de color para interior del triangulo.
    void enviarZoom();                                                                          // función que envia cambios de zoom (in-out) al triangulo.
    void enviarComando(QString instruccion);                                                    // función auxiliar para no repetir código.
    void limpiarSocket();                                                                       // función que limpia memoria y anula los punteros m_socketTCP y m_socketUDP
    void habilitarControles(bool estado);                                                       // función auxiliar que ayuda a habilitar y deshabilitar los ControlBox durante la conexión y desconexión.
    void agregarLog(QString mensaje);                                                           // función auxiliar para agregar el mensaje a QTextEdit a modo de log.



};
#endif // MAINWINDOW_H
