#-------------------------------------------------
#
# Project created by QtCreator 2019-06-17T15:51:43
#
#-------------------------------------------------

# BUILD CONFIG
CONFIG += c++17

ROOT_DIRECTORY = $$PWD/../../../
LIB_DIRECTORY = $${ROOT_DIRECTORY}/lib
SRC_DIRECTORY = $${ROOT_DIRECTORY}/src
BUILD_DIRECTORY = $${ROOT_DIRECTORY}/build
EXEC_DIRECTORY = $${BUILD_DIRECTORY}

DESTDIR = $${EXEC_DIRECTORY}
OBJECTS_DIR = $${BUILD_DIRECTORY}
MOC_DIR = $${BUILD_DIRECTORY}
RCC_DIR = $${BUILD_DIRECTORY}
TARGET = QNAGE
TEMPLATE = app

# QT
QT += core gui
QT += opengl

# LIBS
LIBS += -lglfw3 -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL -lpthread -ldl

# INCLUDE PATHS
INCLUDEPATH += $${LIB_DIRECTORY}
INCLUDEPATH += $${SRC_DIRECTORY}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    $${LIB_DIRECTORY}/glad/glad.c \
    ../../engine/render/collision/aabb.cpp \
    ../../engine/render/collision/bs.cpp \
    ../../engine/render/collision/collisionplane.cpp \
    ../../engine/render/lod/cdlod/cdlod.cpp \
    ../../engine/render/lod/cdlod/cdlodnode.cpp \
    ../../engine/render/lod/cdlod/cdlodquadtree.cpp \
    ../../engine/render/lod/cdlod/cdlodselectednode.cpp \
    ../../engine/render/lod/geoclipmaps/geometryclipmap.cpp \
    ../../engine/world/light/sun.cpp \
    ../../engine/world/primitives/gridmesh.cpp \
    ../../engine/world/primitives/sphere.cpp \
    ../../engine/world/terrain/cdlodterrain.cpp \
    ../../engine/world/terrain/cdlodterrainchunk.cpp \
    ../../engine/world/terrain/iterrain.cpp \
    dialog/dialog.cpp \
    dialog/projectdialog.cpp \
    log/logwidget.cpp \
    log/messagehandler.cpp \
    log/threadlogstream.cpp \
    settings/buildandrunsettings.cpp \
    settings/enginesettings.cpp \
    settings/environmentsettings.cpp \
    settings/settingslayout.cpp \
    settings/settingsnavigation.cpp \
    ui/custombutton.cpp \
    ui/maintool.cpp \
    ui/tabbar.cpp \
    ui/tabwidget.cpp \
    widget/glwidget.cpp \
    widget/mainwidget.cpp \
    widget/settingswidget.cpp \
    widget/vkwidget.cpp \
    widget/welcomewidget.cpp \
    window/framelesswindow.cpp \
    window/mainwindow.cpp \
    window/renderwindow.cpp \
    main.cpp \
    ../../common/errormanager.cpp \
    ../../common/exception.cpp \
    ../../common/log.cpp \
    ../../engine/components/camera/camera.cpp \
    ../../engine/components/image.cpp \
    ../../engine/components/timer.cpp \
    ../../engine/core/coreengine.cpp \
    ../../engine/core/scene/scenemanager.cpp \
    ../../engine/core/scene/scenenode.cpp \
    ../../engine/core/igame.cpp \
    ../../engine/io/iwindow.cpp \
    ../../engine/io/keyboard.cpp \
    ../../engine/io/mouse.cpp \
    ../../engine/io/window.cpp \
    ../../engine/io/X11.cpp \
    ../../engine/render/model/material.cpp \
    ../../engine/render/model/materialtype.cpp \
    ../../engine/render/model/model.cpp \
    ../../engine/render/model/mesh.cpp \
    ../../engine/render/model/texture.cpp \
    ../../engine/world/skybox/skybox.cpp \
    ../../engine/world/light/directionallight.cpp \
    ../../engine/world/light/pointlight.cpp \
    ../../engine/world/light/light.cpp \
    ../../engine/render/color.cpp \
    ../../engine/render/glrenderengine.cpp \
    ../../engine/render/iobject.cpp \
    ../../engine/render/irenderengine.cpp \
    ../../engine/render/projection.cpp \
    ../../engine/render/shader.cpp \
    ../../engine/render/transform.cpp \
    ../../engine/util/objectloader.cpp \
    ../../game/game.cpp \
    ../../engine/world/terrain/heightmap.cpp \
    ../../engine/world/primitives/primitive.cpp \
    ../../engine/world/primitives/plane.cpp \
    ../../engine/world/primitives/cube.cpp \
    ../../engine/render/culling/frustumculling.cpp

