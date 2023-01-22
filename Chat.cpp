#include "Chat.h"
#include "Message.h"
#include <string.h> 
#include <memory>
#include <Windows.h>

void Chat::setSelectUser(User& user)
{
	//Устанавливаем текущий авторизированный пользователь
	selectUser_ = findExistUser(user.getLogin(), 1);
}

void Chat::addItemUserList(User &newUser)
{
	userList_.push_back(newUser);
}

std::vector<Message>& Chat::getMessages()
{
	return messageList_;
}

void Chat::start()
{
	chatWork_ = true;
}

void Chat::stop()
{
	chatWork_ = false;
}

bool Chat::getChatWork()
{
	return chatWork_;
}

std::vector<User>& Chat::getUsers()
{
	return userList_;
}

std::shared_ptr<User> Chat::findExistUser(std::string findData, int comandType)
{
	if (comandType == 1)
	{
		for (User& item : Chat::getUsers())
		{
			if (item.getLogin() == findData) //Совпадает ли полученный логин с логином зарегистрированного пользователя
			{
				return std::make_shared<User>(item);
			}
		}
	}
	if (comandType == 2)
	{
		for (User item : Chat::getUsers())
		{
			//Совпадает ли полученный никнейм с никнеймом зарегистрированного пользователя
			if (item.getName() == findData) 
			{ 
				return std::make_shared<User>(item);
			}
		}
	}

	return nullptr;
}

std::shared_ptr<User>& Chat::getSelectUser()
{
	return selectUser_;
}

void Chat::signIn()
{
	bool checkLogin = true;
	bool checkPassword = true;

	std::string enterLogin = ""; //Введенный логин
	std::string enterPassword = ""; //Введенный пароль

	if (userList_.size() > 0)
	{
		do
		{
			std::cout << std::endl << "---------------------------------------Авторизация пользователя----------------------------------------" << std::endl;
			std::cout << " [Введите логин:]" << std::endl << std::endl;

			/*---------------------------Ввод логина---------------------------------*/
			int indexSpace = -1;
			std::cin.ignore();
			std::getline(std::cin, enterLogin); //Считывание логина с клавиатуры
			indexSpace = enterLogin.find(' '); //Поиск пробелов в логине(все знаки кроме пробела допустимы в логине)

			if (indexSpace == -1)
			{
				checkLogin = false; //Логин успешно принят
				/*-----------------------Ввод пароля--------------------------*/
				do
				{
					system("cls");
					std::cout << std::endl << "---------------------------------------Авторизация пользователя----------------------------------------" << std::endl;
					std::cout << " Логин [" << enterLogin << "]" << std::endl; // "] зарегистрирован" << std::endl;

					std::cout << std::endl << " [Введите пароль:]" << std::endl << std::endl;

					int indexSpace = -1;
					std::getline(std::cin, enterPassword); //Считывание пароля с клавиатуры
					indexSpace = enterPassword.find(' '); //Поиск пробелов в пароле

					if (indexSpace == -1)
					{
						checkPassword = false;

						//Проверка есть ли введеный пользоветель среди зарегистрированных
						User* enterUser = nullptr;

						for (User& item : getUsers())
						{
							if (enterLogin == item.getLogin())
							{
								if (enterPassword == item.getPassword())
								{
									setSelectUser(item); //Устанавливаем введенного пользователя как авторирозованного 
									system("cls");
									std::cout << std::endl << " [Пользователь авторизован]" << std::endl;
									break;
								}
								else
								{
									system("cls");
									std::cout << std::endl << " [Пользователь не авторизован(пароль - неверный)]" << std::endl;
								}
							}
							else
							{
								system("cls");
								std::cout << std::endl << " [Среди зарегистрированных пользователей нет логина( " << enterLogin << " )]" << std::endl;
							}
						}
					}
					else
					{
						try
						{
							throw ValidСharactersExeption();
						}
						catch (ValidСharactersExeption e)
						{
							system("cls");
							std::cout << std::endl << " " << e.what() << std::endl;
							continue;
						}
					}
				}
				while (checkPassword);
			}
			else
			{
				try
				{
					throw ValidСharactersExeption();
				}
				catch (ValidСharactersExeption e)
				{
					system("cls");
					std::cout << std::endl << " " << e.what() << std::endl;
					continue;
				}
			}
		}
		while (checkLogin);
	}
	else
	{
		system("cls");
		std::cout << std::endl << " Список пользователей пуст" << std::endl;
	}
}

