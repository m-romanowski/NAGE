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
    QApplication a(argc, argv);

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
        a.setStyleSheet(ts.readAll());
    }

    /* Create a bridge between engine and world editor.
     * Bridge inherits from the Engine (base class) - see bridge.h for details.
     */

    NAGE::Game* game = new NAGE::Game;

    // Window setup
    QNAGE::MainWindow w;
    QNAGE::RenderWindow* window = new QNAGE::RenderWindow(&w);
    window->setupGLWidget(game);

    // Add gl window to main window and show.
    w.addWindow(window);
    w.show();

    // Setup QMessageCatch.
    qInstallMessageHandler(QNAGE::LogWidget::QMessageOutput);

    return a.exec();
}
