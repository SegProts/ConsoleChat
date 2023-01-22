#include "User.h"

std::string User::getLogin()
{
	return login_;
}

void User::setLogin(std::string login)
{
	login_ = login;
}

std::string User::getPassword()
{
	return password_;
}

void User::setPassword(std::string password)
{
	password_ = password;
}

std::string User::getName()
{
	return name_;
}

void User::setName(std::string name)
{
	name_ = name;
}