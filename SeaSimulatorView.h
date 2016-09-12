#ifndef SEASIMULATOR_VIEW_H
#define SEASIMULATOR_VIEW_H

#include "SeaSimulatorModel.h"

constexpr unsigned DEFAULT_SCALE = 2;
constexpr unsigned DEFAULT_VIEW_SIZE = 25;

class SeaSimulatorView {

	int origin_x, origin_y;
	unsigned view_size, scale;

public:

	SeaSimulatorView();
	~SeaSimulatorView();

	void setOrigin(int , int );
	void setScale(unsigned );
	void setSize(unsigned );
	void reset();

	void printHeader();
	void DrawASCII(SeaSimulatorModel& _model);

};

#endif