#include "Chat.h"
#include "Message.h"
#include <string.h> 
#include <memory>
#include <Windows.h>

void Chat::setSelectUser(User& user)
{
	//������������� ������� ���������������� ������������
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
			if (item.getLogin() == findData) //��������� �� ���������� ����� � ������� ������������������� ������������
			{
				return std::make_shared<User>(item);
			}
		}
	}
	if (comandType == 2)
	{
		for (User item : Chat::getUsers())
		{
			//��������� �� ���������� ������� � ��������� ������������������� ������������
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

	std::string enterLogin = ""; //��������� �����
	std::string enterPassword = ""; //��������� ������

	if (userList_.size() > 0)
	{
		do
		{
			std::cout << std::endl << "---------------------------------------����������� ������������----------------------------------------" << std::endl;
			std::cout << " [������� �����:]" << std::endl << std::endl;

			/*---------------------------���� ������---------------------------------*/
			int indexSpace = -1;
			std::cin.ignore();
			std::getline(std::cin, enterLogin); //���������� ������ � ����������
			indexSpace = enterLogin.find(' '); //����� �������� � ������(��� ����� ����� ������� ��������� � ������)

			if (indexSpace == -1)
			{
				checkLogin = false; //����� ������� ������
				/*-----------------------���� ������--------------------------*/
				do
				{
					system("cls");
					std::cout << std::endl << "---------------------------------------����������� ������������----------------------------------------" << std::endl;
					std::cout << " ����� [" << enterLogin << "]" << std::endl; // "] ���������������" << std::endl;

					std::cout << std::endl << " [������� ������:]" << std::endl << std::endl;

					int indexSpace = -1;
					std::getline(std::cin, enterPassword); //���������� ������ � ����������
					indexSpace = enterPassword.find(' '); //����� �������� � ������

					if (indexSpace == -1)
					{
						checkPassword = false;

						//�������� ���� �� �������� ������������ ����� ������������������
						User* enterUser = nullptr;

						for (User& item : getUsers())
						{
							if (enterLogin == item.getLogin())
							{
								if (enterPassword == item.getPassword())
								{
									setSelectUser(item); //������������� ���������� ������������ ��� ����������������� 
									system("cls");
									std::cout << std::endl << " [������������ �����������]" << std::endl;
									break;
								}
								else
								{
									system("cls");
									std::cout << std::endl << " [������������ �� �����������(������ - ��������)]" << std::endl;
								}
							}
							else
							{
								system("cls");
								std::cout << std::endl << " [����� ������������������ ������������� ��� ������( " << enterLogin << " )]" << std::endl;
							}
						}
					}
					else
					{
						try
						{
							throw Valid�haractersExeption();
						}
						catch (Valid�haractersExeption e)
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
					throw Valid�haractersExeption();
				}
				catch (Valid�haractersExeption e)
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
		std::cout << std::endl << " ������ ������������� ����" << std::endl;
	}
}

void Chat::changePassUser()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool checkPassword = true;
	bool checkNewPassword = true;
	bool errorEnterPassword = false; //����������� ������ ������������� ����� ������

	std::string enterPassword; //��������� ������
	std::string enterNewPassword; //��������� ����� ������

	/*-----------------------���� ������--------------------------*/
	do
	{
		if (!errorEnterPassword) 
		{ 
			errorEnterPassword = false;
			system("cls"); 
		}
		std::cout << std::endl << "------------------------����� ������ ������������-------------------------" << std::endl;
		std::cout << " ����� [" << getSelectUser()->getLogin() << "]" << std::endl;
		std::cout << " �������� [" << getSelectUser()->getName() << "]" << std::endl;

		std::cout << std::endl << " [������� ������:]" << std::endl << std::endl;

		int indexSpace = -1;
		std::getline(std::cin, enterPassword); //���������� ������ � ����������
		indexSpace = enterPassword.find(' '); //����� �������� � ������

		//�������� �� ���� ������� ������
		if (enterPassword != "")
		{
			//�������� ��������� �� ������� ������ � ��������
			if (getSelectUser()->getPassword() == enterPassword)
			{ 
				checkPassword = false; 
			}
			else
			{
				system("cls");
				std::cout << std::endl << " [����������� ������ ������]" << std::endl;
				errorEnterPassword = true;
				continue;
			}

			//�������� ������ �� ������� c ���������
			indexSpace = che�kRussData(enterPassword);
		}
		else { continue; }

		if (indexSpace == -1)
		{
			/*-----------------------���� ����� ������--------------------------*/
			do
			{
				std::cout << std::endl << " [������� ����� ������:]" << std::endl << std::endl;

				int indexSpace = -1;
				std::getline(std::cin, enterNewPassword); //���������� ������ � ����������
				indexSpace = enterNewPassword.find(' '); //����� �������� � ������

				//�������� �� ���� ������� ������
				if (enterNewPassword != "")
				{
					//�������� ������ �� ������� c ���������
					indexSpace = che�kRussData(enterNewPassword);
				}
				else { indexSpace = 1; }

				if (indexSpace == -1)
				{
					checkPassword = false; //����� ������ ������� ������
					//��������� ������ ������

					for (User& user : userList_)
					{
						if (getSelectUser()->getPassword() == enterPassword)
						{
							user.setPassword(enterNewPassword); //��������� ������ ������
							setSelectUser(user); //����� �������� �����������
							break;
						}
					}
					
					checkNewPassword = false; //����� ������ ����������

					system("cls");
					std::cout << std::endl << " [����� ������ ������� ����������]" << std::endl;
				}
				else
				{
					try
					{
						throw Valid�haractersExeption();
					}
					catch (Valid�haractersExeption e)
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
				throw Valid�haractersExeption();
			}
			catch (Valid�haractersExeption e)
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
	bool errorInickName = false; //����������� ������ ���������� ��� �������� ����������� ��������

	std::string enterLogin; //��������� �����
	std::string enterPassword; //��������� ������
	std::string enterName; //��������� �������

	do
	{
		std::cout << std::endl << "------------------------����������� ������ ������������-------------------------" << std::endl;
		std::cout << " [������� �����:]" << std::endl << std::endl;

		/*---------------------------���� ������---------------------------------*/
		int indexSpace = -1;

		std::getline(std::cin, enterLogin); //���������� ������ � ����������
		indexSpace = enterLogin.find(' '); //����� �������� � ������(��� ����� ����� ������� ��������� � ������)

		//�������� �� ���� ������� ������
		if (enterLogin != "")
		{
			//�������� ������ �� ������� c ���������
			indexSpace = che�kRussData(enterLogin);

			//�������� ������ �� ������������
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
			/*-----------------------���� ������--------------------------*/
			do
			{
				system("cls");
				checkLogin = false; //����� ������� ������
				std::cout << std::endl << "------------------------����������� ������ ������������-------------------------" << std::endl;
				std::cout << " ����� [" << enterLogin << "] ������� ������" << std::endl;

				std::cout << std::endl << " [������� ������:]" << std::endl << std::endl;

				int indexSpace = -1;
				std::getline(std::cin, enterPassword); //���������� ������ � ����������
				indexSpace = enterPassword.find(' '); //����� �������� � ������

				//�������� �� ���� ������� ������
				if (enterPassword != "")
				{
					//�������� ������ �� ������� c ���������
					indexSpace = che�kRussData(enterPassword);
				}
				else { indexSpace = 1; }

				if (indexSpace == -1)
				{
					/*-----------------------���� ��������--------------------------*/
					do
					{
						if (!errorInickName)
						{
							errorInickName = false;
							system("cls");
						}
						checkPassword = false; //������ ������� ������	

						std::cout << std::endl << "------------------------����������� ������ ������������-------------------------" << std::endl;
						std::cout << " ����� [" << enterLogin << "] ������� ������" << std::endl;

						std::cout << " ������ [ ******* ] ������� ������" << std::endl;

						std::cout << std::endl << " [������� �������:]" << std::endl << std::endl;

						int indexSpace = -1;
						std::getline(std::cin, enterName); //���������� �������� � ����������
						indexSpace = enterName.find(' '); //����� �������� � ��������(��� ����� ����� ������� ��������� � ��������)

						//�������� �� ���� ������� ������
						if (enterName != "")
						{
							indexSpace = -1;

							//�������� ������ �� ������������
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
									errorInickName = true; //���������� ��� ��������� �� ������ �� ��������� ��� ��������� ����
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
								throw Valid�haractersExeption();
							}
							catch (Valid�haractersExeption e)
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
						throw Valid�haractersExeption();
					}
					catch (Valid�haractersExeption e)
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
				throw Valid�haractersExeption();
			}
			catch (Valid�haractersExeption e)
			{
				system("cls");
				std::cout << std::endl << " " << e.what() << std::endl;
				continue;
			}
		}

		system("cls");
		std::cout << std::endl << "------------------------����������� ������ ������������-------------------------" << std::endl;

		std::cout << "  ����� ������������ ��� ������� ���������������" << std::endl;
		std::cout << "  ����� [" << enterLogin << "] ������� ������" << std::endl;
		std::cout << "  ������ [ ******* ] ������� ������" << std::endl;
		std::cout << "  ������� [" << enterName;
		std::cout << "] ������� ������" << std::endl;

		std::cout << "-------------------------------------------------------------------------------" << std::endl;
	}
	while (checkLogin);

	//�������� ������������ � ���������� ��� � ����� ������ �������������
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
			std::cout << std::endl << "--------------------------------------------------���( ";
			std::cout << getSelectUser()->getName();
			std::cout << " )--------------------------------------------------" << std::endl;
		}
		else
		{
			std::cout << std::endl << "--------------------------------------------------���--------------------------------------------------" << std::endl;
		}

		std::cout << " 1: [�����������] " << " 2: [����� ������] " << " 3: [������ �������������] " << " 0: [�����] " << std::endl;
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
			addUser(); //�������� ������������

			break;
		case 2:
			system("cls");
			//����� ������ �������� ������������
			changePassUser();

			break;
		case 3:
			system("cls");

			//����� ������ ���� �������������
			if (getUsers().size() > 0)
			{
				std::cout << std::endl << "---------------------------------������ ������������������ �������������:------------------------------" << std::endl;
				for (User& item : getUsers())
				{
					std::cout << " �����: " << item.getLogin() << " - [�������: " << item.getName() << "]" << std::endl;
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
			std::cout << std::endl << " [����������� ������� �������]" << std::endl;

			break;
		default:
			system("cls");
			std::cout << std::endl << " [����������� ������� �������]" << std::endl;
		}
	}
	while (workRegistUser_);
}

void Chat::showChat(std::shared_ptr<User> user)
{
	//����� ������ ���� �������������
	if (getMessages().size() > 0)
	{
		std::cout << std::endl << "---------------------------------��������� ��� ������������ "; 
		std::cout << selectUser_->getName();
		std::cout << ":------------------------------" << std::endl;
				
		for (Message& item : getMessages())
		{								
			if (user->getName() == item.getReciever()) //����� ����� ��������� ��������� ����������� ������������ � 
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
	int errorFlag = -1; //-1 - ��� ������, 1 - �������� ������

	std::string enterName; //��������� �������
	std::string enterMessage; //��������� ���������

	do
	{
		system("cls");
		std::cout << std::endl << "------------------------�������� ���������-------------------------" << std::endl;
		std::cout << " [������� �������( All/��� - ��� �������� ���� )]:" << std::endl << std::endl;

		/*---------------------------���� ��������---------------------------------*/
		std::getline(std::cin, enterName); //���������� ������ � ����������

		//�������� �� ���� ������� ������
		if (enterName != "") { errorFlag = -1; }
		else { errorFlag = 1; }

		if (errorFlag == -1)
		{
			/*-----------------------���� ���������--------------------------*/
			do
			{
				system("cls");
				checkName = false; //������������ � ����� ����� ���� ����� �����������������, ������� ������������� ����
				std::cout << std::endl << "------------------------�������� ���������-------------------------" << std::endl;
				std::cout << " ���������� [" << enterName << "]:" << std::endl;

				std::cout << std::endl << " [������� ���������:]" << std::endl << std::endl;

				errorFlag = -1; //���������� ���� ������
				std::getline(std::cin, enterMessage); //���������� ��������� � ����������

				//�������� �� ���� ������� ���������
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
					checkMessage = false; //������������ � �������� ����� ���������������	
				}
				else
				{
					try
					{
						throw Valid�haractersExeption();
					}
					catch (Valid�haractersExeption e)
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
				throw Valid�haractersExeption();
			}
			catch (Valid�haractersExeption e)
			{
				system("cls");
				std::cout << std::endl << " " << e.what() << std::endl;
				continue;
			}
		}

		system("cls");
		std::cout << std::endl << "------------------------�������� ���������-------------------------" << std::endl;
		std::cout << " [ ��������� ������� ���������� ]" << std::endl;
		std::cout << " [ ���������� ] " << enterName << std::endl;
		std::cout << " [ ��������� ] " << enterMessage << std::endl;

		std::cout << "-------------------------------------------------------------------------------" << std::endl;
	}
	while (checkName);

	//�������� ��������� � ���������� ��� � ����� ������ ���������
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
			std::cout << std::endl << "---------------------------------------���( ������������: ";
			std::cout << getSelectUser()->getName();
			std::cout << " )----------------------------------------" << std::endl;
		}
		else
		{
			std::cout << std::endl << "--------------------------------------------------���--------------------------------------------------" << std::endl;
		}

		std::cout << " 1: [���������]" << "		2: [���������] " << "		0: [�����] " << std::endl;
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

				//(����� - ��� �����������, ������� - ��� �������� � ������ ���������)
				//������� ��������� �� selectUser_ ������������ � ����� reciver
				sendMessage(); //��������� ���������
			}

			break;
		case 2:
			system("cls");

			std::cout << " ������ ��������� ��� (" << getSelectUser()->getName() << "):" << std::endl;

			//����� ������ ���� ��������� ��� ������������
			if (getMessages().size() > 0)
			{
				int countMessage = 0;
				for (User& user : getUsers())
				{
					for (Message& message : getMessages())
					{
						//��������� ����� ��������� ���������� ������������ ��� ����(������ ��� ��� All ��� ����� �������� �����������)
						if ((message.getReciever() == getSelectUser()->getName()) || (message.getReciever() == "���") || (message.getReciever() == "All"))
						{
							if (user.getName() == message.getSender())
							{
								std::cout << " [ ����������� ] " << message.getSender() << " [ ��������� ] " << message.getMessage() << std::endl;
								countMessage++;
							}
						}
					}

					std::cout << std::endl;
				}

				std::cout << " [���������� ���������] :" << countMessage << std::endl;
				std::cout << "-------------------------------------------------------------------------------------------------------" << std::endl;
			}
			else
			{
				std::cout << " [���������� ���������] : 0" << std::endl;
			}

			break;
		case 0:
			system("cls");
			workRegistUser_ = false;

			break;
		case -1:
			system("cls");
			std::cout << std::endl << " [����������� ������� �������]" << std::endl;

			break;
		default:
			system("cls");
			std::cout << std::endl << " [����������� ������� �������]" << std::endl;
		}
	}
	while (workRegistUser_);
}

int Chat::che�kRussData(std::string data)
{
	//�������� ������ �� ������� c ���������
	for (char& ch : data)
	{
		if ((ch >= '�' && ch <= '�') || (ch >= '�' && ch <= '�'))
		{
			return 1; //�������� ��� �������� ���� ������ ���� ���� ������ � ���������
		}
	}
	return -1; //�������� � ��������� ����
}
