TEMPLATE = app
TARGET = hw
QT += opengl
OBJECTS_DIR = ./obj
MOC_DIR     = ./moc
#RESOURCES   = hw.qrc

win32-msvc2013 {
	LIBS += -lopengl32 -lglu32
	QMAKE_CXXFLAGS += /MP /Zi
}



mac {
  CONFIG -= app_bundle
}

unix:!macx {
	CONFIG += C++11
}

# Input
HEADERS += MainWindow.h HW.h \
	   HW0a.h HW0b.h HW1a.h HW1b.h
SOURCES += main.cpp MainWindow.cpp HW.cpp \
	   HW0a.cpp HW0b.cpp HW1a.cpp HW1b.cpp
