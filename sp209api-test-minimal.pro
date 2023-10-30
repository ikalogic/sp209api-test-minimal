TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp


win32 {
    DEFINES += OS_WIN
    DEFINES += __WINDOWS_TYPES__

    win32-msvc* {
        LIBS += -lsp209_api
    }
    equals(QMAKE_CXX, g++) {
        LIBS += sp209_api.dll
    }
}
unix: LIBS += -L$$PWD/dependencies/linux/ -lsp209_api
macx: LIBS += -L$$PWD/dependencies/mac/ -lsp209_api.1.0.0

HEADERS += \
    ihwapi_common_types.h \
    sp209api.h \
    sp209api_types.h

