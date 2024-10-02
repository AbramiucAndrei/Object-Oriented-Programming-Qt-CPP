#pragma once
#include <exception>
#include <string>
using namespace std;
class RepoExp:public exception
{
private:
	string exc;
public:
	RepoExp(string exception):exc("RepoException: " + exception) {}
	const char* what() const override{
		return exc.c_str();
	}
};

class RepositoryError : public std::runtime_error {
public:
	explicit RepositoryError(const std::string& message) : std::runtime_error(message) {}
};