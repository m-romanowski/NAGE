#include "editor/QNAGE/window/mainwindow.h"
#include "editor/QNAGE/window/renderwindow.h"
#include "editor/QNAGE/widget/glwidget.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

#include <iostream>

using namespace mr;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Dark styles
    QFile file(":/rc/styles/dark-blue.qss");
    if(!file.exists())
    {
        std::cout << "Cannot to find styles, default path: ./resources/styles/dark.qss" << std::endl;
    }
    else
    {
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&file);
        app.setStyleSheet(ts.readAll());
    }

    nage::IGame* game = new nage::Game;

    qnage::MainWindow mainWindow;
    qnage::RenderWindow* renderWindow = new qnage::RenderWindow(&mainWindow);
    renderWindow->setupGLWidget(game);

    // Add gl window to main window and show.
    mainWindow.addWindow(renderWindow);
    mainWindow.show();

    // Setup QMessageCatch.
    qInstallMessageHandler(qnage::LogWidget::QMessageOutput);

    return app.exec();
}
