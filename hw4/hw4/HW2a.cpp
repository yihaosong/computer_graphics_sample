// ===============================================================
// Computer Graphics Homework Solutions
// Copyright (C) 2015 by George Wolberg
//
// HW0c.cpp - HW0c class
//
// Written by: George Wolberg, 2015
// ===============================================================

#include "HW2a.h"


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

vec2 vertices[16] = {
	vec2(-0.5, -0.75),
	vec2(-0.5, -0.5),
	vec2(-0.5, -0.25),
	vec2(-0.5, 0),
	vec2(-0.5, 0.25),
	vec2(-0.5, 0.5),
	vec2(-0.5, 0.75),
	vec2(-0.5, 0.98),
	vec2(-0.25, 0.98),
	vec2(0, 0.98),
	vec2(0.25, 0.98),
	vec2(0.5, 0.75),
	vec2(0.5, 0.5),
	vec2(0.25, 0.25),
	vec2(0, 0.25),
	vec2(-0.25, 0.25),
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0c::HW0c:
//
// HW0c constructor.
//
HW2a::HW2a(QWidget *parent)
: HW(parent)
{

}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0c::controlPanel:
//
// Create control panel groupbox.
//
QGroupBox*
HW2a::controlPanel()
{
	// init group box
	QGroupBox *groupBox = new QGroupBox("Homework 1a");
	groupBox->setMinimumWidth(300);

	// layout for assembling widgets
	QGridLayout *layout = new QGridLayout;

	// create checkboxes
	m_checkBoxAR = new QCheckBox("Maintain aspect ratio");
	m_checkBoxAR->setChecked(true);

	layout->addWidget(m_checkBoxAR, 1, 0, 1, 3);

	groupBox->setLayout(layout);

	connect(m_checkBoxAR, SIGNAL(stateChanged(int)), this, SLOT(aspect(int)));


	return(groupBox);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0c::initializeGL:
//
// Initialization routine before display loop.
// Gets called once before the first time resizeGL() or paintGL() is called.
//
void
HW2a::initializeGL()
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
HW2a::initShaders()
{
	// compile vertex shader
	if (!m_program.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader2a.glsl")) {
		QMessageBox::critical(0, "Error", "Vertex shader error", QMessageBox::Ok);
		QApplication::quit();
	}

	// compile fragment shader
	if (!m_program.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader2a.glsl")) {
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

}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0c::initVertexBuffer:
//
// Initialize vertex buffer.
//
void
HW2a::initVertexBuffer()
{
	// set flag for creating buffers (1st time only)
	static bool flag = 1;

	// verify that we have valid vertex/color buffers
	static GLuint vertexBuffer = -1;
	if (flag) {	// create vertex and color buffers
		glGenBuffers(1, &vertexBuffer);
		flag = 0;	// reset flag
	}

	// bind the buffer to the GPU; all future drawing calls gets data from this buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// copy the vertices from CPU to GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// enable the assignment of attribute vertex variable
	glEnableVertexAttribArray(ATTRIB_VERTEX);

	// assign the buffer object to the attribute vertex variable
	glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, false, 0, NULL);

}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW2a::resizeGL:
//
// Resize event handler.
// The input parameters are the window width (w) and height (h).
//
void
HW2a::resizeGL(int w, int h)
{
	// save window dimensions
	m_winW = w;
	m_winH = h;

	// compute aspect ratio
	float ar = (float)w / h;


	if (m_checkBoxAR->isChecked()) {
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


	glLoadIdentity();
	glOrtho(-xmax, xmax, -ymax, ymax, -1.0, 1.0);


}



void
HW2a::paintGL()
{
	// clear canvas with background color
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){//using two for loops to step through the 9 portions
			glLoadIdentity();
			if ((j == 0) && (i == 1)){ //the one needed to be filp over

				glOrtho(-xmax, xmax, ymax, -ymax, -1.0, 1.0);
				glViewport(0, m_winH / 3, m_winW / 3, m_winH / 3);
			}
			else{

				glOrtho(-xmax, xmax, -ymax, ymax, -1.0, 1.0);
				glViewport(m_winW / 3 * j, m_winH / 3 * i, m_winW / 3, m_winH / 3);
			}

			glDrawArrays(drawModes[i * 3 + j], 0, sizeof(vertices)/sizeof(vertices[0]));
		}
	}
}

void
HW2a::aspect(int state)
{
	// update checkbox
	m_checkBoxAR->setChecked(state);

	// call resizeGL() to reset coordinate system
	resizeGL(m_winW, m_winH);

	// redraw
	updateGL();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW0c::reset:
//
// Reset parameters.
//
void
HW2a::reset()
{
	// reset checkboxes
	m_checkBoxAR->setChecked(true);
	resizeGL(m_winW, m_winH);
	// redraw
	updateGL();
}
