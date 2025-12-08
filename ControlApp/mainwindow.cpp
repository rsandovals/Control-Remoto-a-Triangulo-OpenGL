#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>                                                             // nos permite manejar direcciones de red para conexiones sobre TCP / UDP.
#include <QDebug>                                                                   // nos permite mostrar mensajes en el terminal
#include <QIcon>                                                                    // nos pemite agregar icono a nuestra app.


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("ControlApp - Control Remoto de RenderApp");
    this->setFixedSize(this->size());
    this->setWindowIcon(QIcon(":/image/gamepad.png"));

    ui->opcionesConexionBox->insertItem(0,"seleccione protocolo...");
    ui->opcionesConexionBox->addItem("Transmission Control Protocol - TCP");
    ui->opcionesConexionBox->addItem("User Datagram Protocol - UDP");
    ui->opcionesConexionBox->setCurrentIndex(0);


    ui->ztGroupBox->setEnabled(false);
    ui->cfGroupBox->setEnabled(false);
    ui->ciGroupBox->setEnabled(false);
    ui->btnConectar->setEnabled(false);

    /* -- CREAMOS UN CONNECT QUE NOS PERMITA EVALUAR EL CAMBIO DE TEXTO DEL COMBOBOX DE PROTOCOLOS PARA HABILITAR EL BOTÓN "CONECTAR" -- */

    connect(ui->opcionesConexionBox, &QComboBox::currentTextChanged, this, [this](const QString &text)
        {
        bool esValido = (text == "Transmission Control Protocol - TCP" || text == "User Datagram Protocol - UDP");
        ui->btnConectar->setEnabled(esValido);
        });


    /* -- CREAMOS LOS CONNECT PARA "ACTUAR" ANTE EL CAMBIO EN LOS SLIDERS DE COLOR DE FONDO DEL TRIANGULO -- */

    connect(ui->sliderRed, &QSlider::valueChanged, this, &MainWindow::enviarColor);
    connect(ui->sliderGreen, &QSlider::valueChanged, this, &MainWindow::enviarColor);
    connect(ui->sliderBlue, &QSlider::valueChanged, this, &MainWindow::enviarColor);

     /* -- CREAMOS EL CONNECT PARA "ACTUAR" ANTE EL CAMBIO EN EL DIAL DE ROTACIÓN -- */

    connect(ui->dialRotacion, &QDial::valueChanged, this, &MainWindow::enviarRotacion);

     /* -- CREAMOS LOS CONNECT PARA "ACTUAR" ANTE EL CAMBIO EN LOS SLIDERS DE COLOR FONDO INTERIOR DEL TRIANGULO -- */

    connect(ui->sliderTriR, &QSlider::valueChanged, this, &MainWindow::enviarColorTriangulo);
    connect(ui->sliderTriG, &QSlider::valueChanged, this, &MainWindow::enviarColorTriangulo);
    connect(ui->sliderTriB, &QSlider::valueChanged, this, &MainWindow::enviarColorTriangulo);

    /* -- CREAMOS EL CONNECT PARA "ACTUAR" ANTE EL CAMBIO EN EL SLIDER DEL ZOOM INT-OUT AL TRIANGULO -- */

    connect(ui->sliderZoom, &QSlider::valueChanged, this, &MainWindow::enviarZoom);



}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btnConectar_clicked(bool checked)
{

    if(!checked)                                                                                                                                                        // boton presionado para desconectar (checked = false o 0)
    {
        if(m_socketUDP){agregarLog("ATENCIÓN: Se ha finalizado UDP");}

        limpiarSocket();                                                                                                                                                // borramos memoria y anulamos puntero de socket respectivo.
        ui->btnConectar->setText("conectar");                                                                                                                           // seteamos el texto del botón.
        ui->opcionesConexionBox->setEnabled(true);                                                                                                                      // habilitamos nuevamente la lista de protocolos.
        habilitarControles(false);                                                                                                                                      // deshabilitamos los controlBox para que no se puedan manipular sin conexión.

        QString opcionSeleccionada = ui->opcionesConexionBox->currentText();
        ui->btnConectar->setEnabled(opcionSeleccionada == "Transmission Control Protocol - TCP" || opcionSeleccionada == "User Datagram Protocol - UDP");
    }

    else
    {
        QString protocolo = ui->opcionesConexionBox->currentText();                                                                                                     // recuperamos el string (protocolo seleccionado) de la lista.
        ui->opcionesConexionBox->setEnabled(false);                                                                                                                     // deshabilitamos la lista de protocolos.

        if(protocolo == "Transmission Control Protocol - TCP")                                                                                                          // si elegimos usar TCP....
            {
                // instanciamos m_socketTCP para que gestionar la conexión TCP
                m_socketTCP = new QTcpSocket(this);

                // creamos las conexiones señal-slot para gestionar la conexión y desconexión TCP
                connect(m_socketTCP, &QTcpSocket::connected, this, &MainWindow::onConectado);
                connect(m_socketTCP, &QTcpSocket::disconnected, this, &MainWindow::onDesconectado);

                // para manejo de errores durante el proceso de conexión TCP
                connect(m_socketTCP, &QTcpSocket::errorOccurred, this, [&](QAbstractSocket::SocketError error)
                        {
                                switch(error)                                                                                                                           // usaremos la variable error para deciir el "tratamiento"
                                {
                                    case QAbstractSocket::ConnectionRefusedError:
                                        agregarLog("ERROR: El servidor rechazó la conexión.");
                                        agregarLog("SUGERENCIA: Verifique que el servidor esté encendido.");
                                        onDesconectado();
                                        break;

                                    case QAbstractSocket::HostNotFoundError:
                                        agregarLog("ERROR: No se encuentra el Host.");
                                        onDesconectado();
                                        break;

                                    case QAbstractSocket::RemoteHostClosedError:
                                        agregarLog("ATENCIÓN: El servidor cortó la conexión.");
                                        onDesconectado();
                                        break;

                                    default:
                                        QString casoDefault= QString ("ERROR " + QString::number(error) + "(DESCONOCIDO): " + m_socketTCP->errorString());
                                        agregarLog(casoDefault);
                                        onDesconectado();
                                }
                        });

                m_socketTCP->connectToHost(QHostAddress::LocalHost, 4040);
                ui->btnConectar->setText("conectando");
                agregarLog("ATENCIÓN: Conectando sobre protocolo TCP...");

            }
            else if(protocolo == "User Datagram Protocol - UDP")                                                                                                        // si elegimos usar UDP.....
            {
                // instanciamos m_socketUDP para que gestione la conexion UDP
                m_socketUDP = new QUdpSocket(this);
                agregarLog("ATENCIÓN: Se ha activado UDP");
                onConectado();
            }

    }
}

