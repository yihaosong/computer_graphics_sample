// ======================================================================
// Computer Graphics Homework Solutions
// Copyright (C) 2015 by George Wolberg
//
// HW0b.h - Header file for HW0b class
//
// Written by: George Wolberg, 2015
// ======================================================================

#ifndef HW1B_H
#define HW1B_H


#include "HW.h"
#include <vector>

// ----------------------------------------------------------------------
// standard include files
//

class HW1b : public HW {
	Q_OBJECT
public:
	HW1b(QWidget *parent = 0);		// constructor
	~HW1b();						// destructor
	QGroupBox*	controlPanel();		// create control panel
	void		reset();		// reset parameters

	public slots:
	void		flipY(int);		// flip y-coordinate
	void		twist();		// twist
	void		aspect(int);		// maintain aspect ratio
	void		rotate(int);		// rotate data
	void		subdivide(int);		// rotate data

protected:
	void		initializeGL();		// init GL state
	void		resizeGL(int, int);	// resize GL widget
	void		paintGL();		// render GL scene

private:
	int		 m_winW;			// window width
	int		 m_winH;			// window height
	double	 m_angle;			// rotation angle
	QPointF * orig_a;
	QPointF * orig_b;
	QPointF * orig_c;
	std::vector<QColor*> Colors;
    std::vector<QPointF*> Points; 
	QCheckBox	*m_checkBoxFlip;		// checkbox to flip y-coordinate
	QCheckBox	*m_checkBoxAR;			// checkbox to maintain aspect ratio
	QCheckBox	*m_checkBoxTwist;			// checkbox for twisting
	QSlider		*m_slider;			// rotation slider
	QSpinBox	*m_spinBox;			// rotation spinbox
	QSlider		*m_sliderSubdiv;			// Subdivisions slider
	QSpinBox	*m_spinBoxSubdiv;			// Subdivisions spinbox
	void divideTriangle(QPointF * a, QPointF * b, QPointF * c, int divisions);
	QPointF * midpoint(QPointF * a, QPointF * b);
};

#endif // HW1B_H
