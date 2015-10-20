include(../config.pri)

TARGET = dummy
TEMPLATE = lib

qml.path = $$MALIIT_KEYBOARD_DATA_DIR
qml.files = *.qml

INSTALLS += qml
OTHER_FILES += \
    maliit-keyboard.qml \
    maliit-keyboard-extended.qml \
    maliit-magnifier.qml \
    Keyboard.qml \

msvc{
    QMAKE_LFLAGS += /NOENTRY #msvc defaults to main entry, but this dll doesn't have one
}