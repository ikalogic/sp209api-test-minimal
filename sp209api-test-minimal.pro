TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp


win32 {
    DEFINES += OS_WIN
    DEFINES += __WINDOWS_TYPES__
    LIBS += sp209_api.dll
}
unix:!macx{
    LIBS += -lsp209_api
}

HEADERS += \
    ihwapi_common_types.h \
    sp209api.h \
    sp209api_types.h
