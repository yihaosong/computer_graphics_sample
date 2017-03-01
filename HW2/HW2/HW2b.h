// ======================================================================
// Computer Graphics Homework Solutions
// Copyright (C) 2015 by George Wolberg
//
// HW0c.h - Header file for HW0c class
//
// Written by: George Wolberg, 2015
// ======================================================================

#ifndef HW2B_H
#define HW2B_H

#include "HW.h"
#include <QGLShaderProgram>
#include <QtOpenGL>
#include <vector>
#include <iostream>

// ----------------------------------------------------------------------
// standard include files
//

class HW2b : public HW {
	Q_OBJECT
public:
	HW2b(QWidget *parent = 0);		// constructor
	QGroupBox*	controlPanel();		// create control panel
	void		reset();		// reset parameters
	void		initVertexBuffer();		// init vertices
	void		initShaders();		// init shaders

	public slots:
	void		changeTheta(int);		// respond to rotation slider
	void		subdivide(int);		// respond to rotation slider
	void		twistChanged(int);		// respond to rotation slider
	void		reverseChanged(bool);			// respond to color reversal (on)

protected:
	void		initializeGL();		// init GL state
	void		resizeGL(int, int);	// resize GL widget
	void		paintGL();		// render GL scene

	void		mousePressEvent(QMouseEvent *);
	void		mouseMoveEvent(QMouseEvent *);
	void		mouseReleaseEvent(QMouseEvent *);

private:
	//points of the original triangle
	float pointA[2];// = { -0.7f, -0.4041f };
	float pointB[2];// = { 0.7f, -0.4041f };
	float pointC[2];// = { 0, 0.8083f };
	int		  m_winW;			// window width
	int		  m_winH;			// window height
	QGLShaderProgram  m_program;			// GLSL program
	bool		  m_reverseColor;		// reverse color flag
	bool		  m_twist;		// reverse color flag
	QSlider		 *m_sliderTheta;		// rotation slider
	QSlider		 *m_sliderSubdivide;
	QCheckBox	 *m_checkBoxTwist;
	QSpinBox	 *m_spinBoxTheta;		// rotation spinbox
	QSpinBox	 *m_spinBoxSubdivide;		// rotation spinbox
	QRadioButton	 *m_radio[2];			// radio button for reversing color
	std::vector<vec2> m_points;			// vector of 2D points (XY)
	std::vector<vec3> m_colors;			// vector of 3D colors (RGB)
	int		  m_numPoints;			// number of 2D points
	int		  subdivisions; //variable to hold subdiv values...
	GLfloat	  m_u_theta;		// 4x4 transformation matrix
	GLuint		  m_u_reverseColor;		// shader index to color reversal flag
	GLuint		  m_u_twist;		// shader index to color reversal flag
	QPoint		  m_mousePosition;		// latest mouse position
	void divideTriangle(float*, float*, float*, int);
};

#endif // HW02C_H