void Chat::changePassUser()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool checkPassword = true;
	bool checkNewPassword = true;
	bool errorEnterPassword = false; //Отображение ошибки неправильного ввода пароля

	std::string enterPassword; //Введенный пароль
	std::string enterNewPassword; //Введенный новый пароль

	/*-----------------------Ввод пароля--------------------------*/
	do
	{
		if (!errorEnterPassword) 
		{ 
			errorEnterPassword = false;
			system("cls"); 
		}
		std::cout << std::endl << "------------------------Смена пароля пользователя-------------------------" << std::endl;
		std::cout << " Логин [" << getSelectUser()->getLogin() << "]" << std::endl;
		std::cout << " Нимкнейм [" << getSelectUser()->getName() << "]" << std::endl;

		std::cout << std::endl << " [Введите пароль:]" << std::endl << std::endl;

		int indexSpace = -1;
		std::getline(std::cin, enterPassword); //Считывание пароля с клавиатуры
		indexSpace = enterPassword.find(' '); //Поиск пробелов в пароле

		//Проверка на ввод пустого пароля
		if (enterPassword != "")
		{
			//Проверка совпадает ли текущий пароль с введеным
			if (getSelectUser()->getPassword() == enterPassword)
			{ 
				checkPassword = false; 
			}
			else
			{
				system("cls");
				std::cout << std::endl << " [Неправильно введен пароль]" << std::endl;
				errorEnterPassword = true;
				continue;
			}

			//Проверка пароля на символы c кирилицей
			indexSpace = cheсkRussData(enterPassword);
		}
		else { continue; }

		if (indexSpace == -1)
		{
			/*-----------------------Ввод новго пароля--------------------------*/
			do
			{
				std::cout << std::endl << " [Введите новый пароль:]" << std::endl << std::endl;

				int indexSpace = -1;
				std::getline(std::cin, enterNewPassword); //Считывание пароля с клавиатуры
				indexSpace = enterNewPassword.find(' '); //Поиск пробелов в пароле

				//Проверка на ввод пустого пароля
				if (enterNewPassword != "")
				{
					//Проверка пароля на символы c кирилицей
					indexSpace = cheсkRussData(enterNewPassword);
				}
				else { indexSpace = 1; }

				if (indexSpace == -1)
				{
					checkPassword = false; //Новый пароль успешно принят
					//Установка нового пароля

					for (User& user : userList_)
					{
						if (getSelectUser()->getPassword() == enterPassword)
						{
							user.setPassword(enterNewPassword); //Установка нового пароля
							setSelectUser(user); //Выбор текущего пользоателя
							break;
						}
					}
					
					checkNewPassword = false; //Новый пароль установлен

					system("cls");
					std::cout << std::endl << " [Новый пароль успешно установлен]" << std::endl;
				}
				else
				{
					try
					{
						throw ValidСharactersExeption();
					}
					catch (ValidСharactersExeption e)
					{
						//system("cls");
						std::cout << std::endl << " " << e.what() << std::endl;
						continue;
					}
				}
			}
			while (checkNewPassword);
		}
		else
		{
			try
			{
				throw ValidСharactersExeption();
			}
			catch (ValidСharactersExeption e)
			{
				system("cls");
				std::cout << std::endl << " " << e.what() << std::endl;
				continue;
			}
		}
	}
	while (checkPassword);
}

