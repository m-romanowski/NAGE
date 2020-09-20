#include "editor/QNAGE/wrapper/enginebridge.h"
#include "editor/QNAGE/window/mainwindow.h"
#include "editor/QNAGE/window/renderwindow.h"
#include "editor/QNAGE/widget/glwidget.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

#include <iostream>
#include <cstdlib>

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

    NAGE::Game* game = new NAGE::Game;

    // Window setup
    QNAGE::MainWindow mainWindow;
    QNAGE::RenderWindow* window = new QNAGE::RenderWindow(&mainWindow);
    window->setupGLWidget(game);

    // Add gl window to main window and show.
    mainWindow.addWindow(window);
    mainWindow.show();

    // Setup QMessageCatch.
    qInstallMessageHandler(QNAGE::LogWidget::QMessageOutput);

    return app.exec();
}
