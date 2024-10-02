#include <string>
#include <exception>
using namespace std;


class ServiceExp :public exception {
private:
	string exc;
public:
	ServiceExp(string exception):exc("ServiceException: " + exception) {}
	const char* what() const override{
		return exc.c_str();
	}
};