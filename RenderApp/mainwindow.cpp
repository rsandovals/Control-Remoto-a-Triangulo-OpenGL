#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/image/cubo.png"));
    this->setWindowTitle("RenderApp - Triangulo OpenGL");
    this->setFixedSize(this->size());

    ui->modoConexionBox->insertItem(0,"seleccione protocolo...");
    ui->modoConexionBox->addItem("Transmission Control Protocol - TCP");
    ui->modoConexionBox->addItem("User Datagram Protocol - UDP");
    ui->modoConexionBox->setCurrentIndex(0);
    ui->modoConexionBox->setEditable(false);

    ui->btnIniciarServidor->setEnabled(false);

    connect(ui->modoConexionBox, &QComboBox::currentTextChanged, this, [this](const QString text)
        {
        bool opcionValida = (text == "Transmission Control Protocol - TCP" ||  text == "User Datagram Protocol - UDP");
        ui->btnIniciarServidor->setEnabled(opcionValida);
        ui->btnIniciarServidor->setChecked(false);
        });

    statusBar()->showMessage("Servidor detenido. seleccione un modo de conexión... ");


}



MainWindow::~MainWindow()
{
    delete ui;
}


    /* -- PARA LA GESTIÓN DE CONEXIONES TCP NUEVAS -- */

void MainWindow::onNuevaConexionTCP()
{
    m_socketClienteTCP = m_servidorTCP->nextPendingConnection();                                                                                                                                    // aceptamos la nueva conexión
    qDebug() << "Control Remoto conectado!..esperando instrucciones!.";                                                                                                                             // generamos mensaje en terminal cuando se genere la conexion remota.
    statusBar()->showMessage("Conexión remota exitosa!.. esperando instrucciones..");                                                                                                               // actualizamos el status del servicio de conexion tcp en la barra de estado

    connect(m_socketClienteTCP, &QTcpSocket::readyRead, this, &MainWindow::leerComandosTCP);                                                                                                        // "saltamos" a la función que gestionará las instrucciones que se reciban, una vez conectado el cliente.
    connect(m_socketClienteTCP, &QTcpSocket::disconnected, this, &MainWindow::onCierreConexionTCP);                                                                                                 // una vez finalizada la conexión, saltamos al slot que gestionará el mensaje y  eliminará el registro del socketCliente (liberamos esa memoria).
}


    /* -- PARA LA DESCONEXIÓN TCP -- */

void MainWindow::onCierreConexionTCP()
{
    qDebug() << "Control Remoto desconectado!";                                                                                                                                                     // generamos mensaje en terminal cuando se cierra la conexion remota.
    statusBar()->showMessage("Conexión remota finalizada!..Esperando nueva conexión a traves del puerto: " + QString::number(m_servidorTCP->serverPort()));                                         // actualizamos el status del servicio de conexion tcp en la barra de estado
    if(m_socketClienteTCP)
    {
        m_socketClienteTCP->deleteLater();                                                                                                                                                          // liberamos la memoria usada.
        m_socketClienteTCP = nullptr;                                                                                                                                                               // dejamos nulo (vacio) el puntero.
    }
}


    /* -- PARA LEER Y "TRADUCIR" LAS INSTRUCCIONES DE CONTROL SOBRE TCP QUE SE RECIBEN DESDE LA APP CLIENTE, BAJO FORMATO CLAVE:VALOR -- */

void MainWindow::leerComandosTCP()
{
    // rescatamos la información recibida y la formateamos...(la data recibida deberia incluir la palabra COLOR o ROT)
    QByteArray data = m_socketClienteTCP->readAll();                                                                                                                                                // Leemos todo lo que llegó
    QString comandoCompleto = QString::fromUtf8(data).trimmed();                                                                                                                                    // convertimos en una cadena de texto la data extraida. Nos aseguramos de eliminar espacios extras.
    qDebug() << "Comando recibido: " << comandoCompleto;                                                                                                                                            // imprimimos en terminal el comando extraido (así vemos que recibimos.)
    procesarInstruccion(comandoCompleto);


}

    /* -- PARA LEER Y "TRADUCIR" LAS INSTRUCCIONES DE CONTROL SOBRE UDP QUE SE RECIBEN DESDE LA APP CLIENTE, BAJO FORMATO CLAVE:VALOR -- */

void MainWindow::leerComandosUDP()
{
    while(m_socketUDP->hasPendingDatagrams())
    {
        QNetworkDatagram datagrama = m_socketUDP->receiveDatagram();
        QByteArray data = datagrama.data();
        QString comandoCompleto = QString::fromUtf8(data).trimmed();
        qDebug() << "Comando recibido: " << comandoCompleto;
        procesarInstruccion(comandoCompleto);
    }

}

    /* -- PARA LEER Y "TRADUCIR" LAS INSTRUCCIONES DE CONTROL SOBRE UDP QUE SE RECIBEN DESDE LA APP CLIENTE, BAJO FORMATO CLAVE:VALOR -- */

