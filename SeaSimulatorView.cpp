#include "SeaSimulatorView.h"

SeaSimulatorView::SeaSimulatorView() { origin_x = -20, origin_y = -20, scale = 5, view_size = DEFAULT_VIEW_SIZE; }

SeaSimulatorView::~SeaSimulatorView() {}

void SeaSimulatorView::setOrigin(int x, int y) { origin_x = x, origin_y = y; }

void SeaSimulatorView::setScale(unsigned new_scale) { scale = new_scale; }

void SeaSimulatorView::setSize(unsigned new_view_size) { view_size = new_view_size; }

void SeaSimulatorView::reset() { origin_x = 0, origin_y = 0, scale = DEFAULT_SCALE, view_size = DEFAULT_VIEW_SIZE; }

void SeaSimulatorView::printHeader() {
	std::cout << "Display size: " << view_size << ", Scale: " << scale << ", Origin: (" << origin_x << ", " << origin_y << ")" << std::endl;
}

void SeaSimulatorView::DrawASCII(SeaSimulatorModel& _model) {
	printHeader();
	//spaces between each indicator
	int seperator = 3;
	//diff between each indicator
	int step_indicator = (seperator * scale);
	//X axis start
	int start_x_indicator = origin_x;
	//Y axis end
	int last_y_indicator = origin_y + (scale*(view_size - 1));
	//Scan direction is left to right, starting from above
	int start_scan_range_x = origin_x;
	int start_scan_range_y = last_y_indicator + scale;

	for (unsigned i = view_size; i > 0; i--) {

		//Y axis
		//Y axis indicators
		//indicator has to be printed:
		if ((i - 1) % seperator == 0) {
			//number length = 1 (0-9)
			if (-1 < last_y_indicator && last_y_indicator < 10) std::cout << "   ";
			//number length = 2 (-9 to -1 , 10 to 99)
			if ((last_y_indicator > 9 && last_y_indicator < 100) || (-10 < last_y_indicator && last_y_indicator < 0)) std::cout << "  ";
			//number length = 3 (-99 to -10 , 100 to 999)
			if (last_y_indicator > 99 || (-100 < last_y_indicator && last_y_indicator < -9)) std::cout << " ";
			//number length = 4 ( -999 to -100 , 1000 to 9999)
			std::cout << last_y_indicator;
		}
		//else
		else {
			std::cout << "   |";
		}
		//decrease Y indicator for next iteration
		last_y_indicator -= scale;

		//content
		for (int j = view_size; j > 0; j--) {

			//calculate limits of scan ranges by round_single_cell_size
			int end_scan_range_x = start_scan_range_x + scale;
			int end_scan_range_y = start_scan_range_y - scale;
			//now we have defined ranges to scan, using ObjectinRange we will find if there are any objects
			//scan direction from above to bottom and left to right therefore:
			//end_scan_range_y < start_scan_range_y but start_scan_range_x < end_scan_range_x
			std::string found = _model.whoIsAt(start_scan_range_x, end_scan_range_x, end_scan_range_y, start_scan_range_y);
			if (found.size() >= 2) {
				//place shorted port name
				std::cout << found.substr(0, 2);
			}
			else {
				//empty space
				std::cout << " .";
			}
			//inner loop move right across X axis
			start_scan_range_x += scale;
		}
		//outer loop move down across Y axis
		start_scan_range_y -= scale;
		//reset X every loop
		start_scan_range_x = origin_x;
		std::cout << std::endl;
	}

	//X axis
	for (unsigned i = 0; i < view_size%seperator + view_size / seperator; i++) {

		//origin x indicator

		if (i == 0) {
			//number length = 1 (0-9)
			if (-1 < start_x_indicator && start_x_indicator < 10) std::cout << "     ";
			//number length = 2 (-9 to -1 , 10 to 99)
			else if ((9 < start_x_indicator && start_x_indicator < 100) || (-10 < start_x_indicator && start_x_indicator < 0)) std::cout << "    ";
			//number length = 3 (-99 to -10 , 100 to 999)
			else if ((99 < start_x_indicator && start_x_indicator < 1000) || (-100 < start_x_indicator && start_x_indicator < -9)) std::cout << "   ";
			//number length = 4 ( -999 to -100 , 1000 to 9999)
			else std::cout << "  ";
		}
		std::cout << start_x_indicator;

		//other X axis indicators
		int next_x_indicator = start_x_indicator + step_indicator;
		//X axis indicators compatability
		if (-1 < next_x_indicator && next_x_indicator < 10) std::cout << "     ";
		//number length = 2 (-9 to -1 , 10 to 99)
		else if ((9 < next_x_indicator  && next_x_indicator < 100) || (-10 < next_x_indicator && next_x_indicator < 0)) std::cout << "    ";
		//number length = 3 (-99 to -10 , 100 to 999)
		else if ((99 < next_x_indicator && next_x_indicator < 1000) || (-100 < next_x_indicator && next_x_indicator < -9)) std::cout << "   ";
		//number length = 4 ( -999 to -100 )
		else std::cout << " ";
		//increase start indicator represents moving across X axis
		start_x_indicator = next_x_indicator;

	}
	std::cout << std::endl;
}
