// ===============================================================
// Computer Graphics Homework Solutions
// Copyright (C) 2015 by George Wolberg
//
// HW0b.cpp - HW0b class
//
// Written by: George Wolberg, 2015
// ===============================================================

#include "HW1b.h"
#include "MainWindow.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1b::HW1b:
//
// HW0b constructor.
//
HW1b::HW1b(QWidget *parent)
	: HW(parent)
{
	float triangle_height = 1.25;
	orig_a = new QPointF(0.0,triangle_height*2/3);
	orig_b = new QPointF(-triangle_height/sqrt(3),-triangle_height*1/3);
	orig_c = new QPointF(triangle_height/sqrt(3),-triangle_height*1/3);
	m_angle = 0;
}

HW1b::~HW1b()
{
	delete orig_a;
	delete orig_b;
	delete orig_c;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0b::initializeGL:
//
// Initialization routine before display loop.
// Gets called once before the first time resizeGL() or paintGL() is called.
//
void
HW1b::initializeGL()
{
	// init state variables
	glClearColor(0.0, 0.0, 0.0, 0.0);	// set background color
	glColor3f(1.0, 1.0, 1.0);		// set foreground color
	subdivide(0);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0b::resizeGL:
//
// Resize event handler.
// The input parameters are the window width (w) and height (h).
//
void
HW1b::resizeGL(int w, int h)
{
	// save window dimensions
	m_winW = w;
	m_winH = h;

	// compute aspect ratio
	float xmax, ymax;
	if (m_checkBoxAR->isChecked()) {
		float ar = (float)w / h;
		if (ar > 1.0) {		// wide screen
			xmax = ar;
			ymax = 1.0;
		}
		else {		// tall screen
			xmax = 1.0;
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
	if (m_checkBoxFlip->isChecked()) glOrtho(-xmax, xmax, ymax, -ymax, -1.0, 1.0);
	else glOrtho(-xmax, xmax, -ymax, ymax, -1.0, 1.0);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1b::paintGL:
//
// Update GL scene.
//
void
HW1b::paintGL()
{	
	float x,y,d;

	// clear canvas with background values
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < Colors.size(); i++) {
        qglColor(*Colors[i]);
        for (int j = 0; j < 3; j++) {
        	QPointF * a = Points[i*3 + j];
        	if (m_checkBoxTwist->isChecked()) {
		        d = sqrt(pow(a->x(), 2)+ pow(a->y(),2));
		    } else {
		        d = 1;
		    }
        	x = a->x()*cos(m_angle * d) + a->y()*sin(m_angle * d);
   			y = a->x()*-sin(m_angle * d) + a->y()*cos(m_angle * d);
   			glVertex2f(x, y);
        }
    }
    glFlush();
    glEnd();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1b::controlPanel:
//
// Create control panel groupbox.
//
QGroupBox*
HW1b::controlPanel()
{
	// init group box
	QGroupBox *groupBox = new QGroupBox("Homework 1b");
	groupBox->setMinimumWidth(300);

	// layout for assembling widgets
	QGridLayout *layout = new QGridLayout;

	// create checkboxes
	m_checkBoxFlip = new QCheckBox("Flip y-coordinates");
	m_checkBoxAR = new QCheckBox("Maintain aspect ratio");
	m_checkBoxTwist = new QCheckBox("Twist");
	m_checkBoxTwist->setChecked(false);
	m_checkBoxFlip->setChecked(false);
	m_checkBoxAR->setChecked(true);

	// create slider to rotate data
	m_slider = new QSlider(Qt::Horizontal);
	m_slider->setRange(0, 360);
	m_slider->setValue(0);

	//create slider to subdivide
	m_sliderSubdiv = new QSlider(Qt::Horizontal);
	m_sliderSubdiv->setRange(0, 6);
	m_sliderSubdiv->setValue(0);

	// create spinBox for Rotation
	m_spinBox = new QSpinBox;
	m_spinBox->setRange(0, 360);
	m_spinBox->setValue(0);

	// create spinBox for Subdivision
	m_spinBoxSubdiv = new QSpinBox;
	m_spinBoxSubdiv->setRange(0, 6);
	m_spinBoxSubdiv->setValue(0);

	// slider labels to display name
	QLabel *label = new QLabel("Rotation");
	QLabel *labelSubdiv = new QLabel("Subdivisions");

	// assemble widgets into layout
	layout->addWidget(m_checkBoxFlip, 0, 0, 1, 3);
	layout->addWidget(m_checkBoxAR, 1, 0, 1, 3);
	layout->addWidget(m_checkBoxTwist, 2, 0, 1, 3);
	layout->addWidget(label, 3, 0);
	layout->addWidget(m_slider, 3, 1);
	layout->addWidget(m_spinBox, 3, 2);
	layout->addWidget(labelSubdiv, 4, 0);
	layout->addWidget(m_sliderSubdiv, 4, 1);
	layout->addWidget(m_spinBoxSubdiv, 4, 2);

	// assign layout to group box
	groupBox->setLayout(layout);

	// init signal/slot connections
	connect(m_checkBoxFlip, SIGNAL(stateChanged(int)), this, SLOT(flipY(int)));
	connect(m_checkBoxAR, SIGNAL(stateChanged(int)), this, SLOT(aspect(int)));
	connect(m_checkBoxTwist, SIGNAL(stateChanged(int)), this, SLOT(twist()));
	connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(rotate(int)));
	connect(m_spinBox, SIGNAL(valueChanged(int)),m_slider,SLOT(setValue(int)) );
	connect(m_slider,SIGNAL(valueChanged(int)),m_spinBox,SLOT(setValue(int)) );
	connect(m_spinBoxSubdiv, SIGNAL(valueChanged(int)), this, SLOT(subdivide(int)));
	connect(m_spinBoxSubdiv, SIGNAL(valueChanged(int)),m_sliderSubdiv,SLOT(setValue(int)) );
	connect(m_sliderSubdiv,SIGNAL(valueChanged(int)),m_spinBoxSubdiv,SLOT(setValue(int)) );

	return(groupBox);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1b::flipY:
//
// Slot function to flip y-coordinates.
//
void
HW1b::flipY(int state)
{
	// update checkbox
	m_checkBoxFlip->setChecked(state);

	// call resizeGL() to reset coordinate system 
	resizeGL(m_winW, m_winH);

	// redraw
	updateGL();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1b::twist:
//
// Slot function to twist.
//
void
HW1b::twist(){
	
	//redraw
	updateGL();
}

QPointF * HW1b::midpoint(QPointF * a, QPointF * b) 
{
    return new QPointF((a->x()+b->x())/2, (a->y()+b->y())/2);
}

void HW1b::subdivide(int divisions) {
	for (std::vector< QPointF *>::iterator it = Points.begin() ; it != Points.end(); ++it)
   	{
    	delete (*it);
   	} 
	Points.clear();
	for (std::vector< QColor *>::iterator it = Colors.begin() ; it != Colors.end(); ++it)
   	{
    	delete (*it);
   	} 
	Colors.clear();
	divideTriangle(
		new QPointF(orig_a->x(), orig_a->y()), 
		new QPointF(orig_b->x(), orig_b->y()), 
		new QPointF(orig_c->x(), orig_c->y()), 
		divisions);
	updateGL();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1b::subdivide:
//
// Slot function to subdivide triangle.
//
void
HW1b::divideTriangle(QPointF * a, QPointF * b, QPointF * c, int divisions)
{
    if (divisions == 0) {
        Points.push_back(a);
   		Points.push_back(b);
    	Points.push_back(c);
    	Colors.push_back(new QColor(rand() % 256, rand() % 256, rand() % 256));
    } else {
        divideTriangle(a, midpoint(a,b), midpoint(a,c), divisions-1);
        divideTriangle(b, midpoint(a,b), midpoint(b,c), divisions-1);
        divideTriangle(c, midpoint(a,c), midpoint(b,c), divisions-1);
        divideTriangle(midpoint(a,b), midpoint(a,c), midpoint(b,c), divisions-1);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1b::aspect:
//
// Slot function to maintain aspect ratio.
//
void
HW1b::aspect(int state)
{
	// update checkbox
	m_checkBoxAR->setChecked(state);

	// call resizeGL() to reset coordinate system 
	resizeGL(m_winW, m_winH);

	// redraw
	updateGL();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0b::rotate:
//
// Slot function to rotate data.
//
void
HW1b::rotate(int angle)
{
	// convert angle to radians
	m_angle = angle * M_PI / 180;

	// redraw
	updateGL();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1b::reset:
//
// Reset parameters.
//
void
HW1b::reset()
{
	// reset checkboxes
	m_checkBoxFlip->setChecked(false);
	m_checkBoxAR->setChecked(true);
	m_checkBoxTwist->setChecked(false);
	resizeGL(m_winW, m_winH);

	// reset angle and slider/spinbox settings
	m_angle = 0;
	m_slider->setValue(0);
	m_spinBox->setValue(0);

	m_sliderSubdiv->setValue(0);
	m_spinBoxSubdiv->setValue(0);

	// redraw
	updateGL();
}
