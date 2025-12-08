/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *cfGroupBox;
    QLabel *labelR;
    QSlider *sliderBlue;
    QSlider *sliderRed;
    QLabel *labelB;
    QLabel *labelG;
    QSlider *sliderGreen;
    QLabel *labelRValue;
    QLabel *labelGValue;
    QLabel *labelBValue;
    QGroupBox *ciGroupBox;
    QSlider *sliderTriR;
    QSlider *sliderTriG;
    QSlider *sliderTriB;
    QLabel *labelWinR;
    QLabel *labelWinG;
    QLabel *labelWinB;
    QLabel *labelWinRValue;
    QLabel *labelWinGValue;
    QLabel *labelWinBValue;
    QGroupBox *groupBox_4;
    QPushButton *btnConectar;
    QComboBox *opcionesConexionBox;
    QLabel *conexionlabel;
    QTextEdit *logTextEdit;
    QGroupBox *controlGroupBox;
    QGroupBox *ztGroupBox;
    QLabel *labelMaxAng;
    QLabel *labelMinAng;
    QDial *dialRotacion;
    QSlider *sliderZoom;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(758, 616);
        MainWindow->setStyleSheet(QString::fromUtf8("/* 1. Fondo General */\n"
"QMainWindow, QWidget#centralwidget {\n"
"    background-color: #f0f2f5;  					/* Blanco palido (tinte grisaceo)  */\n"
"    color: #333333;            			 					/* Carb\303\263n oscuro */\n"
"}\n"
"\n"
"/* 2. Etiquetas */\n"
"QLabel {\n"
"    color: #595875;            								/* P\303\272rpura gris\303\241ceo */\n"
"    font-weight: bold;\n"
"	font-size: 12px\n"
"}\n"
"\n"
"/* 3. Contenedores */\n"
"QGroupBox {\n"
"    background-color: #ffffff; 					 		/* Blanco puro */\n"
"    border: 1px solid #d1d1d1;\n"
"	border-bottom: 2px solid #a09ebf;\n"
"	border-right: 2px solid #a09ebf;\n"
"    border-radius: 6px;\n"
"    margin-top: 10px;\n"
"    font-weight: bold;\n"
"    color: #72719f;             									/* Color de T\303\255tulo: Azul-magenta */\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center; 					/* T\303\255tulos centrado */\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* 4. Entradas */\n"
"QTextEdit, QLineEdit, QComboBox {\n"
""
                        "    background-color: #ffffff;									/* Blanco puro */\n"
"    border: 1px solid #c0c0c0;\n"
"    border-radius: 4px;\n"
"    padding: 4px;\n"
"    color: #333333;														/* Gris muy oscuro */\n"
"}\n"
"\n"
"/* Efecto al pasar el mouse por encima de los inputs */\n"
"QLineEdit:hover, QComboBox:hover {\n"
"    border: 1px solid #0078D7;\n"
"}\n"
"\n"
"QPushButton {\n"
"	/* Estado HABILITADO (normal) */\n"
"    background-color: #a09ebf;  								/* Violeta gris\303\241ceo */\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    padding: 5px;\n"
"    border-radius: 2px;         										/* Casi rectangular */\n"
"\n"
"    /* EFECTO 3D: Luz arriba/izq, Sombra abajo/der */\n"
"    border-top: 2px solid #707070;    						/* Borde claro */\n"
"    border-left: 2px solid #707070;   							/* Borde claro */\n"
"    border-bottom: 2px solid #202020; 					/* Borde oscuro */\n"
"    border-right: 2px solid #202020;  						/* Borde oscuro */\n"
"}\n"
"\n"
"/* Estado PRESIONADO: Invertimos los colores o aplanam"
                        "os */\n"
"QPushButton:pressed {\n"
"    background-color: #72719f;        	/* M\303\241s oscuro: Azul-magenta */\n"
"    border: 2px solid #202020;        		/* Borde gris oscuro oscuro (hundido) */\n"
"    padding-top: 8px;              /* para efecto visual:: texto un poco abajo */\n"
"    padding-left: 8px;               /* para efecto visual: texto un poco a la derecha */\n"
"}\n"
"\n"
"/* Estado DESHABILITADO */\n"
"QPushButton:disabled {\n"
"    background-color: #E6EEFE;			/* Azul claro gris\303\241ceo */\n"
"    color: #888888;									/* Gris medio */\n"
"    border: 1px solid #666666;				/* Gris oscuro */\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        cfGroupBox = new QGroupBox(centralwidget);
        cfGroupBox->setObjectName("cfGroupBox");
        cfGroupBox->setGeometry(QRect(400, 239, 301, 141));
        labelR = new QLabel(cfGroupBox);
        labelR->setObjectName("labelR");
        labelR->setGeometry(QRect(20, 38, 16, 16));
        sliderBlue = new QSlider(cfGroupBox);
        sliderBlue->setObjectName("sliderBlue");
        sliderBlue->setGeometry(QRect(50, 100, 171, 16));
        sliderBlue->setMaximum(255);
        sliderBlue->setValue(125);
        sliderBlue->setOrientation(Qt::Orientation::Horizontal);
        sliderRed = new QSlider(cfGroupBox);
        sliderRed->setObjectName("sliderRed");
        sliderRed->setGeometry(QRect(50, 40, 171, 16));
        sliderRed->setMaximum(255);
        sliderRed->setValue(125);
        sliderRed->setOrientation(Qt::Orientation::Horizontal);
        labelB = new QLabel(cfGroupBox);
        labelB->setObjectName("labelB");
        labelB->setGeometry(QRect(20, 98, 16, 16));
        labelG = new QLabel(cfGroupBox);
        labelG->setObjectName("labelG");
        labelG->setGeometry(QRect(20, 69, 16, 16));
        sliderGreen = new QSlider(cfGroupBox);
        sliderGreen->setObjectName("sliderGreen");
        sliderGreen->setGeometry(QRect(50, 70, 171, 16));
        sliderGreen->setMaximum(255);
        sliderGreen->setValue(125);
        sliderGreen->setOrientation(Qt::Orientation::Horizontal);
        labelRValue = new QLabel(cfGroupBox);
        labelRValue->setObjectName("labelRValue");
        labelRValue->setGeometry(QRect(240, 40, 31, 16));
        labelRValue->setStyleSheet(QString::fromUtf8("background-color:#ffffff;"));
        labelGValue = new QLabel(cfGroupBox);
        labelGValue->setObjectName("labelGValue");
        labelGValue->setGeometry(QRect(240, 70, 31, 16));
        labelGValue->setStyleSheet(QString::fromUtf8("background-color: #ffffff;"));
        labelBValue = new QLabel(cfGroupBox);
        labelBValue->setObjectName("labelBValue");
        labelBValue->setGeometry(QRect(240, 100, 31, 16));
        labelBValue->setStyleSheet(QString::fromUtf8("background-color: #ffffff;"));
        ciGroupBox = new QGroupBox(centralwidget);
        ciGroupBox->setObjectName("ciGroupBox");
        ciGroupBox->setGeometry(QRect(400, 391, 301, 141));
        sliderTriR = new QSlider(ciGroupBox);
        sliderTriR->setObjectName("sliderTriR");
        sliderTriR->setGeometry(QRect(52, 42, 171, 16));
        sliderTriR->setMaximum(255);
        sliderTriR->setSingleStep(1);
        sliderTriR->setValue(255);
        sliderTriR->setOrientation(Qt::Orientation::Horizontal);
        sliderTriG = new QSlider(ciGroupBox);
        sliderTriG->setObjectName("sliderTriG");
        sliderTriG->setGeometry(QRect(53, 70, 171, 16));
        sliderTriG->setMaximum(255);
        sliderTriG->setValue(255);
        sliderTriG->setOrientation(Qt::Orientation::Horizontal);
        sliderTriB = new QSlider(ciGroupBox);
        sliderTriB->setObjectName("sliderTriB");
        sliderTriB->setGeometry(QRect(54, 100, 171, 16));
        sliderTriB->setMaximum(255);
        sliderTriB->setValue(255);
        sliderTriB->setOrientation(Qt::Orientation::Horizontal);
        labelWinR = new QLabel(ciGroupBox);
        labelWinR->setObjectName("labelWinR");
        labelWinR->setGeometry(QRect(21, 41, 16, 16));
        labelWinG = new QLabel(ciGroupBox);
        labelWinG->setObjectName("labelWinG");
        labelWinG->setGeometry(QRect(21, 70, 16, 16));
        labelWinB = new QLabel(ciGroupBox);
        labelWinB->setObjectName("labelWinB");
        labelWinB->setGeometry(QRect(22, 99, 16, 16));
        labelWinRValue = new QLabel(ciGroupBox);
        labelWinRValue->setObjectName("labelWinRValue");
        labelWinRValue->setGeometry(QRect(240, 42, 31, 16));
        labelWinRValue->setStyleSheet(QString::fromUtf8("background-color: #ffffff"));
        labelWinGValue = new QLabel(ciGroupBox);
        labelWinGValue->setObjectName("labelWinGValue");
        labelWinGValue->setGeometry(QRect(240, 70, 31, 16));
        labelWinGValue->setStyleSheet(QString::fromUtf8("background-color: #ffffff"));
        labelWinBValue = new QLabel(ciGroupBox);
        labelWinBValue->setObjectName("labelWinBValue");
        labelWinBValue->setGeometry(QRect(240, 100, 31, 16));
        labelWinBValue->setStyleSheet(QString::fromUtf8("background-color: #ffffff;"));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(40, 10, 681, 181));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        groupBox_4->setFont(font);
        btnConectar = new QPushButton(groupBox_4);
        btnConectar->setObjectName("btnConectar");
        btnConectar->setGeometry(QRect(510, 40, 111, 31));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        btnConectar->setFont(font1);
        btnConectar->setStyleSheet(QString::fromUtf8(""));
        btnConectar->setCheckable(true);
        opcionesConexionBox = new QComboBox(groupBox_4);
        opcionesConexionBox->setObjectName("opcionesConexionBox");
        opcionesConexionBox->setGeometry(QRect(154, 43, 341, 24));
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(false);
        opcionesConexionBox->setFont(font2);
        conexionlabel = new QLabel(groupBox_4);
        conexionlabel->setObjectName("conexionlabel");
        conexionlabel->setGeometry(QRect(40, 44, 121, 20));
        QFont font3;
        font3.setBold(true);
        conexionlabel->setFont(font3);
        logTextEdit = new QTextEdit(groupBox_4);
        logTextEdit->setObjectName("logTextEdit");
        logTextEdit->setGeometry(QRect(30, 90, 611, 70));
        logTextEdit->setFont(font2);
        logTextEdit->setStyleSheet(QString::fromUtf8("border-color: 2px solid #053394;\n"
"background-color: #E6EEFE;\n"
""));
        logTextEdit->setReadOnly(true);
        controlGroupBox = new QGroupBox(centralwidget);
        controlGroupBox->setObjectName("controlGroupBox");
        controlGroupBox->setGeometry(QRect(40, 200, 681, 361));
        controlGroupBox->setFont(font);
        ztGroupBox = new QGroupBox(controlGroupBox);
        ztGroupBox->setObjectName("ztGroupBox");
        ztGroupBox->setGeometry(QRect(20, 40, 301, 291));
        labelMaxAng = new QLabel(ztGroupBox);
        labelMaxAng->setObjectName("labelMaxAng");
        labelMaxAng->setGeometry(QRect(184, 130, 31, 16));
        labelMaxAng->setFont(font3);
        labelMinAng = new QLabel(ztGroupBox);
        labelMinAng->setObjectName("labelMinAng");
        labelMinAng->setGeometry(QRect(98, 130, 16, 16));
        labelMinAng->setFont(font3);
        dialRotacion = new QDial(ztGroupBox);
        dialRotacion->setObjectName("dialRotacion");
        dialRotacion->setGeometry(QRect(88, 30, 121, 121));
        dialRotacion->setMaximum(360);
        sliderZoom = new QSlider(ztGroupBox);
        sliderZoom->setObjectName("sliderZoom");
        sliderZoom->setGeometry(QRect(59, 190, 191, 41));
        sliderZoom->setMinimum(10);
        sliderZoom->setMaximum(300);
        sliderZoom->setValue(100);
        sliderZoom->setOrientation(Qt::Orientation::Horizontal);
        dialRotacion->raise();
        labelMaxAng->raise();
        labelMinAng->raise();
        sliderZoom->raise();
        MainWindow->setCentralWidget(centralwidget);
        controlGroupBox->raise();
        cfGroupBox->raise();
        ciGroupBox->raise();
        groupBox_4->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 758, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Control App", nullptr));
        cfGroupBox->setTitle(QCoreApplication::translate("MainWindow", "COLOR FONDO TRIANGULO", nullptr));
        labelR->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        labelB->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        labelG->setText(QCoreApplication::translate("MainWindow", "G", nullptr));
        labelRValue->setText(QCoreApplication::translate("MainWindow", "125", nullptr));
        labelGValue->setText(QCoreApplication::translate("MainWindow", "125", nullptr));
        labelBValue->setText(QCoreApplication::translate("MainWindow", "125", nullptr));
        ciGroupBox->setTitle(QCoreApplication::translate("MainWindow", "COLOR INTERIOR TRIANGULO", nullptr));
        labelWinR->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        labelWinG->setText(QCoreApplication::translate("MainWindow", "G", nullptr));
        labelWinB->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        labelWinRValue->setText(QCoreApplication::translate("MainWindow", "255", nullptr));
        labelWinGValue->setText(QCoreApplication::translate("MainWindow", "255", nullptr));
        labelWinBValue->setText(QCoreApplication::translate("MainWindow", "255", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "TABLERO DE CONEXI\303\223N", nullptr));
        btnConectar->setText(QCoreApplication::translate("MainWindow", "conectar", nullptr));
        opcionesConexionBox->setCurrentText(QString());
        conexionlabel->setText(QCoreApplication::translate("MainWindow", "Tipo de Conexi\303\263n:", nullptr));
        controlGroupBox->setTitle(QCoreApplication::translate("MainWindow", "TABLERO DE CONTROL", nullptr));
        ztGroupBox->setTitle(QCoreApplication::translate("MainWindow", "ROTACI\303\223N Y ZOOM TRIANGULO", nullptr));
        labelMaxAng->setText(QCoreApplication::translate("MainWindow", "360\302\260", nullptr));
        labelMinAng->setText(QCoreApplication::translate("MainWindow", "0\302\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
