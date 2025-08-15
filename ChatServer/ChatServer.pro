QT       += core network sql
QT += network
CONFIG   += c++17
TARGET = ChatServer
TEMPLATE = app

SOURCES += \
    main.cpp \
    server.cpp \
    clienthandler.cpp \
    database.cpp

HEADERS += \
    server.h \
    clienthandler.h \
    database.h
