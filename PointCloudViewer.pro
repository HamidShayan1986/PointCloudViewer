QT       += core gui widgets opengl
CONFIG += c++11
##########################################################################################
SOURCES += \
    Camera.cpp \
    PointCloud.cpp \
    ShaderPrograms.cpp \
    ViewerWidget.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Camera.h \
    MainWindow.h \
    PointCloud.h \
    ShaderPrograms.h \
    ViewerWidget.h

FORMS += \
    MainWindow.ui
######################################################
RESOURCES += \
    Resource/Shader/CommonShaders.qrc
