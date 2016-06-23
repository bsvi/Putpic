#-------------------------------------------------
#
# Project created by QtCreator 2015-09-16T13:09:38
#
#-------------------------------------------------

QT       += core gui network
win32:RC_ICONS += resources/screenshot.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = putpic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        runguard.cpp \
        settings.cpp \
    notifier.cpp    \
    tray-icon.cpp \
    optionsform.cpp \
    keys.cpp \
    HotkeyEditor.cpp \
    hookkeyboard.cpp \
    capture/ArrowTool.cpp \
    capture/CaptureForm.cpp \
    capture/LineTool.cpp \
    capture/myqgraphicsview.cpp \
    capture/PointerTool.cpp \
    capture/SelectTool.cpp \
    capture/TextTool.cpp \
    capture/ToolBase.cpp \
    capture/arrow.cpp \
    capture/drawingmenu.cpp \
    capture/HighlightedArea.cpp \
    capture/TextItem.cpp \
    upload/BsviRuUploader.cpp \
    upload/CustomServerUploader.cpp \
    upload/FileUploader.cpp \
    upload/ImgSaver.cpp \
    upload/IUploader.cpp \
    serversource.cpp



HEADERS  += mainwindow.h \
    runguard.h \
    settings.h \
    global.h \
    notifier.h  \
    tray-icon.h\
    optionsform.h \
    keys.h \
    HotkeyEditor.h \
    hookkeyboard.h \
    capture/ArrowTool.h \
    capture/CaptureForm.h \
    capture/LineTool.h \
    capture/myqgraphicsview.h \
    capture/PointerTool.h \
    capture/SelectTool.h \
    capture/TextTool.h \
    capture/ToolBase.h \
    capture/arrow.h \
    capture/drawingmenu.h \
    capture/HighlightedArea.h \
    capture/TextItem.h \
    upload/BsviRuUploader.h \
    upload/CustomServerUploader.h \
    upload/FileUploader.h \
    upload/ImgSaver.h \
    upload/IUploader.h \
    serversource.h


RESOURCES += \
    resources.qrc

FORMS += \
    optionsform.ui \
    capture/drawingmenu.ui
