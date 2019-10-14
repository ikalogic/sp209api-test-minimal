TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

contains(QT_ARCH, i386) {
    ARCHVER = 32

} else {
    ARCHVER = 64
}


win32 {
    #DEFINES += IMPORT_API_WIN
    DEFINES += OS_WIN
    DEFINES += __WINDOWS_TYPES__
    LIBS += sp209_api.dll
}

######################## Dependy management: copy files to output DIR before build
#copy_ftdi.commands = $(COPY_FILE) \"$$shell_path($$PWD\\dependencies\\ftd2xx_$${ARCHVER}.lib.rename)\" \"$$shell_path($$OUT_PWD\\ftd2xx.lib)\"
copy_sp209.commands = $(COPY_FILE) \"$$shell_path($$PWD\\dependencies\\sp209_api_$${ARCHVER}.dll.rename)\" \"$$shell_path($$OUT_PWD\\sp209_api.dll)\"
first.depends = $(first) copy_ftdi copy_sp209
export(first.depends)
export(copy_sp209.commands)
QMAKE_EXTRA_TARGETS += first copy_ftdi copy_sp209
