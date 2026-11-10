QT += widgets

CONFIG += c++17
CONFIG += warn_on

TEMPLATE = app
TARGET = VoleSimulatorQt

# The main source file keeps the exact name required by the course.
SOURCES += \
    $$quote(A2-S15, 16-20251149-20251111-20250508-20250102.cpp) \
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

# Include all text files in the project folder, including any extra test files.
DISTFILES += $$files($$PWD/*.txt)
