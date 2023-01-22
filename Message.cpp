#include "Message.h"


std::string Message::getSender()
{
	return sender_;
}

void Message::setSender(std::string sender)
{
	sender_ = sender;
}


std::string Message::getReciever()
{
	return reciever_;
}

void Message::setReciever(std::string reciever)
{
	reciever_ = reciever;
}

std::string Message::getMessage()
{
	return message_;
}

void Message::setMessage(std::string message)
{
	message_ = message;
}
