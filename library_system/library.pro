TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    date.cpp \
    book.cpp \
    loan.cpp \
    library.cpp \
    person.cpp \
    file_reader.cpp \
    cli.cpp

HEADERS += \
    date.hh \
    book.hh \
    loan.hh \
    library.hh \
    person.hh \
    file_reader.hh \
    cli.hh
