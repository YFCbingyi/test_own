#-------------------------------------------------
#
# Project created by QtCreator 2019-01-22T17:30:00
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NLP_CHEN
TEMPLATE = app

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
        main.cpp \
        mainwindow.cpp \
    nlp.cpp \
    xunshi.cpp \
    form.cpp \
    point_zb.cpp \
    config_json.cpp \
    debug_log.cpp \
    new_thread.cpp \
    nlp_test.cpp \
    uipython.cpp \
    fourssqlite.cpp \
    chrono_test.cpp \
    cplustest.cpp \
    mybind.cpp \
    my_template.cpp \
    my_thread.cpp \
    my_theta.cpp \
    my_vector.cpp \
    my_time.cpp \
    my_json.cpp \
    my_fstream.cpp \
    my_share_ptr.cpp \
    normalmode.cpp \
    planmode.cpp

HEADERS += \
        mainwindow.h \
    nlp.h \
    xunshi.h \
    form.h \
    point_zb.h \
    config_json.h \
    debug_log.h \
    new_thread.h \
    nlp_test.h \
    uipython.h \
    fourssqlite.h \
    chrono_test.h \
    xunshi.h \
    cplustest.h \
    mybind.h \
    BlockQueue.h \
    my_template.h \
    my_thread.h \
    my_theta.h \
    my_vector.h \
    my_time.h \
    my_json.h \
    my_fstream.h \
    my_share_ptr.h \
    mode.h

FORMS += \
        mainwindow.ui \
    form.ui \
    uipython.ui
LIBS += -ljsoncpp -lcurl -lpthread -lsqlite3

CONFIG += C++14

DISTFILES += \
    python_file.py
