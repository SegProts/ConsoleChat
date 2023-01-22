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
		return " [ОШИБКА]: Введенный логин уже занят";
	}
};

class UserNameUnicExeption : public std::exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "[ОШИБКА]: Введенный никнейм уже занят";
	}
};

class ValidСharactersExeption : public std::exception
{
public:
	virtual const char* what() const noexcept override
	{
		return "[ОШИБКА]: Введён недопустимый символ";
	}
};

class Chat
{
	bool chatWork_ = 0; //Чат работает
	std::shared_ptr<User> selectUser_ = nullptr; //Авторизованный на данный момент пользователь
	bool workLogUser_ = false; //Происходит вход зарегистрированного пользователя
	bool workRegistUser_ = false; //Происходит регистрация нового пользователя
	std::vector<User> userList_; //Список всех зарегистрированных пользователей
	std::vector<Message> messageList_; //Список всех сообщений
public:
	std::vector<User>& getUsers(); //Получить всех пользователей
	std::vector<Message>& getMessages();
	std::shared_ptr<User>& getSelectUser();

	//Вернет ссылку на пользователя, если зарегистрирован(иначен nullptr). 
	std::shared_ptr<User> findExistUser(std::string findData, int comandType);

	//(Логин - для авторизации, никнейм - для отправки и приема сообщений)
	void sendMessage(); //Послать сообщение от selectUser_ выбранному пользователю

	void start(); //Запустить чат
	void stop(); //Остановить чат

	void setSelectUser(User& user);

	void addUser(); //Добавить нового пользователя
	void changePassUser(); //Поменять пароль текущего авторизованого пользователя

	bool getChatWork(); //Проверить работает ли чат
	void addItemUserList(User& newUser);
	void signIn(); //Войти по логину и паролю
	void showMenuUsers(); //Показать меню Пользователи
	void showMenuChat(); //Показать меню Чат
	int cheсkRussData(std::string data); //Проверяет строки на налициче символов с кирилицей
};