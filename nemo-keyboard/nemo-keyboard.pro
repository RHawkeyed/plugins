include(../config.pri)

TEMPLATE = lib
TARGET = dummy

PLUGIN_FILE = nemo-keyboard.qml
PLUGIN_DATA = org

plugin.files = $${PLUGIN_FILE}
plugin.CONFIG += no_check_exist
plugin.path = $${MALIIT_PLUGINS_DIR}

other_files.files = $${PLUGIN_DATA}/
other_files.CONFIG += no_check_exist
other_files.path = $${MALIIT_PLUGINS_DATA_DIR}

QMAKE_CLEAN += libdummy.so*
INSTALLS += plugin other_files

msvc{
    QMAKE_LFLAGS += /NOENTRY #msvc defaults to main entry, but this dll doesn't have one
}
