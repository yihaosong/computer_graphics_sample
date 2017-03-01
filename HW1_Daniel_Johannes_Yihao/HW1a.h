// ======================================================================
// Computer Graphics Homework Solutions
// Copyright (C) 2015 by George Wolberg
//
// HW0b.h - Header file for HW0b class
//
// Written by: George Wolberg, 2015
// ======================================================================

#ifndef HW1A_H
#define HW1A_H


#include "HW.h"


// ----------------------------------------------------------------------
// standard include files
//

class HW1A : public HW {
	Q_OBJECT
public:
	HW1A(QWidget *parent = 0);		// constructor
	QGroupBox*	controlPanel();		// create control panel
	void		reset();		// reset parameters

	public slots:
	void		flipY(int);		// flip y-coordinate
	void		aspect(int);		// maintain aspect ratio
	void		rotate(int);		// rotate data

protected:
	void		initializeGL();		// init GL state
	void		resizeGL(int, int);	// resize GL widget
	void		paintGL();		// render GL scene

private:
	float xmax, ymax; //useful for flipping on the fly
	int		 m_winW;			// window width
	int		 m_winH;			// window height
	double		 m_angle;			// rotation angle
	QCheckBox	*m_checkBoxFlip;		// checkbox to flip y-coordinate
	QCheckBox	*m_checkBoxAR;			// checkbox to maintain aspect ratio
	QSlider		*m_slider;			// rotation slider
	QSpinBox	*m_spinBox;			// rotation spinbox
};

#endif // HW1A_H
