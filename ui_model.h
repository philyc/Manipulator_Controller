/********************************************************************************
** Form generated from reading UI file 'model.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODEL_H
#define UI_MODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Model
{
public:
    QWidget *centralwidget;
    QPushButton *btnOpen;
    QPushButton *btnClose;
    QGroupBox *grpTransmit;
    QLineEdit *edtData;
    QLabel *labId_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *labId;
    QLineEdit *edtId;
    QPushButton *btnSend;
    QTabWidget *tabWidget;
    QWidget *tabP2P;
    QWidget *tabAngle;
    QWidget *tabSingle;
    QPushButton *BtnEnable;
    QGroupBox *grpTest;
    QLineEdit *edtMoter1Angle;
    QLineEdit *edtMoter2Angle;
    QLineEdit *edtMoter3Angle;
    QLineEdit *edtMoter4Angle;
    QLineEdit *edtMoter5Angle;
    QLineEdit *edtMoter6Angle;
    QLineEdit *edtMoter1AddAngle;
    QLineEdit *edtMoter2AddAngle;
    QLineEdit *edtMoter3AddAngle;
    QLineEdit *edtMoter4AddAngle;
    QLineEdit *edtMoter5AddAngle;
    QLineEdit *edtMoter6AddAngle;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Model)
    {
        if (Model->objectName().isEmpty())
            Model->setObjectName(QString::fromUtf8("Model"));
        Model->resize(983, 595);
        centralwidget = new QWidget(Model);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btnOpen = new QPushButton(centralwidget);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));
        btnOpen->setGeometry(QRect(10, 10, 75, 23));
        btnClose = new QPushButton(centralwidget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(110, 10, 75, 23));
        grpTransmit = new QGroupBox(centralwidget);
        grpTransmit->setObjectName(QString::fromUtf8("grpTransmit"));
        grpTransmit->setGeometry(QRect(10, 40, 271, 121));
        edtData = new QLineEdit(grpTransmit);
        edtData->setObjectName(QString::fromUtf8("edtData"));
        edtData->setGeometry(QRect(50, 80, 201, 20));
        labId_2 = new QLabel(grpTransmit);
        labId_2->setObjectName(QString::fromUtf8("labId_2"));
        labId_2->setGeometry(QRect(10, 80, 31, 20));
        widget = new QWidget(grpTransmit);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 30, 240, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        labId = new QLabel(widget);
        labId->setObjectName(QString::fromUtf8("labId"));

        horizontalLayout->addWidget(labId);

        edtId = new QLineEdit(widget);
        edtId->setObjectName(QString::fromUtf8("edtId"));

        horizontalLayout->addWidget(edtId);

        btnSend = new QPushButton(widget);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));

        horizontalLayout->addWidget(btnSend);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 170, 581, 381));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabP2P = new QWidget();
        tabP2P->setObjectName(QString::fromUtf8("tabP2P"));
        tabWidget->addTab(tabP2P, QString());
        tabAngle = new QWidget();
        tabAngle->setObjectName(QString::fromUtf8("tabAngle"));
        tabWidget->addTab(tabAngle, QString());
        tabSingle = new QWidget();
        tabSingle->setObjectName(QString::fromUtf8("tabSingle"));
        BtnEnable = new QPushButton(tabSingle);
        BtnEnable->setObjectName(QString::fromUtf8("BtnEnable"));
        BtnEnable->setGeometry(QRect(30, 20, 91, 23));
        tabWidget->addTab(tabSingle, QString());
        grpTest = new QGroupBox(centralwidget);
        grpTest->setObjectName(QString::fromUtf8("grpTest"));
        grpTest->setGeometry(QRect(620, 30, 341, 171));
        edtMoter1Angle = new QLineEdit(grpTest);
        edtMoter1Angle->setObjectName(QString::fromUtf8("edtMoter1Angle"));
        edtMoter1Angle->setGeometry(QRect(30, 30, 51, 20));
        edtMoter2Angle = new QLineEdit(grpTest);
        edtMoter2Angle->setObjectName(QString::fromUtf8("edtMoter2Angle"));
        edtMoter2Angle->setGeometry(QRect(30, 70, 51, 20));
        edtMoter3Angle = new QLineEdit(grpTest);
        edtMoter3Angle->setObjectName(QString::fromUtf8("edtMoter3Angle"));
        edtMoter3Angle->setGeometry(QRect(30, 110, 51, 20));
        edtMoter4Angle = new QLineEdit(grpTest);
        edtMoter4Angle->setObjectName(QString::fromUtf8("edtMoter4Angle"));
        edtMoter4Angle->setGeometry(QRect(100, 30, 51, 20));
        edtMoter5Angle = new QLineEdit(grpTest);
        edtMoter5Angle->setObjectName(QString::fromUtf8("edtMoter5Angle"));
        edtMoter5Angle->setGeometry(QRect(100, 70, 51, 20));
        edtMoter6Angle = new QLineEdit(grpTest);
        edtMoter6Angle->setObjectName(QString::fromUtf8("edtMoter6Angle"));
        edtMoter6Angle->setGeometry(QRect(100, 110, 51, 20));
        edtMoter1AddAngle = new QLineEdit(grpTest);
        edtMoter1AddAngle->setObjectName(QString::fromUtf8("edtMoter1AddAngle"));
        edtMoter1AddAngle->setGeometry(QRect(180, 30, 51, 20));
        edtMoter2AddAngle = new QLineEdit(grpTest);
        edtMoter2AddAngle->setObjectName(QString::fromUtf8("edtMoter2AddAngle"));
        edtMoter2AddAngle->setGeometry(QRect(180, 70, 51, 20));
        edtMoter3AddAngle = new QLineEdit(grpTest);
        edtMoter3AddAngle->setObjectName(QString::fromUtf8("edtMoter3AddAngle"));
        edtMoter3AddAngle->setGeometry(QRect(180, 110, 51, 20));
        edtMoter4AddAngle = new QLineEdit(grpTest);
        edtMoter4AddAngle->setObjectName(QString::fromUtf8("edtMoter4AddAngle"));
        edtMoter4AddAngle->setGeometry(QRect(250, 30, 51, 20));
        edtMoter5AddAngle = new QLineEdit(grpTest);
        edtMoter5AddAngle->setObjectName(QString::fromUtf8("edtMoter5AddAngle"));
        edtMoter5AddAngle->setGeometry(QRect(250, 70, 51, 20));
        edtMoter6AddAngle = new QLineEdit(grpTest);
        edtMoter6AddAngle->setObjectName(QString::fromUtf8("edtMoter6AddAngle"));
        edtMoter6AddAngle->setGeometry(QRect(250, 110, 51, 20));
        Model->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Model);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 983, 23));
        Model->setMenuBar(menubar);
        statusbar = new QStatusBar(Model);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Model->setStatusBar(statusbar);

        retranslateUi(Model);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Model);
    } // setupUi

    void retranslateUi(QMainWindow *Model)
    {
        Model->setWindowTitle(QCoreApplication::translate("Model", "Model", nullptr));
        btnOpen->setText(QCoreApplication::translate("Model", "open", nullptr));
        btnClose->setText(QCoreApplication::translate("Model", "close", nullptr));
        grpTransmit->setTitle(QCoreApplication::translate("Model", "GroupBox", nullptr));
        edtData->setText(QCoreApplication::translate("Model", "4D 4F 00 00 01 00 00 00", nullptr));
        labId_2->setText(QCoreApplication::translate("Model", "Data", nullptr));
        labId->setText(QCoreApplication::translate("Model", "ID:", nullptr));
        edtId->setText(QCoreApplication::translate("Model", "00 00 03 01", nullptr));
        btnSend->setText(QCoreApplication::translate("Model", "send", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabP2P), QCoreApplication::translate("Model", "P2P", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAngle), QCoreApplication::translate("Model", "Angle", nullptr));
        BtnEnable->setText(QCoreApplication::translate("Model", "Enable moter", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabSingle), QCoreApplication::translate("Model", "Motor", nullptr));
        grpTest->setTitle(QCoreApplication::translate("Model", "GroupBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Model: public Ui_Model {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODEL_H