void MainWindow::procesarInstruccion(QString instruccion)
{

    // ahora separaremos la cadena de texto para encontrar las instrucciones..
    QStringList partes = instruccion.split(":");                                                                                                                                                    // busca el caracter : y divide el texto en n partes. Esto generará un array!.

    if(partes.size() < 2) return;                                                                                                                                                                   // comprobamos el total de partes rescatadas post split. si son menos de 2, se considera que el comando esta incompleto.
    QString clave = partes[0].toUpper();                                                                                                                                                            // guardamos como clave el primer string, como debería ser el nombre de la instrucción (COLOR o ROT), nos aseguramos de ponerlo en mayuscula
    QString valor = partes[1];                                                                                                                                                                      // guardamos como valro el resto del string que deberia contener los valores a usar para modificar color o angulo de rotación.

    // ahora, evaluamos que categoria recibimos como clave: COLOR o ROT.
    if(clave == "COLOR")
    {
        QStringList rgb = valor.split(",");                                                                                                                                                         // dividimos el string "valor" tomando como referencia de división el caracter ","
        if(rgb.size()==3)                                                                                                                                                                           // nos aseguramos que, al menos, el array contenga 3 valores para formar el color
        {
            float r = (rgb[0].toFloat())/255.0f;                                                                                                                                                    // convertimos el primero valor del array rgb en float y lo guardamos en una nueva variable..
            float g = (rgb[1].toFloat())/255.0f;                                                                                                                                                    // seguimos con el siguiente..
            float b = (rgb[2].toFloat())/255.0f;                                                                                                                                                    // y el último.

            ui->openGLWidget->setColorFiltro(r,g,b);                                                                                                                                                // finalmente le pasamos los valores al slot setColorFiltro()..
        }
    }
    else if(clave == "ROT")
    {
        float angulo = valor.toFloat();                                                                                                                                                             // tomamos valor, asumiendo que contiene solo un valor numérico

        ui->openGLWidget->setRotation(angulo);                                                                                                                                                      // finalmente s elo pasamos al slot setRotation()...
    }

    else if (clave == "TRICOLOR")
    {
        QStringList rgb = valor.split(",");
        if (rgb.size() == 3) {
            float r = rgb[0].toFloat() / 255.0f;
            float g = rgb[1].toFloat() / 255.0f;
            float b = rgb[2].toFloat() / 255.0f;
            ui->openGLWidget->setColorTriangulo(r, g, b);
        }
    }

    else if (clave == "ZOOM")
    {
        float zoom = valor.toFloat();
        ui->openGLWidget->setZoom(zoom);
    }

    qDebug() << "Comando ejecutado:" << instruccion;
}


void MainWindow::detenerServidores()
{
    if(m_servidorTCP)
    {
        if(m_servidorTCP->isListening())
        {
            m_servidorTCP->close();
            delete m_servidorTCP;
            m_servidorTCP = nullptr;
            qDebug() << "Servicio TCP detenido.";
        }
    }

    if(m_socketUDP)
    {
        m_socketUDP->close();
        delete m_socketUDP;
        m_socketUDP = nullptr;
        qDebug() << "Servicio UDP detenido.";
    }

    statusBar()->showMessage("Servidor detenido");
    ui->modoConexionBox->setEnabled(true);
    ui->btnIniciarServidor->setText("iniciar servidor");
}

void MainWindow::on_btnIniciarServidor_clicked(bool checked)
{
    if(!checked)
    {
        detenerServidores();
        statusBar()->showMessage("Servidor detenido..........");
        ui->modoConexionBox->setEnabled(true);
        ui->btnIniciarServidor->setText("iniciar servidor");

        QString seleccion = ui->modoConexionBox->currentText();
        ui->btnIniciarServidor->setEnabled(seleccion == "Transmission Control Protocol - TCP" ||  seleccion == "User Datagram Protocol - UDP");
        return;
    }
    else
    {
        QString protocolo = ui->modoConexionBox->currentText();
        ui->modoConexionBox->setEnabled(false);
        ui->btnIniciarServidor->setText("detener servidor");

        if(protocolo == "Transmission Control Protocol - TCP")
        {
            m_servidorTCP = new QTcpServer(this);
            connect(m_servidorTCP, &QTcpServer::newConnection, this, &MainWindow::onNuevaConexionTCP);

                if(m_servidorTCP->listen(QHostAddress::Any, 4040))                                                                                                                                              // nuestro servidor estará escuchando en todas las interfaces de red a traves del puerto 4040
                {
                    qDebug() << "Modo TCP Listo: Servidor esperando conexión a traves del puerto: " << m_servidorTCP->serverPort();                                                                             // generamos mensaje en terminal cuando se inicie correctamente el servidor tcp
                    statusBar()->showMessage("Modo TCP activado: Esperando conexión de control a través del puerto: " + QString::number(m_servidorTCP->serverPort()));                                          // actualizamos el status del servicio de conexion tcp en la barra de estado
                }
                else
                {
                    qDebug() << "ERROR EN SERVIDOR: No se pudo iniciarl el servicio TCP.";
                    ui->btnIniciarServidor->setChecked(false);
                    ui->modoConexionBox->setEnabled(true);
                }
        }
        else if(protocolo == "User Datagram Protocol - UDP")
        {
            m_socketUDP = new QUdpSocket(this);
            if(m_socketUDP->bind(QHostAddress::AnyIPv4, 4040))
            {
                qDebug() << "Servicio UDP Listo. Escuchando en puerto: " << m_socketUDP->localPort();
                statusBar()->showMessage("Modo UDP activado: Esperando conexión de control a través del puerto: " + QString::number(m_socketUDP->localPort()));
                connect(m_socketUDP, &QUdpSocket::readyRead, this, &MainWindow::leerComandosUDP);
            }
            else
            {
                qDebug() << "ERROR EN SERVIDOR: No se pudo iniciar el servicio UDP.";
                ui->btnIniciarServidor->setChecked(false);
                ui->modoConexionBox->setEnabled(true);
            }
        }
    }
}

