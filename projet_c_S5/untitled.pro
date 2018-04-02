TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    voiture.c \
    indicateurs.c \
    utils.c \
    game.c

HEADERS += \
    voiture.h \
    indicateurs.h \
    utils.h \
    game.h
