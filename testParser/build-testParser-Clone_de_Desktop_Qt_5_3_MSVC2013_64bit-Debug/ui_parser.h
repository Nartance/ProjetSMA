/********************************************************************************
** Form generated from reading UI file 'parser.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARSER_H
#define UI_PARSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Parser
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Parser)
    {
        if (Parser->objectName().isEmpty())
            Parser->setObjectName(QStringLiteral("Parser"));
        Parser->resize(400, 300);
        menuBar = new QMenuBar(Parser);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        Parser->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Parser);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Parser->addToolBar(mainToolBar);
        centralWidget = new QWidget(Parser);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Parser->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Parser);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Parser->setStatusBar(statusBar);

        retranslateUi(Parser);

        QMetaObject::connectSlotsByName(Parser);
    } // setupUi

    void retranslateUi(QMainWindow *Parser)
    {
        Parser->setWindowTitle(QApplication::translate("Parser", "Parser", 0));
    } // retranslateUi

};

namespace Ui {
    class Parser: public Ui_Parser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARSER_H
