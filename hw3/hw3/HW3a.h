// ======================================================================
// Computer Graphics Homework Solutions
// Copyright (C) 2015 by George Wolberg
//
// HW3a.h - Header file for HW3a class
//
// Written by: George Wolberg, 2015
// ======================================================================

#ifndef HW3A_H
#define HW3A_H


#include "HW.h"
#include <QGLShaderProgram>
#include <QtOpenGL>


// ----------------------------------------------------------------------
// standard include files
//

class HW3a : public HW {
	Q_OBJECT
public:
	HW3a(QWidget *parent = 0);		// constructor
	QGroupBox*	controlPanel();		// create control panel
	void		reset();		// reset parameters
	void		initVertexBuffer();		// init vertices
	void		initShaders();		// init shaders
	void		initTexture();		// init texture image

	public slots:
	void		changeTheta(int);		// respond to rotation slider
	void		changeSubdiv(int);		// respond to subdivision slider
	void		changeTwist(int);		// respond to twist checkbox
	void		changeWire(int);		// respond to wireframe checkbox

protected:
	void		initializeGL();		// init GL state
	void		resizeGL(int, int);	// resize GL widget
	void		paintGL();		// render GL scene
	//void		divideTriangle(vec2, vec2, vec2, int);	// subdivide triangle
	void divideTriangle(float*, float*, float*, int); //my own version...
	void		triangle(vec2, vec2, vec2);	// process single triangle
	void		initShader1();		// texture mapping shader
	void		initShader2();		// wireframe rendering shader

private:
	std::vector<float> aPointx, aPointy, bPointx, bPointy, cPointx, cPointy, colorR, colorG, colorB;
	//points of the original triangle
	float pointA[2];// = { -0.7f, -0.4041f };
	float pointB[2];// = { 0.7f, -0.4041f };
	float pointC[2];// = { 0, 0.8083f };
	int		  m_winW;			// window width
	int		  m_winH;			// window height
	QGLShaderProgram  m_program[2];			// GLSL programs
	bool		  m_twist;			// twist flag
	bool		  m_wire;			// wireframe flag
	float		  m_theta;			// rotation angle
	int		  m_subdivisions;		// triangle subdivisions
	int		  subdivisions; //variable to hold subdiv values...
	QSlider		 *m_sliderTheta;		// rotation slider
	QSlider		 *m_sliderSubdiv;		// subdivision slider
	QSpinBox	 *m_spinBoxTheta;		// rotation spinbox
	QSpinBox	 *m_spinBoxSubdiv;		// subdivision spinbox
	QCheckBox	 *m_checkBoxTwist;		// twist checkbox
	QCheckBox	 *m_checkBoxWire;		// wireframe checkbox
	std::vector<vec2> m_points;			// vector of 2D points (XY)
	std::vector<vec2> m_coords;			// vector of 2D coords (UV)
	int		  m_numPoints;			// number of 2D points
	QImage		  m_image;			// texture image
	GLuint		  m_texture;			// shader index to texture unit
	GLint		  m_uniform[2][16];		// uniform vars for two shaders and <16 vars
};

#endif // HW3A_H