void Chat::addUser()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool checkLogin = true;
	bool checkPassword = true;
	bool checkName = true;
	bool errorInickName = false; //Отображение ошибки исключения при создании уникального никнейма

	std::string enterLogin; //Введенный логин
	std::string enterPassword; //Введенный пароль
	std::string enterName; //Введенный никнейм

	do
	{
		std::cout << std::endl << "------------------------Регистрация нового пользователя-------------------------" << std::endl;
		std::cout << " [Введите логин:]" << std::endl << std::endl;

		/*---------------------------Ввод логина---------------------------------*/
		int indexSpace = -1;

		std::getline(std::cin, enterLogin); //Считывание логина с клавиатуры
		indexSpace = enterLogin.find(' '); //Поиск пробелов в логине(все знаки кроме пробела допустимы в логине)

		//Проверка на ввод пустого логина
		if (enterLogin != "")
		{
			//Проверка логина на символы c кирилицей
			indexSpace = cheсkRussData(enterLogin);

			//Проверка логина на уникальность
			if (findExistUser(enterLogin, 1) != nullptr)
			{
				try
				{
					throw UserLoginUnicExeption();
				}
				catch (UserLoginUnicExeption e)
				{
					system("cls");
					std::cout << std::endl << " " << e.what() << std::endl;
					continue;
				}
			}
		}
		else
		{
			system("cls");
			continue;
		}

		if (indexSpace == -1)
		{
			/*-----------------------Ввод пароля--------------------------*/
			do
			{
				system("cls");
				checkLogin = false; //Логин успешно принят
				std::cout << std::endl << "------------------------Регистрация нового пользователя-------------------------" << std::endl;
				std::cout << " Логин [" << enterLogin << "] успешно принят" << std::endl;

				std::cout << std::endl << " [Введите пароль:]" << std::endl << std::endl;

				int indexSpace = -1;
				std::getline(std::cin, enterPassword); //Считывание пароля с клавиатуры
				indexSpace = enterPassword.find(' '); //Поиск пробелов в пароле

				//Проверка на ввод пустого пароля
				if (enterPassword != "")
				{
					//Проверка пароля на символы c кирилицей
					indexSpace = cheсkRussData(enterPassword);
				}
				else { indexSpace = 1; }

				if (indexSpace == -1)
				{
					/*-----------------------Ввод никнейма--------------------------*/
					do
					{
						if (!errorInickName)
						{
							errorInickName = false;
							system("cls");
						}
						checkPassword = false; //Пароль успешно принят	

						std::cout << std::endl << "------------------------Регистрация нового пользователя-------------------------" << std::endl;
						std::cout << " Логин [" << enterLogin << "] успешно принят" << std::endl;

						std::cout << " Пароль [ ******* ] успешно принят" << std::endl;

						std::cout << std::endl << " [Введите никнейм:]" << std::endl << std::endl;

						int indexSpace = -1;
						std::getline(std::cin, enterName); //Считывание никнейма с клавиатуры
						indexSpace = enterName.find(' '); //Поиск пробелов в никнейме(все знаки кроме пробела допустимы в никнейме)

						//Проверка на ввод пустого пароля
						if (enterName != "")
						{
							indexSpace = -1;

							//Проверка логина на уникальность
							if (findExistUser(enterName, 2) != nullptr)
							{
								try
								{
									throw UserNameUnicExeption();
								}
								catch (UserNameUnicExeption e)
								{
									system("cls");
									std::cout << std::endl << " " << e.what() << std::endl;
									errorInickName = true; //Необходима что сообщение об ошибке не затерлось при прогрузке меню
									continue;
								}
							}
						}
						else { indexSpace = 1; }

						if (indexSpace == -1) { checkName = false; }
						else
						{
							try
							{
								throw ValidСharactersExeption();
							}
							catch (ValidСharactersExeption e)
							{
								system("cls");
								std::cout << std::endl << " " << e.what() << std::endl;
								continue;
							}
						}
					}
					while (checkName);
				}
				else
				{
					try
					{
						throw ValidСharactersExeption();
					}
					catch (ValidСharactersExeption e)
					{
						system("cls");
						std::cout << std::endl << " " << e.what() << std::endl;
						continue;
					}
				}
			}
			while (checkPassword);
		}
		else
		{
			try
			{
				throw ValidСharactersExeption();
			}
			catch (ValidСharactersExeption e)
			{
				system("cls");
				std::cout << std::endl << " " << e.what() << std::endl;
				continue;
			}
		}

		system("cls");
		std::cout << std::endl << "------------------------Регистрация нового пользователя-------------------------" << std::endl;

		std::cout << "  Новый пользователь был успешно зарегистрирован" << std::endl;
		std::cout << "  Логин [" << enterLogin << "] успешно принят" << std::endl;
		std::cout << "  Пароль [ ******* ] успешно принят" << std::endl;
		std::cout << "  Никнейм [" << enterName;
		std::cout << "] успешно принят" << std::endl;

		std::cout << "-------------------------------------------------------------------------------" << std::endl;
	}
	while (checkLogin);

	//Создание пользователя и добавления его в общий список пользователей
	userList_.push_back(User(enterLogin, enterPassword, enterName));
}

