#ifndef HW2A_H
#define HW2A_H

#include "HW.h"
#include <QGLShaderProgram>
#include <QtOpenGL>
#include <iostream>

// ----------------------------------------------------------------------
// standard include files
//

class HW2a : public HW {
	Q_OBJECT
public:
	HW2a(QWidget *parent = 0);		// constructor
	QGroupBox*	controlPanel();		// create control panel
	void		reset();		// reset parameters
	void		initVertexBuffer();		// init vertices
	void		initShaders();		// init shaders

protected:
	void		initializeGL();		// init GL state
	void		resizeGL(int, int);	// resize GL widget
	void		paintGL();		// render GL scene

public slots:
	void		aspect(int);		// maintain aspect ratio

private:
	float xmax, ymax; //useful for flipping on the fly
	int		 m_winW;			// window width
	int		 m_winH;			// window height
	QCheckBox	*m_checkBoxAR;			// checkbox to maintain aspect ratio
	QGLShaderProgram  m_program;			// GLSL program
};

#endif \
