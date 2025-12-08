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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "myglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    MyGLWidget *openGLWidget;
    QGroupBox *renderGroupBox;
    QLabel *label;
    QComboBox *modoConexionBox;
    QPushButton *btnIniciarServidor;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 653);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow, QWidget#centralwidget {\n"
"    background-color: #f0f2f5;  /* Gris muy suave, casi blanco */\n"
"    color: #333333;             /* Texto gris oscuro (no negro puro) */\n"
"}\n"
"/* 2. Etiquetas */\n"
"QLabel {\n"
"    color: #595875;            /* Texto oscuro para contraste */\n"
"    font-weight: bold;\n"
"	font-size: 12px\n"
"}\n"
"\n"
"/* 3. Entrada de datos */\n"
"QComboBox {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #c0c0c0;\n"
"    border-radius: 2px;\n"
"    padding: 4px;\n"
"    color: #333333;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #a09ebf;  /* Gris base */\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    padding: 5px;\n"
"    border-radius: 2px;         /* Casi rectangular */\n"
"\n"
"    /* EFECTO 3D: Luz arriba/izq, Sombra abajo/der */\n"
"    border-top: 2px solid #707070;    /* Borde claro */\n"
"    border-left: 2px solid #707070;   /* Borde claro */\n"
"    border-bottom: 2px solid #202020; /* Borde oscuro */\n"
"    border-right: 2px s"
                        "olid #202020;  /* Borde oscuro */\n"
"}\n"
"\n"
"/* Estado PRESIONADO: Invertimos los colores o aplanamos */\n"
"QPushButton:pressed {\n"
"    background-color: #72719f;        /* M\303\241s oscuro */\n"
"    border: 2px solid #202020;        /* Borde oscuro uniforme (hundido) */\n"
"    padding-top: 8px;                /* Truco visual: mueve el texto un poco abajo */\n"
"    padding-left: 8px;               /* mueve el texto un poco a la derecha */\n"
"}\n"
"\n"
"/* Estado Deshabilitado */\n"
"QPushButton:disabled {\n"
"    background-color: #E6EEFE;\n"
"    color: #888888;\n"
"    border: 1px solid #666666;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        openGLWidget = new MyGLWidget(centralwidget);
        openGLWidget->setObjectName("openGLWidget");
        openGLWidget->setGeometry(QRect(9, 9, 782, 521));
        renderGroupBox = new QGroupBox(centralwidget);
        renderGroupBox->setObjectName("renderGroupBox");
        renderGroupBox->setGeometry(QRect(10, 540, 781, 61));
        label = new QLabel(renderGroupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 21, 211, 20));
        QFont font;
        font.setBold(true);
        label->setFont(font);
        modoConexionBox = new QComboBox(renderGroupBox);
        modoConexionBox->setObjectName("modoConexionBox");
        modoConexionBox->setGeometry(QRect(240, 19, 331, 24));
        btnIniciarServidor = new QPushButton(renderGroupBox);
        btnIniciarServidor->setObjectName("btnIniciarServidor");
        btnIniciarServidor->setGeometry(QRect(600, 17, 121, 31));
        btnIniciarServidor->setCheckable(true);
        btnIniciarServidor->setChecked(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        renderGroupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("MainWindow", "seleccione un modo de conexi\303\263n:", nullptr));
        btnIniciarServidor->setText(QCoreApplication::translate("MainWindow", "iniciar servidor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
