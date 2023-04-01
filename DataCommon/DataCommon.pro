QT -= gui

TEMPLATE = lib
DEFINES += DATACOMMON_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/armorpiece.cpp \
    src/datacommon.cpp \
    src/decoration.cpp \
    src/riseexception.cpp \
    src/skill.cpp \
    src/talisman.cpp \
    src/weapon.cpp \
    src/datacommon.cpp

HEADERS += \
    src/DataCommon_global.h \
    src/DataCommon_global.h \
    src/armorpiece.h \
    src/datacommon.h \
    src/decoration.h \
    src/riseexception.h \
    src/skill.h \
    src/talisman.h \
    src/weapon.h \
    src/datacommon.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
