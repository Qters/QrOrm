QT       += sql

QT       -= gui

DEFINES += QRORM_LIBRARY

TEMPLATE = lib

TARGET = QrOrm

include($$PWD/../config.pri)
include($$PWD/../output.pri)

INCLUDEPATH += \
    $$PWD/inl \
    $$PWD/include \

HEADERS += \
    include/qrorm_global.h \
    include/entity/qrsqlconfig.h \
    include/entity/qrsqltable.h \
    include/entity/qrsqltableinfo.h \
    include/entity/qrsqldatabase.h \
    include/entity/qrsqldatabaseerror.h \
    include/entity/qrsqlquery.h \
    include/generator/element/qrsqlcompare.h \
    include/generator/element/qrsqlelement.h \
    include/generator/element/qrsqlelementtemp.h \
    include/generator/element/qrsqlemptytext.h \
    include/generator/element/qrsqlexpression.h \
    include/generator/element/qrsqlin.h \
    include/generator/element/qrsqlisbetween.h \
    include/generator/element/qrsqlisnull.h \
    include/generator/element/qrsqllimit.h \
    include/generator/element/qrsqlsort.h \
    include/generator/qrdeletesql.h \
    include/generator/qrinsertsql.h \
    include/generator/qrselectsql.h \
    include/generator/qrsqlgenerator.h \
    include/generator/qrupdatesql.h \
    include/qrdbresultsguard.h \
    include/qrsqlhelper.h \
    include/generator/qrcreatesql.h

SOURCES += \
    inl/qrdbresultsguard.inl \
    src/entity/qrsqlconfig.cpp \
    src/entity/qrsqldatabase.cpp \
    src/entity/qrsqldatabaseerror.cpp \
    src/entity/qrsqlquery.cpp \
    src/entity/qrsqltableinfo.cpp \
    src/entity/qrsqltable.cpp \
    src/generator/element/qrsqlcompare.cpp \
    src/generator/element/qrsqlelement.cpp \
    src/generator/element/qrsqlelementtemp.cpp \
    src/generator/element/qrsqlemptytext.cpp \
    src/generator/element/qrsqlexpression.cpp \
    src/generator/element/qrsqlin.cpp \
    src/generator/element/qrsqlisbetween.cpp \
    src/generator/element/qrsqlisnull.cpp \
    src/generator/element/qrsqllimit.cpp \
    src/generator/element/qrsqlsort.cpp \
    src/generator/qrdeletesql.cpp \
    src/generator/qrinsertsql.cpp \
    src/generator/qrselectsql.cpp \
    src/generator/qrsqlgenerator.cpp \
    src/generator/qrupdatesql.cpp \
    src/qrsqlhelper.cpp \
    src/generator/qrcreatesql.cpp