HEADERS += \
    $${LIB_DIRECTORY}/glad/glad.h \
    $${LIB_DIRECTORY}/STB/stb_image.h \
    $${LIB_DIRECTORY}/KHR/khrplatform.h \
    ../../engine/render/collision/aabb.h \
    ../../engine/render/collision/bs.h \
    ../../engine/render/collision/collisionplane.h \
    ../../engine/render/lod/cdlod/cdlod.h \
    ../../engine/render/lod/cdlod/cdlodnode.h \
    ../../engine/render/lod/cdlod/cdlodquadtree.h \
    ../../engine/render/lod/cdlod/cdlodselectednode.h \
    ../../engine/render/lod/cdlod/cdlodsettings.h \
    ../../engine/render/lod/geoclipmaps/geometryclipmap.h \
    ../../engine/render/vertexhelper.h \
    ../../engine/util/size.h \
    ../../engine/world/light/sun.h \
    ../../engine/world/primitives/gridmesh.h \
    ../../engine/world/primitives/sphere.h \
    ../../engine/world/procedural/diamondsquare.h \
    ../../engine/world/procedural/lsystem.h \
    ../../engine/world/terrain/cdlodterrain.h \
    ../../engine/world/terrain/cdlodterrainchunk.h \
    ../../engine/world/terrain/iterrain.h \
    dialog/dialog.h \
    dialog/projectdialog.h \
    log/logwidget.h \
    log/messagehandler.h \
    log/threadlogstream.h \
    settings/buildandrunsettings.h \
    settings/enginesettings.h \
    settings/environmentsettings.h \
    settings/settingslayout.h \
    settings/settingsnavigation.h \
    ui/custombutton.h \
    ui/maintool.h \
    ui/tabbar.h \
    ui/tabwidget.h \
    widget/glwidget.h \
    widget/mainwidget.h \
    widget/setingswidget.h \
    widget/vkwidget.h \
    widget/welcomewidget.h \
    window/framelesswindow.h \
    window/mainwindow.h \
    window/renderwindow.h \
    ../../common/errormanager.h \
    ../../common/exception.h \
    ../../common/log.h \
    ../../common/macro.h \
    ../../common/stringextension.h \
    ../../engine/components/camera/camera.h \
    ../../engine/components/image.h \
    ../../engine/components/timer.h \
    ../../engine/components/const.h \
    ../../engine/components/types.h \
    ../../engine/core/coreengine.h \
    ../../engine/core/scene/scenemanager.h \
    ../../engine/core/scene/scenenode.h \
    ../../engine/core/igame.h \
    ../../engine/io/input.h \
    ../../engine/io/iwindow.h \
    ../../engine/io/key.h \
    ../../engine/io/keyboard.h \
    ../../engine/io/mouse.h \
    ../../engine/io/mousebutton.h \
    ../../engine/io/window.h \
    ../../engine/io/X11.h \
    ../../engine/math/NAGEMath/nagemathcommon.h \
    ../../engine/math/NAGEMath/nagemathmatrix.h \
    ../../engine/math/NAGEMath/nagemathquaternion.h \
    ../../engine/math/NAGEMath/nagemathvector.h \
    ../../engine/render/model/material.h \
    ../../engine/render/model/materialtype.h \
    ../../engine/render/model/mesh.h \
    ../../engine/render/model/model.h \
    ../../engine/render/model/texture.h \
    ../../engine/world/skybox/skybox.h \
    ../../engine/world/light/directionallight.h \
    ../../engine/world/light/pointlight.h \
    ../../engine/world/light/light.h \
    ../../engine/render/color.h \
    ../../engine/render/glrenderengine.h \
    ../../engine/render/vertex.h \
    ../../engine/render/iobject.h \
    ../../engine/render/irenderengine.h \
    ../../engine/render/projection.h \
    ../../engine/render/shader.h \
    ../../engine/render/transform.h \
    ../../engine/util/objectloader.h \
    ../../engine/wrapper/glwrapper.h \
    ../../game/game.h \
    ../../engine/util/stl.h \
    ../../engine/util/random.h \
    ../../engine/world/terrain/heightmap.h \
    ../../engine/world/primitives/primitive.h \
    ../../engine/world/primitives/plane.h \
    ../../engine/world/primitives/cube.h \
    ../../engine/render/culling/frustumculling.h \
    ../../engine/world/procedural/perlinnoise.h \
    ../../engine/world/procedural/simplexnoise.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/rc.qrc

# GLFW LIB
win32:CONFIG(release, debug|release): LIBS += -L$${LIB_DIRECTORY}/glfw/lib/release/ -lglfw3
else:win32:CONFIG(debug, debug|release): LIBS += -L$${LIB_DIRECTORY}/glfw/lib/debug/ -lglfw3
else:unix: LIBS += -L$${LIB_DIRECTORY}/glfw/lib/ -lglfw3

INCLUDEPATH += $${LIB_DIRECTORY}/glfw/include
DEPENDPATH += $${LIB_DIRECTORY}/glfw/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $${LIB_DIRECTORY}/glfw/lib/release/libglfw3.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $${LIB_DIRECTORY}/glfw/lib/debug/libglfw3.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $${LIB_DIRECTORY}/glfw/lib/release/glfw3.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $${LIB_DIRECTORY}/glfw/lib/debug/glfw3.lib
else:unix: PRE_TARGETDEPS += $${LIB_DIRECTORY}/glfw/lib/libglfw3.a
