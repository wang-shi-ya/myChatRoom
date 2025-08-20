QT       += core gui network sql widgets
CONFIG   += c++17
TARGET = ChatClient
TEMPLATE = app

SOURCES += \
    ImageLabel.cpp \
    ProfileDialog.cpp \
    main.cpp \
    client.cpp \
    loginwindow.cpp \
    chatwindow.cpp

HEADERS += \
    ImageLabel.h \
    ProfileDialog.h \
    client.h \
    loginwindow.h \
    chatwindow.h

FORMS += \
    ProfileDialog.ui \
    loginwindow.ui \
    chatwindow.ui
