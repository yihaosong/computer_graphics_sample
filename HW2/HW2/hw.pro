TEMPLATE = app
TARGET = hw
QT += widgets opengl
OBJECTS_DIR = ./obj
MOC_DIR     = ./moc
RESOURCES   = hw.qrc

win32-msvc2013 {
	LIBS += -lopengl32 -lglu32
	QMAKE_CXXFLAGS += /MP /Zi
}


unix:!macx {
	CONFIG += C++11
}

# Input
HEADERS +=	MainWindow.h	\
		HW.h		\
		HW0a.h		\
		HW0b.h		\
		HW0c.h      \
		HW2a.h    \
		HW2b.h

SOURCES +=	main.cpp	\
		MainWindow.cpp 	\
		HW.cpp		\
		HW0a.cpp	\
		HW0b.cpp	\
		HW0c.cpp    \
		HW2a.cpp   \
		HW2b.cpp
