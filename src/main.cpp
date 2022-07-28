#include "logcplus/src/logcplus.h"
#include "editor/QNAGE/qnage.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

#include <iostream>

using namespace mr;

int main(int argc, char *argv[])
{
    auto logManager = dev::marcinromanowski::logcplus::LogManager::instance();
    logManager->setLogLevel(dev::marcinromanowski::logcplus::Logger::LogLevel::Debug);
    logManager->setLogMode(dev::marcinromanowski::logcplus::Logger::LogMode::Console);
    logManager->disableDirectoryWatcher();
    logManager->disableFileWatcher();
    logManager->initialize();

    QApplication app(argc, argv);

    // Dark styles
    QFile file(":/rc/styles/dark-blue.qss");
    if(!file.exists())
    {
        std::cout << "Cannot to find styles, default path: editor/QNAGE/resources/styles/dark.qss" << std::endl;
    }
    else
    {
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&file);
        app.setStyleSheet(ts.readAll());
    }

    nage::IGame* game = new nage::Game;
    qnage::QNAGE* editor = new qnage::QNAGE;
    editor->setup(game);

    // Setup QMessageCatch.
    qInstallMessageHandler(qnage::LogWidget::QMessageOutput);

    return app.exec();
}
