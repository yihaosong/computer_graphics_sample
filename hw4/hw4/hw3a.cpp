// ===============================================================
// Computer Graphics Homework Solutions
// Copyright (C) 2015 by George Wolberg
//
// HW3a.cpp - HW3a class
//
// Written by: George Wolberg, 2015
// ===============================================================

#include "HW3a.h"

enum {
	MV,
	THETA,
	SUBDIV,
	TWIST,
	SAMPLER
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::HW3a:
//
// HW3a constructor.
//
HW3a::HW3a(QWidget *parent)
	: HW(parent)
{
	// init vars
	m_theta = 0.0f;
	m_subdivisions = 0;
	m_twist = true;
	m_wire = true;
	pointA[0] = 0.0f;
	pointA[1] = 0.75f;
	pointB[0] = 0.65f;
	pointB[1] = -0.375f;
	pointC[0] = -0.65f;
	pointC[1] = -0.375f;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::controlPanel:
//
// Create control panel groupbox.
//
QGroupBox*
HW3a::controlPanel()
{
	// init group box
	QGroupBox *groupBox = new QGroupBox("Homework 3a");

	// create labels
	QLabel *label[3];
	label[0] = new QLabel("Theta");
	label[1] = new QLabel("Subdivisions:");

	//create and init slider
	m_sliderTheta = new QSlider(Qt::Horizontal);
	m_sliderTheta->setRange(0, 360);
	m_sliderTheta->setValue(0);

	// create spinBoxes
	m_spinBoxTheta = new QSpinBox;
	m_spinBoxTheta->setRange(0, 360);
	m_spinBoxTheta->setValue(0);

	//create and init slider
	m_sliderSubdiv = new QSlider(Qt::Horizontal);
	m_sliderSubdiv->setRange(0, 10);
	m_sliderSubdiv->setValue(0);

	// create spinBoxes
	m_spinBoxSubdiv = new QSpinBox;
	m_spinBoxSubdiv->setRange(0, 10);
	m_spinBoxSubdiv->setValue(0);

	// checkbox for enabling/disabling twist
	m_checkBoxTwist = new QCheckBox("Twist?");
	m_checkBoxTwist->setChecked(m_twist);

	// checkbox for enabling/disabling wire
	m_checkBoxWire = new QCheckBox("Draw Wire?");
	m_checkBoxWire->setChecked(m_wire);

	// assemble radio buttons into horizontal widget
	QWidget *widget = new QWidget;
	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addStretch();
	widget->setLayout(hbox);

	// layout for assembling widgets
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(label[0], 0, 0);
	layout->addWidget(m_sliderTheta, 0, 1);
	layout->addWidget(m_spinBoxTheta, 0, 2);
	layout->addWidget(label[1], 1, 0);
	layout->addWidget(m_sliderSubdiv, 1, 1);
	layout->addWidget(m_spinBoxSubdiv, 1, 2);
	layout->addWidget(m_checkBoxTwist, 2, 0);
	layout->addWidget(m_checkBoxWire, 2, 1);

	// assign layout to group box
	groupBox->setLayout(layout);

	// init signal/slot connections
	connect(m_sliderTheta, SIGNAL(valueChanged(int)), this, SLOT(changeTheta(int)));
	connect(m_spinBoxTheta, SIGNAL(valueChanged(int)), this, SLOT(changeTheta(int)));
	connect(m_sliderSubdiv, SIGNAL(valueChanged(int)), this, SLOT(changeSubdiv(int)));
	connect(m_spinBoxSubdiv, SIGNAL(valueChanged(int)), this, SLOT(changeSubdiv(int)));
	connect(m_checkBoxTwist, SIGNAL(stateChanged(int)), this, SLOT(changeTwist(int)));
	connect(m_checkBoxWire, SIGNAL(stateChanged(int)), this, SLOT(changeWire(int)));
	return(groupBox);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::initializeGL:
//
// Initialization routine before display loop.
// Gets called once before the first time resizeGL() or paintGL() is called.
//
void
HW3a::initializeGL()
{
	// initialize GL function resolution for current context
	initializeGLFunctions();

	// init texture
	initTexture();

	// init vertex and fragment shaders
	initShaders();

	// initialize vertex buffer and write positions to vertex shader
	initVertexBuffer();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::initTexture:
//
// Initialize texture.
//
void
HW3a::initTexture()
{
	// read image from file
	m_image.load(QString(":/mandrill.jpg"));

	// convert jpg to GL formatted image
	QImage qImage = QGLWidget::convertToGLFormat(m_image);

	// init vars
	int w = qImage.width();
	int h = qImage.height();

	// generate texture name and bind it
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// set the texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, qImage.bits());
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::initShaders:
//
// Initialize vertex and fragment shaders.
//
void
HW3a::initShaders()
{
	initShader1();
	initShader2();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::initShader1:
//
// Initialize vertex and fragment shaders for texture mapping.
//
void
HW3a::initShader1()
{
	// compile vertex shader
	if (!m_program[0].addShaderFromSourceFile(QGLShader::Vertex, ":/vshader3a1.glsl")) {
		QMessageBox::critical(0, "Error", "Vertex shader error", QMessageBox::Ok);
		QApplication::quit();
	}

	// compile fragment shader
	if (!m_program[0].addShaderFromSourceFile(QGLShader::Fragment, ":/fshader3a1.glsl")) {
		QMessageBox::critical(0, "Error", "Fragment shader error", QMessageBox::Ok);
		QApplication::quit();
		//exit(-1);
	}

	// bind the attribute variable in the glsl program with a generic vertex attribute index;
	// values provided via ATTRIB_VERTEX will modify the value of "a_position")
	glBindAttribLocation(m_program[0].programId(), ATTRIB_VERTEX, "a_Position");

	// bind the attribute variable in the glsl program with a generic vertex attribute index;
	// values provided via ATTRIB_TEXTURE_POSITION will modify the value of "a_TexCoord")
	glBindAttribLocation(m_program[0].programId(), ATTRIB_TEXTURE_POSITION, "a_TexCoord");

	// link shader pipeline; attribute bindings go into effect at this point
	if (!m_program[0].link()) {
		QMessageBox::critical(0, "Error", "Could not link shader", QMessageBox::Ok);
		QApplication::quit();
	}
	// get storage location of u_Theta in vertex shader
	m_uniform[0][THETA] = glGetUniformLocation(m_program[0].programId(), "u_Theta");
	if (m_uniform[0][THETA] < 0) {
		qDebug() << "Failed to get the storage location of u_Theta";
		exit(-1);
	}

	// get storage location of u_Twist in vertex shader
	m_uniform[0][TWIST] = glGetUniformLocation(m_program[0].programId(), "u_Twist");
	if (m_uniform[0][TWIST] < 0) {
		qDebug() << "Failed to get the storage location of u_Twist";
		exit(-1);
	}

	// get storage location of u_Sampler in fragment shader
	m_uniform[0][SAMPLER] = glGetUniformLocation(m_program[0].programId(), "u_Sampler");
	if (m_uniform[0][SAMPLER] < 0) {
		qDebug() << "Failed to get the storage location of u_Sampler";
		exit(-1);
	}

	// bind the glsl program
	glUseProgram(m_program[0].programId());

	glUniform1f(m_uniform[0][THETA], m_theta);
	glUniform1i(m_uniform[0][TWIST], m_twist);
	glUniform1i(m_uniform[0][SAMPLER], 0);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::initShader2:
//
// Initialize vertex and fragment shaders for wireframe rendering.
//
void
HW3a::initShader2()
{
	// compile vertex shader
	if (!m_program[1].addShaderFromSourceFile(QGLShader::Vertex, ":/vshader3a2.glsl")) {
		QMessageBox::critical(0, "Error", "Vertex shader error", QMessageBox::Ok);
		QApplication::quit();
	}

	// compile fragment shader
	if (!m_program[1].addShaderFromSourceFile(QGLShader::Fragment, ":/fshader3a2.glsl")) {
		QMessageBox::critical(0, "Error", "Fragment shader error", QMessageBox::Ok);
		QApplication::quit();
	}

	// bind the attribute variable in the glsl program with a generic vertex attribute index;
	// values provided via ATTRIB_VERTEX will modify the value of "a_position")
	glBindAttribLocation(m_program[1].programId(), ATTRIB_VERTEX, "a_Position");

	// bind the attribute variable in the glsl program with a generic vertex attribute index;
	// values provided via ATTRIB_TEXTURE_POSITION will modify the value of "a_TexCoord")
	glBindAttribLocation(m_program[1].programId(), ATTRIB_TEXTURE_POSITION, "a_TexCoord");

	// link shader pipeline; attribute bindings go into effect at this point
	if (!m_program[1].link()) {
		QMessageBox::critical(0, "Error", "Could not link shader", QMessageBox::Ok);
		QApplication::quit();
	}

	// get storage location of u_Theta in vertex shader
	m_uniform[1][THETA] = glGetUniformLocation(m_program[1].programId(), "u_Theta");
	if (m_uniform[1][THETA] < 0) {
		qDebug() << "Failed to get the storage location of u_Theta";
		exit(-1);
	}

	// get storage location of u_Twist in vertex shader
	m_uniform[1][TWIST] = glGetUniformLocation(m_program[1].programId(), "u_Twist");
	if (m_uniform[1][TWIST] < 0) {
		qDebug() << "Failed to get the storage location of u_Twist";
		exit(-1);
	}

	// bind the glsl program
	glUseProgram(m_program[1].programId());

	glUniform1f(m_uniform[1][THETA], m_theta);
	glUniform1i(m_uniform[1][TWIST], m_twist);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::initVertexBuffer:
//
// Initialize vertex buffer.
//
void
HW3a::initVertexBuffer()
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

	//generate first set of vertices...
	divideTriangle(pointA, pointB, pointC, m_subdivisions);

	// store vertex positions and colors in m_points and m_colors, respectively
	for (size_t i = 0; i<aPointx.size(); i++) {
		vec2 verticeA(aPointx[i], aPointy[i]);
		vec2 verticeB(bPointx[i], bPointy[i]);
		vec2 verticeC(cPointx[i], cPointy[i]);

		triangle(verticeA, verticeB, verticeC); //store vertices, also for textures...

	}
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
	glBufferData(GL_ARRAY_BUFFER, m_coords.size()*sizeof(vec2), &m_coords[0], GL_STATIC_DRAW);

	// enable the assignment of attribute color variable
	glEnableVertexAttribArray(ATTRIB_TEXTURE_POSITION);

	// assign the buffer object to the attribute color variable
	glVertexAttribPointer(ATTRIB_TEXTURE_POSITION, 2, GL_FLOAT, false, 0, NULL);

	// clear vertex and color vectors because they have already been copied into GPU
	m_points.clear();
	m_coords.clear();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::divideTriangle:
//
// Recursive subdivision of triangle (a,b,c). Recurse count times.
//
void
HW3a::divideTriangle(float* a, float* b, float* c, int count) {
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
		aPointx.push_back(a[0]);
		aPointy.push_back(a[1]);
		bPointx.push_back(b[0]);
		bPointy.push_back(b[1]);
		cPointx.push_back(c[0]);
		cPointy.push_back(c[1]);
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::triangle:
//
// Push positions and colors of the three triangle vertices.
//
void
HW3a::triangle(vec2 v1, vec2 v2, vec2 v3)
{
	// init geometry
	m_points.push_back(v1);
	m_points.push_back(v2);
	m_points.push_back(v3);

	// init texture coordinates
	m_coords.push_back(vec2((v1.x() + .65) / 1.3, (v1.y() + .375) / 1.125));
	m_coords.push_back(vec2((v2.x() + .65) / 1.3, (v2.y() + .375) / 1.125));
	m_coords.push_back(vec2((v3.x() + .65) / 1.3, (v3.y() + .375) / 1.125));
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::resizeGL:
//
// Resize event handler.
// The input parameters are the window width (w) and height (h).
//
void
HW3a::resizeGL(int w, int h)
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
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::paintGL:
//
// Update GL scene.
//
void
HW3a::paintGL()
{
	// clear canvas with background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw texture mapped triangles
	glUseProgram(m_program[0].programId());		// bind the glsl progam
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_numPoints);

	// draw wireframe, if necessary
	if (m_wire) {
		glUseProgram(m_program[1].programId());	// bind the glsl progam
		for (int i = 0; i<m_numPoints; i += 3)
			glDrawArrays(GL_LINE_LOOP, i, (GLsizei)3);
	}
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::reset:
//
// Reset parameters.
//
void
HW3a::reset()
{
	//......

	changeTheta(0.0);
	changeSubdiv(0);
	changeTwist(1);
	changeWire(1);
	// copy data to vertex shader
	/*for (int i = 0; i<2; i++) {
		glUseProgram(m_program[i].programId());		// bind the glsl progam
		glUniformMatrix4fv(m_uniform[i][MV], 1, GL_FALSE, m_ModelMatrix.constData());
		glUniform1f(m_uniform[i][THETA], m_theta);
		glUniform1i(m_uniform[i][THETA], m_twist);
	}*/
	// draw
	updateGL();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::changeTheta:
//
// Slot function to change rotation angle.
//
void
HW3a::changeTheta(int angle)
{
	// update slider and spinbox
	m_sliderTheta->blockSignals(true);
	m_sliderTheta->setValue(angle);
	m_sliderTheta->blockSignals(false);

	m_spinBoxTheta->blockSignals(true);
	m_spinBoxTheta->setValue(angle);
	m_spinBoxTheta->blockSignals(false);

	// update model's rotation matrix
	for (int i = 0; i<2; i++) {
		glUseProgram(m_program[i].programId());		// bind the glsl progam
		glUniform1f(m_uniform[i][THETA], angle); //convert to pi @ GPU side...
	}
	// draw
	updateGL();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::changeSubdiv:
//
// Slot function to change number of recursive subdivisions.
//
void
HW3a::changeSubdiv(int subdiv)
{
	//clear all arrays first
	aPointx.clear();
	aPointy.clear();
	bPointx.clear();
	bPointy.clear();
	cPointx.clear();
	cPointy.clear();

	// update slider and spinbox
	m_sliderSubdiv->blockSignals(true);
	m_sliderSubdiv->setValue(subdiv);
	m_sliderSubdiv->blockSignals(false);

	m_spinBoxSubdiv->blockSignals(true);
	m_spinBoxSubdiv->setValue(subdiv);
	m_spinBoxSubdiv->blockSignals(false);

	// init vars
	m_subdivisions = subdiv;
	divideTriangle(pointA, pointB, pointC, m_subdivisions);

	// compute new vertices and texture coordinates
	initVertexBuffer();

	// draw
	updateGL();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::changeTwist:
//
// Slot function to turn on/off m_twist;
//
void
HW3a::changeTwist(int twist)
{
	// init vars
	m_twist = twist;

	m_checkBoxTwist->blockSignals(true);
	m_checkBoxTwist->setChecked((bool)twist);
	m_checkBoxTwist->blockSignals(false);

	// redraw with new twist flag
	for (int i = 0; i<2; i++) {
		glUseProgram(m_program[i].programId());		// bind the glsl progam
		glUniform1i(m_uniform[i][TWIST], m_twist);
	}
	updateGL();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW3a::changeWire:
//
// Slot function to turn on/off m_wire;
//
void
HW3a::changeWire(int wire)
{
	// init vars
	m_wire = wire;

	m_checkBoxWire->blockSignals(true);
	m_checkBoxWire->setChecked((bool)wire);
	m_checkBoxWire->blockSignals(false);

	// redraw with new wire flag
	updateGL();
}