void Chat::showMenuUsers()
{
	system("cls");
	workRegistUser_ = true;

	do
	{
		if (getSelectUser() != nullptr)
		{
			std::cout << std::endl << "--------------------------------------------------ЧАТ( ";
			std::cout << getSelectUser()->getName();
			std::cout << " )--------------------------------------------------" << std::endl;
		}
		else
		{
			std::cout << std::endl << "--------------------------------------------------ЧАТ--------------------------------------------------" << std::endl;
		}

		std::cout << " 1: [Регистрация] " << " 2: [Смена пароля] " << " 3: [Список пользователей] " << " 0: [Назад] " << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------" << std::endl;

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
			system("cls");
			addUser(); //Добавить пользователя

			break;
		case 2:
			system("cls");
			//Смена пароля текущего пользователя
			changePassUser();

			break;
		case 3:
			system("cls");

			//Вывод списка всех пользователей
			if (getUsers().size() > 0)
			{
				std::cout << std::endl << "---------------------------------Список зарегистрированных пользователей:------------------------------" << std::endl;
				for (User& item : getUsers())
				{
					std::cout << " Логин: " << item.getLogin() << " - [Никнейм: " << item.getName() << "]" << std::endl;
				}
				std::cout << "-------------------------------------------------------------------------------------------------------" << std::endl;
			}

			break;
		case 0:
			system("cls");
			workRegistUser_ = false;

			break;
		case -1:
			system("cls");
			std::cout << std::endl << " [Неправильно введена команда]" << std::endl;

			break;
		default:
			system("cls");
			std::cout << std::endl << " [Неправильно введена команда]" << std::endl;
		}
	}
	while (workRegistUser_);
}

void Chat::showChat(std::shared_ptr<User> user)
{
	//Вывод списка всех пользователей
	if (getMessages().size() > 0)
	{
		std::cout << std::endl << "---------------------------------Сообщения для пользователя "; 
		std::cout << selectUser_->getName();
		std::cout << ":------------------------------" << std::endl;
				
		for (Message& item : getMessages())
		{								
			if (user->getName() == item.getReciever()) //Поиск путем сравнения никнеймов переданного пользователя и 
			{
				std::cout << " [" << item.getReciever() << "]: " << item.getMessage() << std::endl;
			}
		}
		std::cout << "-------------------------------------------------------------------------------------------------------" << std::endl;
	}
}

void Chat::sendMessage()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool checkName = true;
	bool checkMessage = true;
	int errorFlag = -1; //-1 - нет ошибок, 1 - возникла ошибка

	std::string enterName; //Введенный никнейм
	std::string enterMessage; //Введенное сообщение

	do
	{
		system("cls");
		std::cout << std::endl << "------------------------Отправка сообщения-------------------------" << std::endl;
		std::cout << " [Введите никнейм( All/Все - для отправки всем )]:" << std::endl << std::endl;

		/*---------------------------Ввод никнейма---------------------------------*/
		std::getline(std::cin, enterName); //Считывание логина с клавиатуры

		//Проверка на ввод пустого логина
		if (enterName != "") { errorFlag = -1; }
		else { errorFlag = 1; }

		if (errorFlag == -1)
		{
			/*-----------------------Ввод сообщения--------------------------*/
			do
			{
				system("cls");
				checkName = false; //Пользователь с таким ником есть среди зарегистрироваших, поэтому останавливаем ввод
				std::cout << std::endl << "------------------------Отправка сообщения-------------------------" << std::endl;
				std::cout << " Получатель [" << enterName << "]:" << std::endl;

				std::cout << std::endl << " [Введите сообщение:]" << std::endl << std::endl;

				errorFlag = -1; //Сбрасываем флаг ошибки
				std::getline(std::cin, enterMessage); //Считывание сообщение с клавиатуры

				//Проверка на ввод пустого сообщения
				if (enterMessage != "")
				{
					errorFlag = -1;
				}
				else
				{
					errorFlag = 1;
				}

				if (errorFlag == -1)
				{
					checkMessage = false; //Пользователь с введённым ником зарегистрирован	
				}
				else
				{
					try
					{
						throw ValidСharactersExeption();
					}
					catch (ValidСharactersExeption e)
					{
						system("cls");
						std::cout << std::endl << " " << e.what() << std::endl;
						continue;
					}
				}
			}
			while (checkMessage);
		}
		else
		{
			try
			{
				throw ValidСharactersExeption();
			}
			catch (ValidСharactersExeption e)
			{
				system("cls");
				std::cout << std::endl << " " << e.what() << std::endl;
				continue;
			}
		}

		system("cls");
		std::cout << std::endl << "------------------------Отправка сообщения-------------------------" << std::endl;
		std::cout << " [ Сообщение успешно отправлено ]" << std::endl;
		std::cout << " [ Получатель ] " << enterName << std::endl;
		std::cout << " [ Сообщение ] " << enterMessage << std::endl;

		std::cout << "-------------------------------------------------------------------------------" << std::endl;
	}
	while (checkName);

	//Создание сообщения и добавления его в общий список сообщений
	messageList_.push_back(Message(getSelectUser()->getName(), enterName, enterMessage));
}

