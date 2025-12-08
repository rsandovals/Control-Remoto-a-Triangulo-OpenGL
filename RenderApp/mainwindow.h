#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>                                                                           // servidor TCP
#include <QTcpSocket>                                                                           // gestion de conexiones TCP
#include <QUdpSocket>                                                                           // gestión de conexiones UDP
#include <QNetworkDatagram>                                                                     // gestión de datagramas UDP

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
    QTcpServer *m_servidorTCP = nullptr;                                                        // para configurar el servidor tcp
    QTcpSocket *m_socketClienteTCP = nullptr;                                                   // para gestionar el socket TCP.
    QUdpSocket *m_socketUDP=nullptr;                                                            // para gestionar el socket UDP.

private slots:
    void onNuevaConexionTCP();                                                                  // para la gestión de conexiones nuevas TCP.
    void onCierreConexionTCP();                                                                 // para la gestión del cliente desconectado bajo TCP.
    void leerComandosTCP();                                                                     // para la lectura del mensaje (texto) que llegue con las instrucciones sobre una conexión TCP.
    void leerComandosUDP();                                                                     // para la lectura del datagrama que llegue con las instrucciones sobre una conexión UDP.
    void procesarInstruccion(QString instruccion);                                              // para procesar la data recibida y convertirla en una instrucción que pueda interpretar la RenderApp.
    void on_btnIniciarServidor_clicked(bool checked);
    void detenerServidores();

};
#endif // MAINWINDOW_H
