#pragma once
#include <string>

class Message
{
	std::string reciever_;
	std::string sender_;
	std::string message_;

public:
	Message(std::string sender, std::string resiever, std::string message) :
		sender_(sender), reciever_(resiever), message_(message)
	{}

	std::string getSender();
	void setSender(std::string sender);

	std::string getReciever();
	void setReciever(std::string resiever);

	std::string getMessage();
	void setMessage(std::string ότϋϋτοσ);
};
