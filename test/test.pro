CONFIG   += console
CONFIG   -= app_bundle

QT += testlib sql

include($$PWD/../config.pri)
QR_TEST_PRO = $$PWD/../../QrTest/source
QR_ORM_PRO = $$PWD/../source

CONFIG(debug, debug|release) {
    LIBS += \
        -L$$QR_TEST_PRO/../../build_debug_qrtest/ -lQrTestd \
        -L$$QR_ORM_PRO/../../build_debug_qrorm/ -lQrOrmd \
}

CONFIG(release, debug|release) {
    LIBS += \
        -L$$QR_TEST_PRO/../../build_release_qrtest/ -lQrTest \
        -L$$QR_ORM_PRO/../../build_release_qrorm/ -lQrOrm \
}

INCLUDEPATH += \
    $$PWD/include \
    $$QR_TEST_PRO\include \
    $$QR_ORM_PRO\include \
    $$QR_ORM_PRO\inl \

HEADERS += \
    include/tst_orm.h

SOURCES += \
    src/main.cpp \
    src/tst_orm.cpp

