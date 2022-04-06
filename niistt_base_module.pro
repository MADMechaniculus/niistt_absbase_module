# TODO: REMOVE QMAKE, MIGRATE TO CMAKE !!!
# TODO: REMOVE QMAKE, MIGRATE TO CMAKE !!!
# TODO: REMOVE QMAKE, MIGRATE TO CMAKE !!!
# TODO: REMOVE QMAKE, MIGRATE TO CMAKE !!!
# TODO: REMOVE QMAKE, MIGRATE TO CMAKE !!!
# TODO: REMOVE QMAKE, MIGRATE TO CMAKE !!!
# TODO: REMOVE QMAKE, MIGRATE TO CMAKE !!!
# TODO: REMOVE QMAKE, MIGRATE TO CMAKE !!!
# TODO: REMOVE QMAKE, MIGRATE TO CMAKE !!!
# TODO: REMOVE QMAKE, MIGRATE TO CMAKE !!!

CONFIG -= qt

TEMPLATE = lib
DEFINES += NIISTT_BASE_MODULE_LIBRARY

CONFIG += c++14

SOURCES += \
    abstractbasemodule.cpp \
    telemetryflow.cpp \
    telemetrytypes.cpp

HEADERS += \
    niistt_base_module_global.h \
    abstractbasemodule.h \
    telemetryflow.h \
    telemetrytypes.h \
    typeimpls.h

# LIBS, INCLUDEPATH WIN32 =======================================

win32 {
INCLUDEPATH += \
        "C:\\include" \
        "C:\\include\\niistt_libs" \
        "C:\\include\\boost_1_76_0"

LIBS += \
        -L"C:\\libs" \
        -L"C:\\libs\\niistt_libs" \
        -L"C:\\libs\\libboost_1.76.0" \
        -llibboost_system-mgw7-mt-x32-1_76 \
        -llibboost_thread-mgw7-mt-x32-1_76 \
        -llibboost_date_time-mgw7-mt-x32-1_76 \
        -llibboost_json-mgw7-mt-x32-1_76 \
        -llibboost_chrono-mgw7-mt-x32-1_76 \
        -llibboost_atomic-mgw7-mt-x32-1_76
        -lpthread
}

# ===============================================================

# LIBS, INCLUDEPATH UNIX ========================================

unix {
INCLUDEPATH += \
        "/usr/include/boostlibs/boost_1_76_0"

LIBS += \
        -L"/usr/lib/boost/1_76_0" \
        -lboost_system \
        -lboost_thread \
        -lboost_date_time \
        -lboost_json \
        -lboost_chrono \
        -lpthread
}

# ===============================================================


# ================================================================
# Installs
unix {
headers.path = /usr/include/niistt_libs/$${TARGET}
headers.files = *.h *.hpp adc_ad9467_adcdac

target.path = /usr/lib/niistt_libs
}

win32 {
headers.path = "C://include//niistt_libs//$${TARGET}"
headers.files = *.h *.hpp adc_ad9467_adcdac

target.path = "C://libs//niistt_libs"
}

INSTALLS += headers target
# ================================================================
