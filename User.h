#pragma once
#include <string>


class User
{
	std::string login_;
	std::string password_;
	std::string name_;

public:
	User(std::string& login, std::string& password, std::string& name) :
		login_(login), password_(password), name_(name)
	{}

	std::string getLogin();
	void setLogin(std::string login);

	std::string getPassword();
	void setPassword(std::string password);

	std::string getName();
	void setName(std::string name);

};