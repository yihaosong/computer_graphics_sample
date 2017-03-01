// ===============================================================
// Computer Graphics Homework Solutions
// Copyright (C) 2015 by George Wolberg
//
// HW0b.cpp - HW0b class
//
// Written by: George Wolberg, 2015
// ===============================================================

#include "HW1A.h"
#include "MainWindow.h"
#include <vector>
using namespace std;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1A::HW1A:
//
// HW1A constructor.
//
HW1A::HW1A(QWidget *parent)
	: HW(parent)
{
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1A::initializeGL:
//
// Initialization routine before display loop.
// Gets called once before the first time resizeGL() or paintGL() is called.
//
void
HW1A::initializeGL()
{
	// init state variables
	glClearColor(0.0, 0.0, 0.0, 1.0);	// set background color
	glColor3f(1.0, 1.0, 0.0);		// set foreground color
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0b::resizeGL:
//
// Resize event handler.
// The input parameters are the window width (w) and height (h).
//
void
HW1A::resizeGL(int w, int h)
{
	// save window dimensions
	m_winW = w;
	m_winH = h;

	// compute aspect ratio

	if (m_checkBoxAR->isChecked()) {
		float ar = (float)w / h;
		if (ar > 1.0) {		// wide screen
			xmax = ar;
			ymax = 1.;
		}
		else {		// tall screen
			xmax = 1.;
			ymax = 1 / ar;
		}
	}
	else {
		xmax = 1.0;
		ymax = 1.0;
	}

	// set viewport to occupy full canvas
	glViewport(0, 0, w, h);

	// init viewing coordinates for orthographic projection
	glLoadIdentity();
	if (m_checkBoxFlip->isChecked())
		glOrtho(-xmax, xmax, ymax, -ymax, -1.0, 1.0);
	else	glOrtho(-xmax, xmax, -ymax, ymax, -1.0, 1.0);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1A::paintGL:
//
// Update GL scene.
//
void
HW1A::paintGL()
{

	glClear(GL_COLOR_BUFFER_BIT);

	/* put the 9 draw modes that we'll use in an array */
	GLbitfield drawModes[9] = {
		GL_POINTS,
		GL_LINES,
		GL_LINE_STRIP,
		GL_LINE_LOOP,
		GL_TRIANGLES,
		GL_TRIANGLE_STRIP,
		GL_TRIANGLE_FAN,
		GL_QUADS,
		GL_POLYGON
	};
	//CREATE A LOOP THAT WILL CREATE ONE VIEWPORT PER ITERATION

	QVector2D v[] = {
		QVector2D(-0.5, -0.75),
		QVector2D(-0.5, -0.5),
		QVector2D(-0.5, -0.25),
		QVector2D(-0.5, 0),
		QVector2D(-0.5, 0.25),
		QVector2D(-0.5, 0.5),
		QVector2D(-0.5, 0.75),
		QVector2D(-0.5, 0.98),
		QVector2D(-0.25, 0.98),
		QVector2D(0, 0.98),
		QVector2D(0.25, 0.98),
		QVector2D(0.5, 0.75),
		QVector2D(0.5, 0.5),
		QVector2D(0.25, 0.25),
		QVector2D(0, 0.25),
		QVector2D(-0.25, 0.25),
	};

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){//using two for loops to step through the 9 portions
			if ((j == 0) && (i == 1)){ //the one needed to be filp over
				glLoadIdentity();
				glOrtho(-xmax, xmax, ymax, -ymax, -1.0, 1.0);
				glViewport(0, m_winH / 3, m_winW / 3, m_winH / 3);
					}
			else{
				glLoadIdentity();
				glOrtho(-xmax, xmax, -ymax, ymax, -1.0, 1.0);
				glViewport(m_winW / 3 * j, m_winH / 3 * i, m_winW / 3, m_winH / 3);
			}

			//Set the draw mode:
			glBegin(drawModes[i * 3 + j]); //chose the correct mode b4 drawing...
			for (int k = 0; k < 16; k++) {
				glVertex2f(v[k].x(), v[k].y());
			}
			glEnd();
			glFlush();
		}
	}

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0b::controlPanel:
//
// Create control panel groupbox.
//
QGroupBox*
HW1A::controlPanel()
{
	// init group box
	QGroupBox *groupBox = new QGroupBox("Homework 1a");
	groupBox->setMinimumWidth(300);

	// layout for assembling widgets
	QGridLayout *layout = new QGridLayout;

	// create checkboxes
	m_checkBoxFlip = new QCheckBox("Flip y-coordinates");
	m_checkBoxAR = new QCheckBox("Maintain aspect ratio");
	m_checkBoxFlip->setChecked(false);
	m_checkBoxAR->setChecked(true);

	// create slider to rotate data
	m_slider = new QSlider(Qt::Horizontal);
	m_slider->setRange(0, 360);
	//m_slider->setValue(0);

	// create spinBox
	m_spinBox = new QSpinBox;
	m_spinBox->setRange(0, 360);
	//m_spinBox->setValue(0);

	// slider label to display name	
	//QLabel *label = new QLabel("Rotation");

	// assemble widgets into layout
	//layout->addWidget(m_checkBoxFlip, 0, 0, 1, 3);
	layout->addWidget(m_checkBoxAR, 1, 0, 1, 3);
	//layout->addWidget(label, 2, 0);
	//layout->addWidget(m_slider, 2, 1);
	//layout->addWidget(m_spinBox, 2, 2);

	// assign layout to group box
	groupBox->setLayout(layout);

	// init signal/slot connections
	connect(m_checkBoxFlip, SIGNAL(stateChanged(int)), this, SLOT(flipY(int)));
	connect(m_checkBoxAR, SIGNAL(stateChanged(int)), this, SLOT(aspect(int)));
	connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(rotate(int)));
	connect(m_spinBox, SIGNAL(valueChanged(int)), this, SLOT(rotate(int)));

	return(groupBox);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0b::flipY:
//
// Slot function to flip y-coordinates.
//
void
HW1A::flipY(int state)
{
	// update checkbox
	m_checkBoxFlip->setChecked(state);

	// call resizeGL() to reset coordinate system 
	resizeGL(m_winW, m_winH);

	// redraw
	updateGL();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0b::aspect:
//
// Slot function to maintain aspect ratio.
//
void
HW1A::aspect(int state)
{
	// update checkbox
	m_checkBoxAR->setChecked(state);

	// call resizeGL() to reset coordinate system 
	resizeGL(m_winW, m_winH);

	// redraw
	updateGL();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1A::rotate:
//
// Slot function to rotate data.
//

void
HW1A::rotate(int angle)
{
	// update slider and spinbox
	m_slider->blockSignals(true);
	m_slider->setValue(angle);
	m_slider->blockSignals(false);

	m_spinBox->blockSignals(true);
	m_spinBox->setValue(angle);
	m_spinBox->blockSignals(false);

	// convert angle to radians
	m_angle = angle * (M_PI / 180.);

	// redraw
	updateGL();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0b::reset:
//
// Reset parameters.
//
void
HW1A::reset()
{
	// reset checkboxes
	m_checkBoxFlip->setChecked(false);
	m_checkBoxAR->setChecked(true);
	resizeGL(m_winW, m_winH);

	// reset angle and slider/spinbox settings
	m_angle = 0;
	m_slider->setValue(0);
	m_spinBox->setValue(0);

	// redraw
	updateGL();
}
