#include <string>
#include <exception>
using namespace std;


class ValidatorExp :public exception {
private:
	string exc;
public:
	ValidatorExp(string exception) :exc("\nValidatorException: " + exception) {}
	const char* what() const override {
		return exc.c_str();
	}
};