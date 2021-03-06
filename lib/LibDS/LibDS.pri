#
# This file is part of QDriverStation
#
# Copyright (c) 2015 WinT 3794 <http:/wint3794.org>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

CODECFORTR = UTF-8
CODECFORSRC = UTF-8

QT += gui
QT += qml
QT += core
QT += network
QT += widgets
QT += multimedia

CONFIG += c++11

!win32* {
    QMAKE_CXXFLAGS += -std=c++0x
}

INCLUDEPATH += $$PWD/include

HEADERS += \
    $$PWD/include/LibDS/DriverStation.h \
    $$PWD/include/LibDS/Protocols/Protocol2015.h \
    $$PWD/include/LibDS/Core/Client.h \
    $$PWD/include/LibDS/Core/Common.h \
    $$PWD/include/LibDS/Core/ElapsedTimer.h \
    $$PWD/include/LibDS/Core/Library.h \
    $$PWD/include/LibDS/Core/NetConsole.h \
    $$PWD/include/LibDS/Core/ProtocolBase.h \
    $$PWD/include/LibDS/Core/ProtocolManager.h \
    $$PWD/include/LibDS/Core/Timers.h \
    $$PWD/include/LibDS/Core/Watchdog.h \
    $$PWD/include/LibDS/Core/Discovery/Discovery.h \
    $$PWD/include/LibDS/Protocols/Protocol2016.h \
    $$PWD/include/LibDS/Core/Discovery/MDNS_Discovery.h

SOURCES += \
    $$PWD/src/DriverStation.cpp \
    $$PWD/src/Core/Client.cpp \
    $$PWD/src/Core/Common.cpp \
    $$PWD/src/Core/ElapsedTimer.cpp \
    $$PWD/src/Core/NetConsole.cpp \
    $$PWD/src/Core/ProtocolBase.cpp \
    $$PWD/src/Core/ProtocolManager.cpp \
    $$PWD/src/Core/Timers.cpp \
    $$PWD/src/Core/Watchdog.cpp \
    $$PWD/src/Core/Discovery/Discovery.cpp \
    $$PWD/src/Protocols/Protocol2015.cpp \
    $$PWD/src/Protocols/Protocol2016.cpp \
    $$PWD/src/Core/Discovery/MDNS_Discovery.cpp

RESOURCES += $$PWD/etc/sounds/libds-sounds.qrc
