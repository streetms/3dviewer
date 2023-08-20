QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
LIBS += -L./../build/libs -l3D -lmatrix
CONFIG += c++17 debug
DESTDIR += ../build/
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    app.cpp \
    canvas.cpp \
    main.cpp \
    mainwindow.cpp \
    settingwindow.cpp

HEADERS += \
    app.h \
    canvas.h \
    mainwindow.h \
    settingwindow.h

FORMS += \
    mainwindow.ui \
    settingwindow.ui

OBJECTS_DIR =  $$DESTDIR/obj
MOC_DIR =  $$DESTDIR/moc
UI_DIR = $$DESTDIR/ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
