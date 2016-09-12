#ifndef SEAOBJECTMAKER_H
#define SEAOBJECTMAKER_H

template <class T>
class SeaObjectMaker {

public:

	SeaObjectMaker() { }
	SeaObjectMaker(const SeaObjectMaker&) = delete;
	SeaObjectMaker& operator= (const SeaObjectMaker&) = delete;
	SeaObjectMaker(const SeaObjectMaker&&) = delete;
	SeaObjectMaker& operator= (SeaObjectMaker&&) = delete;
	~SeaObjectMaker() {}
	static std::shared_ptr<T> make(const std::string& new_name, double x_pos, double y_pos, unsigned arg1, unsigned arg2);

};

template <class T>
std::shared_ptr<T> SeaObjectMaker<T>::make(const std::string& new_name, double x_pos, double y_pos, unsigned arg1, unsigned arg2) {

	auto instance = std::make_shared<T>(new_name, x_pos, y_pos, arg1, arg2);
	return instance;

}

#endif