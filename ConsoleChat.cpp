#include <iostream>
#include "Chat.h"
#include "Windows.h"


using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Chat chat;

	/*---------Временный код создающий двух пользователей(Admin(никнейм: Admin, пароль: admin), seg(Seg, seg))--------*/

	std::string enterLogin = "seg";
	std::string enterPassword = "seg";
	std::string enterName = "Seg";

	User user = User(enterLogin, enterPassword, enterName);

	chat.setSelectUser(user);
	//Создание пользователя и добавления его в общий список пользователей
	bool addUser(); //Добавить нового пользователя

	User us = User(enterLogin, enterPassword, enterName);

	chat.addItemUserList(us);

	enterLogin = "admin";
	enterPassword = "admin";
	enterName = "Admin";

	user = User(enterLogin, enterPassword, enterName);

	chat.setSelectUser(user);
	//Создание пользователя и добавления его в общий список пользователей
	bool addUser(); //Добавить нового пользователя

	us = User(enterLogin, enterPassword, enterName);

	chat.addItemUserList(us);
	chat.setSelectUser(us);

	/*----------------------------------------------------------------------------------------------------------------*/

	chat.start();

	do
	{
		if (chat.getSelectUser() != nullptr)
		{		
			std::cout << std::endl << "---------------------------------------ЧАТ( Пользователь: ";
			//setlocale(LC_ALL, ".866");
			std::cout << chat.getSelectUser()->getName();
			//setlocale(LC_ALL, "Russian");
			std::cout << " )----------------------------------------" << std::endl;
		}
		else
		{
			std::cout << std::endl << "--------------------------------------------------ЧАТ--------------------------------------------------" << std::endl;
		}

		cout << " 1: [Вход]	" << " 2: [Пользователи]	" << " 3: [Чат]	" << " 0: [Закрыть]" << endl;
		std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl << std::endl;

		std::string enterComand;
		int selectComand = 0;

		std::cin >> enterComand;

		try
		{
			selectComand = stoi(enterComand);
		}
		catch (std::invalid_argument)
		{
			selectComand = -1;
		}

		switch (selectComand)
		{
		case 1:
			chat.signIn();
			break;
		case 2:
			chat.showMenuUsers();
			break;
		case 3:
			chat.showMenuChat();
			break;
		case 0:
			chat.stop();
			return 0;
		case -1:
			system("cls");
			cout << endl << " [Неправильно введена команда]" << endl;
			break;
		default:
			system("cls");
			cout << endl << " [Неправильно введена команда]" << endl;
		}
	}
	while (chat.getChatWork());

	return 0;
}