void Chat::showMenuChat()
{
	system("cls");
	workRegistUser_ = true;

	do
	{
		if (getSelectUser() != nullptr)
		{
			std::cout << std::endl << "---------------------------------------ЧАТ( Пользователь: ";
			std::cout << getSelectUser()->getName();
			std::cout << " )----------------------------------------" << std::endl;
		}
		else
		{
			std::cout << std::endl << "--------------------------------------------------ЧАТ--------------------------------------------------" << std::endl;
		}

		std::cout << " 1: [Отправить]" << "		2: [Прочитать] " << "		0: [Назад] " << std::endl;
		std::cout << "-------------------------------------------------------------------------------------------------------" << std::endl;

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
			system("cls");

			{
				std::string reciver = "";
				std::string message = "";

				//(Логин - для авторизации, никнейм - для отправки и приема сообщений)
				//Послать сообщение от selectUser_ пользователю с ником reciver
				sendMessage(); //Отправить сообщение
			}

			break;
		case 2:
			system("cls");

			std::cout << " Список сообщений для (" << getSelectUser()->getName() << "):" << std::endl;

			//Вывод списка всех сообщений для пользователя
			if (getMessages().size() > 0)
			{
				int countMessage = 0;
				for (User& user : getUsers())
				{
					for (Message& message : getMessages())
					{
						//Сообщение можно отправить отдельному пользователю или всем(указав Все или All при вводе никнейма отправителя)
						if ((message.getReciever() == getSelectUser()->getName()) || (message.getReciever() == "Все") || (message.getReciever() == "All"))
						{
							if (user.getName() == message.getSender())
							{
								std::cout << " [ Отправитель ] " << message.getSender() << " [ Сообщение ] " << message.getMessage() << std::endl;
								countMessage++;
							}
						}
					}

					std::cout << std::endl;
				}

				std::cout << " [Количество сообщений] :" << countMessage << std::endl;
				std::cout << "-------------------------------------------------------------------------------------------------------" << std::endl;
			}
			else
			{
				std::cout << " [Количество сообщений] : 0" << std::endl;
			}

			break;
		case 0:
			system("cls");
			workRegistUser_ = false;

			break;
		case -1:
			system("cls");
			std::cout << std::endl << " [Неправильно введена команда]" << std::endl;

			break;
		default:
			system("cls");
			std::cout << std::endl << " [Неправильно введена команда]" << std::endl;
		}
	}
	while (workRegistUser_);
}

int Chat::cheсkRussData(std::string data)
{
	//Проверка пароля на символы c кирилицей
	for (char& ch : data)
	{
		if ((ch >= 'А' && ch <= 'Я') || (ch >= 'а' && ch <= 'я'))
		{
			return 1; //Вернется это значение если найден хоть один символ с кирилицей
		}
	}
	return -1; //Символов с кирилицей нету
}
