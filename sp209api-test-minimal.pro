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


API_BIN_PATH = "$$OUT_PWD\\..\\scanaduinoApi"
######################## Dependy management: copy files to output DIR before build
win32 {
    #DEFINES += IMPORT_API_WIN
    DEFINES += OS_WIN
    DEFINES += __WINDOWS_TYPES__
    LIBS += sp209_api.dll
    copy_sp209.commands = $(COPY_FILE) \"$$shell_path($$PWD\\dependencies\\sp209_api_$${ARCHVER}.dll.rename)\" \"$$shell_path($$OUT_PWD\\sp209_api.dll)\"
}
unix:!macx{
    LIBS += -L$$OUT_PWD/../scanaduinoApi/ -lsp209_ap
    copy_sp209.commands = $(COPY_FILE) \"$$shell_path($$PWD\\dependencies\\libsp209_api.so.rename)\" \"$$shell_path($$OUT_PWD)\\libsp209_api.so\"
}

macx{
    LIBS += -L$$OUT_PWD/../scanaduinoApi/ -lsp209_ap
    copy_sp209.commands = $(COPY_FILE) \"$$shell_path($$PWD\\dependencies\\libsp209_api.dylib.rename)\" \"$$shell_path($$OUT_PWD)\\libsp209_api.dylib\"
}

first.depends = $(first) copy_sp209
export(first.depends)
export(copy_sp209.commands)
QMAKE_EXTRA_TARGETS += first copy_ftdi copy_sp209













#Automatically copy lib binaries
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
