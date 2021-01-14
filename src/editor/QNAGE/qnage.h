#ifndef QNAGE_H_
#define QNAGE_H_

#include "engine/core/igame.h"
#include "editor/QNAGE/window/mainwindow.h"

namespace mr::qnage
{
    class QNAGE
    {
    public:
        ~QNAGE();

        void setup(nage::IGame* _game);

    private:
        MainWindow* mainWindow_;
    };
}

#endif // QNAGE_H_
