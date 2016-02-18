include($$PWD/profileinformations/profileinformations.pri)
include($$PWD/usercategories/usercategories.pri)
include($$PWD/research/research.pri)

SOURCES +=\
    $$PWD/user.cpp \
    $$PWD/profile.cpp \
    $$PWD/userdata.cpp \
    $$PWD/contactsnetwork.cpp \
    $$PWD/usercreator.cpp \
    $$PWD/smartuser.cpp

HEADERS  +=\
    $$PWD/user.h \
    $$PWD/profile.h \
    $$PWD/userdata.h \
    $$PWD/contactsnetwork.h \
    $$PWD/usercreator.h \
    $$PWD/smartuser.h
