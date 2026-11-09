QT += widgets

CONFIG += c++17
CONFIG += warn_on

TEMPLATE = app
TARGET = VoleSimulatorQt

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Machine.cpp \
    CPU.cpp \
    ALU.cpp \
    Memory.cpp \
    Utilities.cpp

HEADERS += \
    MainWindow.h \
    Machine.h \
    CPU.h \
    ALU.h \
    Memory.h \
    Utilities.h

# Example program files are included in the project folder.
DISTFILES += \
    program(1).txt \
    program(2).txt \
    program(3).txt \
    program(4).txt \
    program(5).txt \
    program(6).txt \
    program(7).txt \
    program(8).txt \
    program(9).txt \
    program(10).txt
