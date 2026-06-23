TEMPLATE = app
TARGET = Praktika2026

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# The code is standard C and should build on MSVC, MinGW, Linux and macOS.
# MSVC shows C4996 warnings for standard C functions. These warnings are not
# real portability errors, so we disable them at project level.
DEFINES += _CRT_SECURE_NO_WARNINGS

win32-msvc:QMAKE_CFLAGS += /std:c11
!win32-msvc:QMAKE_CFLAGS += -std=c11 -Wall -Wextra

SOURCES += \
    file_utils.c \
    main.c \
    sorting.c \
    utils.c

HEADERS += \
    file_utils.h \
    sorting.h \
    utils.h
