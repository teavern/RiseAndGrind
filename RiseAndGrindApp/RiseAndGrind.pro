QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        armorpiece.cpp \
        armorset.cpp \
        decoration.cpp \
        engine.cpp \
        equipmentdatabase.cpp \
        fittedarmorpiece.cpp \
        main.cpp \
        searchparameters.cpp \
        setreport.cpp \
        skill.cpp \
        talisman.cpp \
        weapon.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    armorpiece.h \
    armorset.h \
    decoration.h \
    engine.h \
    equipmentdatabase.h \
    fittedarmorpiece.h \
    searchparameters.h \
    setreport.h \
    skill.h \
    talisman.h \
    weapon.h
