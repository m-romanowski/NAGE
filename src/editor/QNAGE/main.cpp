#include "editor/QNAGE/wrapper/enginebridge.h"
#include "editor/QNAGE/window/mainwindow.h"
#include "editor/QNAGE/window/renderwindow.h"
#include "editor/QNAGE/widget/glwidget.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

#include <iostream>
#include <cstdlib>

using namespace mr;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Dark styles
    QFile file(":/rc/styles/dark-blue.qss");
    if(!file.exists())
    {
        printf("Cannot to find styles, default path: ./resources/styles/dark.qss \n");
    }
    else
    {
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&file);
        app.setStyleSheet(ts.readAll());
    }

    nage::Game* game = new nage::Game;

    // Window setup
    qnage::MainWindow mainWindow;
    qnage::RenderWindow* window = new qnage::RenderWindow(&mainWindow);
    window->setupGLWidget(game);

    // Add gl window to main window and show.
    mainWindow.addWindow(window);
    mainWindow.show();

    // Setup QMessageCatch.
    qInstallMessageHandler(qnage::LogWidget::QMessageOutput);

    return app.exec();
}
