#pragma once
#include <vector>
#include <memory>
#include "User.h"
#include "Message.h"
#include <iostream>
#include <locale.h>

class UserLoginUnicExeption : public std::exception
{
public:
	virtual const char* what() const noexcept override
	{
		return " [������]: ��������� ����� ��� �����";
	}
};

class UserNameUnicExeption : public std::exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "[������]: ��������� ������� ��� �����";
	}
};

class Valid�haractersExeption : public std::exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "[������]: ����� ������������ ������";
	}
};

class Chat
{
	bool chatWork_ = 0; //��� ��������
	std::shared_ptr<User> selectUser_ = nullptr; //�������������� �� ������ ������ ������������
	bool workLogUser_ = false; //���������� ���� ������������������� ������������
	bool workRegistUser_ = false; //���������� ����������� ������ ������������
	std::vector<User> userList_; //������ ���� ������������������ �������������
	std::vector<Message> messageList_; //������ ���� ���������
public:
	std::vector<User>& getUsers(); //�������� ���� �������������
	std::vector<Message>& getMessages();
	std::shared_ptr<User>& getSelectUser();

	//������ ������ �� ������������, ���� ���������������(������ nullptr). 
	std::shared_ptr<User> findExistUser(std::string findData, int comandType);

	void showChat(std::shared_ptr<User> user); //���������� ��� ��� ����������� ������������

	//(����� - ��� �����������, ������� - ��� �������� � ������ ���������)
	void sendMessage(); //������� ��������� �� selectUser_ ���������� ������������

	void start(); //��������� ���
	void stop(); //���������� ���

	void setSelectUser(User& user);

	void addUser(); //�������� ������ ������������
	void changePassUser(); //�������� ������ �������� �������������� ������������

	bool getChatWork(); //��������� �������� �� ���
	void addItemUserList(User& newUser);
	void signIn(); //����� �� ������ � ������
	void showMenuUsers(); //�������� ���� ������������
	void showMenuChat(); //�������� ���� ���
	int che�kRussData(std::string data); //��������� ������ �� �������� �������� � ���������
};