// ===============================================================
// Computer Graphics Homework Solutions
// Copyright (C) 2015 by George Wolberg
//
// HW0c.cpp - HW0c class
//
// Written by: George Wolberg, 2015
// ===============================================================

#include "HW2b.h"
#include <time.h>


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0c::HW0c:
//
// HW0c constructor.
//
HW2b::HW2b(QWidget *parent)
	: HW(parent)
{
	// init vars
	m_twist = true;
	m_reverseColor = false;
	pointA[0] = -0.7f;
	pointA[1] = -0.4041f;
	pointB[0] = 0.7f;
	pointB[1] = -0.4041f;
	pointC[0] = 0;
	pointC[1] = 0.8083f;

	subdivisions = 0;

	//seed random function
	srand (static_cast <unsigned> (time(0)));
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0c::controlPanel:
//
// Create control panel groupbox.
//
QGroupBox*
HW2b::controlPanel()
{
	// init group box
	QGroupBox *groupBox = new QGroupBox("Homework 2c");

	// create labels
	QLabel *label[3];
	label[0] = new QLabel("Theta");
	label[1] = new QLabel("Reverse color?");
	label[2] = new QLabel("Subdivisions:");

	//create and init slider
	m_sliderTheta = new QSlider(Qt::Horizontal);
	m_sliderTheta->setRange(0, 360);
	m_sliderTheta->setValue(0);

	// create spinBoxes
	m_spinBoxTheta = new QSpinBox;
	m_spinBoxTheta->setRange(0, 360);
	m_spinBoxTheta->setValue(0);

	//create and init slider
	m_sliderSubdivide = new QSlider(Qt::Horizontal);
	m_sliderSubdivide->setRange(0, 10);
	m_sliderSubdivide->setValue(0);

	// create spinBoxes
	m_spinBoxSubdivide = new QSpinBox;
	m_spinBoxSubdivide->setRange(0, 10);
	m_spinBoxSubdivide->setValue(0);

	// init radio buttons
	m_radio[0] = new QRadioButton("Yes");
	m_radio[1] = new QRadioButton("No");

	// set "No" radio button to be default
	m_radio[1]->setChecked(true);

	// checkbox for enabling/disabling twist
	m_checkBoxTwist = new QCheckBox("Twist?");
	m_checkBoxTwist->setChecked(m_twist);

	// assemble radio buttons into horizontal widget
	QWidget *widget = new QWidget;
	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget(m_radio[0]);
	hbox->addWidget(m_radio[1]);
	hbox->addStretch();
	widget->setLayout(hbox);

	// layout for assembling widgets
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(label[0], 0, 0);
	layout->addWidget(m_sliderTheta, 0, 1);
	layout->addWidget(m_spinBoxTheta, 0, 2);
	layout->addWidget(label[2], 1, 0);
	layout->addWidget(m_sliderSubdivide, 1, 1);
	layout->addWidget(m_spinBoxSubdivide, 1, 2);
	layout->addWidget(label[1], 2, 0);
	layout->addWidget(widget, 2, 1);
	layout->addWidget(m_checkBoxTwist, 3, 0);

	// assign layout to group box
	groupBox->setLayout(layout);

	// init signal/slot connections
	connect(m_sliderTheta, SIGNAL(valueChanged(int)), this, SLOT(changeTheta(int)));
	connect(m_spinBoxTheta, SIGNAL(valueChanged(int)), m_sliderTheta, SLOT(setValue(int)));
	connect(m_sliderTheta, SIGNAL(valueChanged(int)), m_spinBoxTheta, SLOT(setValue(int)));
	connect(m_sliderSubdivide, SIGNAL(valueChanged(int)), this, SLOT(subdivide(int)));
	connect(m_spinBoxSubdivide, SIGNAL(valueChanged(int)), m_sliderSubdivide, SLOT(setValue(int)));
	connect(m_sliderSubdivide, SIGNAL(valueChanged(int)), m_spinBoxSubdivide, SLOT(setValue(int)));
	connect(m_radio[0], SIGNAL(toggled(bool)), this, SLOT(reverseChanged(bool)));
	connect(m_checkBoxTwist, SIGNAL(stateChanged(int)), this, SLOT(twistChanged(int)));

	return(groupBox);
}


//helper function to perform recursion for vertices
void
HW2b::divideTriangle(float* a, float* b, float* c, int count) {
	if (count > 0) {
		float ab[2] = { (a[0] + b[0]) / 2.0, (a[1] + b[1]) / 2.0 };
		float bc[2] = { (b[0] + c[0]) / 2.0, (b[1] + c[1]) / 2.0 };
		float ac[2] = { (a[0] + c[0]) / 2.0, (a[1] + c[1]) / 2.0 };
		divideTriangle(a, ab, ac, count - 1);
		divideTriangle(b, bc, ab, count - 1);
		divideTriangle(c, ac, bc, count - 1);
		divideTriangle(ab, ac, bc, count - 1);
	}
	else{
		m_points.push_back(vec2(a[0], a[1]));
		m_points.push_back(vec2(b[0], b[1]));
		m_points.push_back(vec2(c[0], c[1]));

		//create random color
		vec3 c(
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX));

		//push the color for each of the three vertices
		for (int i = 0; i<3;i++){
			m_colors.push_back(c);
		}
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0c::initializeGL:
//
// Initialization routine before display loop.
// Gets called once before the first time resizeGL() or paintGL() is called.
//
void
HW2b::initializeGL()
{
	// initialize GL function resolution for current context
	initializeGLFunctions();

	// init vertex and fragment shaders
	initShaders();

	// initialize vertex buffer and write positions to vertex shader
	initVertexBuffer();

	// init state variables
	glClearColor(0.0, 0.0, 0.0, 0.0);	// set background color
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW2a::initShaders:
//
// Initialize vertex and fragment shaders.
//
void
HW2b::initShaders()
{
	// compile vertex shader
	if (!m_program.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader2b.glsl")) {
		QMessageBox::critical(0, "Error", "Vertex shader error", QMessageBox::Ok);
		QApplication::quit();
	}

	// compile fragment shader
	if (!m_program.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader2b.glsl")) {
		QMessageBox::critical(0, "Error", "Fragment shader error", QMessageBox::Ok);
		QApplication::quit();
	}

	// link shader pipeline
	if (!m_program.link()) {
		QMessageBox::critical(0, "Error", "Could not link shader", QMessageBox::Ok);
		QApplication::quit();
	}

	// bind the glsl progam
	glUseProgram(m_program.programId());

	// bind the attribute variable in the glsl program with a generic vertex attribute index;
	// values provided via ATTRIB_VERTEX will modify the value of "a_position")
	glBindAttribLocation(m_program.programId(), ATTRIB_VERTEX, "a_Position");

	// bind the attribute variable in the glsl program with a generic vertex attribute index;
	// values provided via ATTRIB_COLOR will modify the value of "a_Color")
	glBindAttribLocation(m_program.programId(), ATTRIB_COLOR, "a_Color");

	m_u_theta = glGetUniformLocation(m_program.programId(), "u_theta");
	if ((int)m_u_theta < 0) {
		qDebug() << "Failed to get the storage location of u_theta";
		exit(-1);
	}
	glUniform1f(m_u_theta, 0);
	// get storage location of u_Twist in vertex shader
	m_u_reverseColor = glGetUniformLocation(m_program.programId(), "u_ReverseColor");
	if ((int)m_u_reverseColor < 0) {
		qDebug() << "Failed to get the storage location of u_ReverseColor";
		exit(-1);
	}
	glUniform1i(m_u_reverseColor, m_reverseColor);

	m_u_twist = glGetUniformLocation(m_program.programId(), "u_twist");
	if ((int)m_u_twist < 0) {
		qDebug() << "Failed to get the storage location of u_twist";
		exit(-1);
	}
	glUniform1i(m_u_twist, m_twist);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0c::initVertexBuffer:
//
// Initialize vertex buffer.
//
void
HW2b::initVertexBuffer()
{
	// set flag for creating buffers (1st time only)
	static bool flag = 1;

	// verify that we have valid vertex/color buffers
	static GLuint vertexBuffer = -1;
	static GLuint colorBuffer = -1;
	if (flag) {	// create vertex and color buffers
		glGenBuffers(1, &vertexBuffer);
		glGenBuffers(1, &colorBuffer);
		flag = 0;	// reset flag
	}

	divideTriangle(pointA, pointB, pointC, subdivisions);

  m_numPoints = m_points.size();		// save number of vertices

	// bind the buffer to the GPU; all future drawing calls gets data from this buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// copy the vertices from CPU to GPU
	glBufferData(GL_ARRAY_BUFFER, m_numPoints*sizeof(vec2), &m_points[0], GL_STATIC_DRAW);

	// enable the assignment of attribute vertex variable
	glEnableVertexAttribArray(ATTRIB_VERTEX);

	// assign the buffer object to the attribute vertex variable
	glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, false, 0, NULL);

	// bind color buffer to the GPU; all future buffer ops operate on this buffer
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);

	// copy the color from CPU to GPU
	glBufferData(GL_ARRAY_BUFFER, m_colors.size()*sizeof(vec3), &m_colors[0], GL_STATIC_DRAW);

	// enable the assignment of attribute color variable
	glEnableVertexAttribArray(ATTRIB_COLOR);

	// assign the buffer object to the attribute color variable
	glVertexAttribPointer(ATTRIB_COLOR, 3, GL_FLOAT, false, 0, NULL);

	// clear vertex and color vectors because they have already been copied into GPU
	m_points.clear();
	m_colors.clear();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW2b::resizeGL:
//
// Resize event handler.
// The input parameters are the window width (w) and height (h).
//
void
HW2b::resizeGL(int w, int h)
{
	// save window dimensions
	m_winW = w;
	m_winH = h;

	// compute aspect ratio
	float ar = (float)w / h;
	float xmax, ymax;
	if (ar > 1.0) {		// wide screen
		xmax = ar;
		ymax = 1.;
	}
	else {			// tall screen
		xmax = 1.;
		ymax = 1 / ar;
	}

	// set viewport to occupy full canvas
	glViewport(0, 0, w, h);

	// init viewing coordinates for orthographic projection
	glLoadIdentity();
	glOrtho(-xmax, xmax, -ymax, ymax, -1.0, 1.0);
	updateGL();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW2b::paintGL:
//
// Update GL scene.
//
void
HW2b::paintGL()
{
	// clear canvas with background color
	glClear(GL_COLOR_BUFFER_BIT);

	// draw triangles
	glDrawArrays(GL_TRIANGLES, 0, m_numPoints);
}

void
HW2b::reset()
{
	// reset parameters
	m_reverseColor = false;
	m_twist = true;

	m_sliderTheta->setValue(0);

	m_spinBoxTheta->setValue(0);

	// set "No" radio button to be default
	m_radio[1]->setChecked(true);
	m_checkBoxTwist->setChecked(true);

}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0c::changeTheta:
//
// Slot function to change rotation angle.
//
void
HW2b::changeTheta(int angle)
{
	// init vars
	m_reverseColor = false;			// do not update color during rotation

	glUniform1f(m_u_theta, angle*M_PI/180);
	//glUniform1f(m_u_reverseColor, m_reverseColor);

	// draw
	updateGL();
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW2v::subdivide:
//
// Slot function to subdivide.
//
void
HW2b::subdivide(int subdivs)
{
	subdivisions = subdivs;

	initVertexBuffer(); //reinitialize with new vertices...
	// draw
	updateGL();
}

void
HW2b::reverseChanged(bool value)
{
	// init vars
	m_reverseColor = value;

	// redraw with flag set to 1
	glUniform1i(m_u_reverseColor, m_reverseColor);
	updateGL();
}

void
HW2b::twistChanged(int value)
{
	// init vars
	m_twist = (bool) value;

	// redraw with flag set to 0
	glUniform1i(m_u_twist, m_twist);
	updateGL();
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0c::mousePressEvent:
//
// Event handler for mouse press events.
//
void
HW2b::mousePressEvent(QMouseEvent *event)
{
	m_mousePosition = event->pos();
	QGLWidget::mousePressEvent(event);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0c::mouseReleaseEvent:
//
// Event handler for mouse release events.
//
void
HW2b::mouseReleaseEvent(QMouseEvent *event)
{
	QGLWidget::mouseReleaseEvent(event);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0c::mouseMoveEvent:
//
// Event handler for mouse move events.
//
void
HW2b::mouseMoveEvent(QMouseEvent *event)
{
	// compute a1: angle of previous mouse position
	int x = m_mousePosition.x() - m_winW / 2;
	int y = m_winH / 2 - m_mousePosition.y();
	int a1 = atan2(y, x) * 180 / M_PI;

	// get current mouse position and save it
	m_mousePosition = event->pos();

	if (event->buttons() & Qt::LeftButton) {
		// compute a2: angle of current mouse position
		x = m_mousePosition.x() - m_winW / 2;
		y = m_winH / 2 - m_mousePosition.y();
		int a2 = atan2(y, x) * 180 / M_PI;

		// update angle based on difference between a1 and a2;
		int angle = m_sliderTheta->value() + (a2 - a1);

		// convert angle into [0,360] range
		if (angle < 0)	angle += 360;
		if (angle > 360)	angle -= 360;

		m_sliderTheta->setValue(angle);
	}

	QGLWidget::mouseMoveEvent(event);
}
