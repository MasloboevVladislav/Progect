QT += testlib
QT += core
QT -= gui
QT += network
QT += core gui sql
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_basictest.cpp \
    ../../server/database_u.cpp \
    ../../server/functions.cpp \
    ../../server/server.cpp

HEADERS += \
    ../../server/database_u.h \
    ../../server/functions.h \
    ../../server/server.h

FORMS +=

DISTFILES += \
    ../../server/data.db