void MainWindow::onConectado()
{
    habilitarControles(true);
    ui->btnConectar->setText("desconectar");
        if(m_socketTCP) agregarLog("ATENCIÓN: Conectado al servidor .");

    agregarLog("ATENCIÓN: Ya puede enviar instrucciones mediante el Tablero de Control.");

}


void MainWindow::onDesconectado()
{
    limpiarSocket();
    ui->btnConectar->setText("conectar");
    ui->btnConectar->setChecked(false);
    habilitarControles(false);
    ui->opcionesConexionBox->setEnabled(true);
}


void MainWindow::enviarComando(QString instruccion)
{
    QString protocolo = ui->opcionesConexionBox->currentText();
    QByteArray comando = instruccion.toUtf8();

    if(protocolo == "Transmission Control Protocol - TCP")
    {
        if(m_socketTCP->state() == QAbstractSocket::ConnectedState)                                                                                             // si la conexion de socket se ha establecido y está lista para transferir datos...
        {
            m_socketTCP->write(comando);                                                                                                                        // generamos el mensaje con la instrucción
            m_socketTCP->flush();                                                                                                                               // vaciamos inmediatamente el buffer de salida.
        }
    }
    else if(protocolo == "User Datagram Protocol - UDP")
    {
        if(m_socketUDP)
        {
            m_socketUDP->writeDatagram(comando, QHostAddress::LocalHost, 4040);
            m_socketUDP->flush();
        }
        else
        {
            qDebug() << "No es posible enviar comandos sin socket UDP activo.";
        }

    }
}


void MainWindow::habilitarControles(bool estado)
{
    ui->ztGroupBox->setEnabled(estado);
    ui->cfGroupBox->setEnabled(estado);
    ui->ciGroupBox->setEnabled(estado);
}




void MainWindow::enviarColor()
{
                                                                                                                                                                // Formato de la instrucción de color fondo exterior triangulo: "COLOR:255,0,0"
    int r = ui->sliderRed->value();
    int g = ui->sliderGreen->value();
    int b = ui->sliderBlue->value();

                                                                                                                                                                // mostrar valores de cada slider en su respectiva label
    ui->labelRValue->setText(QString::number(r));
    ui->labelGValue->setText(QString::number(g));
    ui->labelBValue->setText(QString::number(b));

    QString instruccion= QString("COLOR:%1,%2,%3").arg(r).arg(g).arg(b);
    enviarComando(instruccion);
}



void MainWindow::enviarRotacion()
{
                                                                                                                                                                // Formato de la instrucción de rotación: "ROT:45"
    int angulo = ui->dialRotacion->value();

    QString instruccion = QString("ROT:%1").arg(angulo);
    enviarComando(instruccion);
}

void MainWindow::enviarColorTriangulo()
{
                                                                                                                                                                // Formato de la instrucción de color fondo interior triangulo: "TRICOLOR:r,g,b"
    int r = ui->sliderTriR->value();
    int g = ui->sliderTriG->value();
    int b = ui->sliderTriB->value();

                                                                                                                                                                // mostrar valores de cada slider en su respectiva label
    ui->labelWinRValue->setText(QString::number(r));
    ui->labelWinGValue->setText(QString::number(g));
    ui->labelWinBValue->setText(QString::number(b));

    QString instruccion = QString("TRICOLOR:%1,%2,%3").arg(r).arg(g).arg(b);
    enviarComando(instruccion);
}


void MainWindow::enviarZoom()
{
                                                                                                                                                                // Formato de ls instrucción de zoom in y zoom out al triangulo: "ZOOM:1.5"
    float zoom = ui->sliderZoom->value() / 100.0f;                                                                                                              // El slider 150 se convierte en 1.5
    QString instruccion = QString("ZOOM:%1").arg(zoom);
    enviarComando(instruccion);
}

void MainWindow::limpiarSocket()
{
    if(m_socketTCP)
    {
        m_socketTCP->disconnectFromHost();
        delete m_socketTCP;
        m_socketTCP = nullptr;
    }

    if(m_socketUDP)
    {
        delete m_socketUDP;
        m_socketUDP = nullptr;
    }
}

void MainWindow::agregarLog(QString mensaje)
{
    QString tiempo = QDateTime::currentDateTime().toString("HH:mm:ss");
    QString log = QString("[%1] - %2").arg(tiempo).arg(mensaje);
    ui->logTextEdit->append(log);

}
