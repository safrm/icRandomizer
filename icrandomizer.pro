TARGET        = icRandomizer
HEADERS       = icrandomizer.h
SOURCES       = icrandomizer.cpp \
                main.cpp
RESOURCES     = icrandomizer.qrc

# install
target.path = $$[INSTALL_ROOT]/icRadnomizer
INSTALLS += target 

win32 {
QTDIR_BIN = $$system(qmake -query QT_INSTALL_BINS)
message($$QTDIR)
INSTALLS    += qtlibraries
qtlibraries.path  = /
qtlibraries.files = \
    $$QTDIR_BIN/QtCored4.dll \
    $$QTDIR_BIN/QtGuid4.dll \
    $$QTDIR_BIN/mingwm10.dll \
    $$QTDIR_BIN/libgcc_s_dw2-1.dll
} 

INSTALLS    += docs
docs.path  = $$[INSTALL_ROOT]/icRadnomizer
docs.files  = README LICENSE.LGPL

INSTALLS    += images-default images-dice images-emotions
images-default.files = images/*.png
images-default.path = $$[INSTALL_ROOT]/icRadnomizer/images
images-dice.files = images-dice/*.png
images-dice.path = $$[INSTALL_ROOT]/icRadnomizer/images-dice
images-emotions.files = images-emotions/*.png
images-emotions.path = $$[INSTALL_ROOT]/icRadnomizer/images-emotions



OTHER_FILES += \
    README \
    LICENSE.LGPL
