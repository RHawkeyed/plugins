include(../config.pri)

VERSION = 0.2.0
TARGET = $${MALIIT_KEYBOARD_TARGET}
TEMPLATE = lib
QT = core
CONFIG += staticlib

DEFINES += MALIIT_KEYBOARD_LIB_BUILDING

include(models/models.pri)
include(logic/logic.pri)
include(parser/parser.pri)

HEADERS += coreutils.h \
    common.h
SOURCES += coreutils.cpp

include(../word-prediction.pri)
