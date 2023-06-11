#include <iostream>
#include <helpers/olc_net.h>
#include <fstream>
#include <string>


/*
����� ��������� ��������� �������.
������ ��������� ��������� ������� ���������� ���������, ������������ � ���������� � �������.
*/
enum class CustomMsgTypes : uint32_t
{
	ServerAccept, ///< ������ ������� ����������� �������
	ServerDeny, ///< ������ �������� ���������� ����������
	ServerMessage,

	ServerPing, ///< ����������� ���� �������
	SayHello, ///< ���������� ��������������� ������� �� ������
	GoodBye, ///<  ���������� ��������������� ������� �� ������
	SendPeace, ///< ���������� ��������������� ������� �� ������
	GoOffline, ///< ���������� ��������������� ������� �� ������
	AskMood, ///< ���������� ��������������� ������� �� ������
	SendBadMood, ///< ���������� ��������������� ������� �� ������ 
	SendOK, ///< ���������� ��������������� ������� �� ������
	FeelHungry ///< ���������� ��������������� ������� �� ������

};


/*
\date 12 ��� 2023
������������� ��������� ��� ������ ������� � ��������.
*/
class CustomClient : public olc::net::client_interface<CustomMsgTypes>
{
	public:

		/*
		�� ������ ������������ ��������� � �������� �������
		*/
		void PingServer()
		{
			/// �������� ��������� ������������ �������
			olc::net::message<CustomMsgTypes> msg;
			
			/// ���������� ���������
			msg.header.id = CustomMsgTypes::ServerPing;

			/// �������� ��������� �����
			std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

			/// ���������� ������ � ���������
			msg << timeNow;

			/// �������� ���������
			Send(msg);
		}

		/*
		�� ������ ������������ ������ ��������� � �������� SayHello
		*/
		void SayHello()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::SayHello;
			Send(msg);
		}

		/*
		�� ������ ������������ ������ ��������� � �������� GoodBye
		*/
		void GoodBye()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::GoodBye;
			Send(msg);
		}

		/*
		�� ������ ������������ ������ ��������� � �������� SendPeace
		*/
		void SendPeace()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::SendPeace;
			Send(msg);
		}

		/*
		�� ������ ������������ ������ ��������� � �������� GoOffline
		*/
		void GoOffline()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::GoOffline;
			Send(msg);
		}

		/*
		�� ������ ������������ ������ ��������� � �������� AskMood
		*/
		void AskMood()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::AskMood;
			Send(msg);
		}

		/*
		�� ������ ������������ ������ ��������� � �������� SendBadMood
		*/
		void SendBadMood()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::SendBadMood;
			Send(msg);
		}

		/*
		�� ������ ������������ ������ ��������� � �������� SendOK
		*/
		void SendOK()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::SendOK;
			Send(msg);
		}

		/*
		�� ������ ������������ ������ ��������� � �������� FeelHungry
		*/
		void FeelHungry()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::FeelHungry;
			Send(msg);
		}

};

int main()
{
	setlocale(LC_ALL, "Russian");

	/// ����� �����������
	std::cout << "--------------------\n����� ���������� � ��� Flag Connection!\n\n������� ������������ � �������...\n\n";
	
	/// �������� ������� ������
	CustomClient c;

	/// ����������� � �������
	c.Connect("127.0.0.1", 6000);

	/// ����������� � ��������� ��������, � ������� ����� ��������� ��������� ������
	bool key[10]{ false };
	bool old_key[10]{ false };

	/// bQuit - ���� ��� ������ �� ����� ������������� �������
	bool bQuit = false;
	while (!bQuit)
	{
		if (GetForegroundWindow() == GetConsoleWindow())
		{
			key[0] = GetAsyncKeyState('1') & 0x8000;
			key[1] = GetAsyncKeyState('2') & 0x8000;
			key[2] = GetAsyncKeyState('3') & 0x8000;
			key[3] = GetAsyncKeyState('4') & 0x8000;
			key[4] = GetAsyncKeyState('5') & 0x8000;
			key[5] = GetAsyncKeyState('6') & 0x8000;
			key[6] = GetAsyncKeyState('7') & 0x8000;
			key[7] = GetAsyncKeyState('8') & 0x8000;
			key[8] = GetAsyncKeyState('9') & 0x8000;
			key[9] = GetAsyncKeyState('0') & 0x8000;
		}

		{
			/// �������� ������ �� ���������� �� 0 �� 9 ��� ������ ��������������� �������
			if (key[0] && !old_key[0]) c.PingServer();
			if (key[1] && !old_key[1]) c.SayHello();
			if (key[2] && !old_key[2]) c.GoodBye();
			if (key[3] && !old_key[3]) c.SendPeace();
			if (key[4] && !old_key[4]) c.GoOffline();
			if (key[5] && !old_key[5]) c.AskMood();
			if (key[6] && !old_key[6]) c.SendBadMood();
			if (key[7] && !old_key[7]) c.SendOK();
			if (key[8] && !old_key[8]) c.FeelHungry();
			if (key[9] && !old_key[9]) bQuit = true;
		}

		for (int i = 0; i < 9; i++) old_key[i] = key[i];

		/// �������� �����������
		if (c.IsConnected())
		{
			if (!c.Incoming().empty())
			{
				auto msg = c.Incoming().pop_front().msg;

				/*
				����� ����, ��� ��������� �������, ��� ��������� �����������.
				� ����������� �� �������� ��������� ������� ��������� ��������������� ���������
				*/
				switch (msg.header.id){
					case CustomMsgTypes::ServerAccept:
					{
						std::cout << "������ ������� �����������. �����������!\n"; 
						std::cout << "��������� �������, ����������� ������� �������� ���������. \n��� �������� ������ ����������� ����� �� 0 �� 9.\n���� ��������� ����� ���� ���������� �������.\n\n������� ��� �������������:\n";
						std::cout << "\t [ 1 ] - ��������� ������ ���� ���������� ����\n";
						std::cout << "\t [ 2 ] - ����������� �� ����� :f\n";
						std::cout << "\t [ 3 ] - ��������� PEACE!\n";
						std::cout << "\t [ 4 ] - �������� ������� ��������� � offline\n";
						std::cout << "\t [ 5 ] - ���������������� ����������� ��������\n";
						std::cout << "\t [ 6 ] - ������������������ ������ ����������\n";
						std::cout << "\t [ 7 ] - ������������������ ������� ����������\n";
						std::cout << "\t [ 8 ] - �������� ���� � ����� ������\n";
						std::cout << "\t [ 9 ] - ��������� ping\n";
						std::cout << "\t [ 0 ] - ����������� �� ������� � �������� ���\n";
						std::cout << "\n�������, �� ����� ������� ��-���������!\n";
					}
					break;

					case CustomMsgTypes::ServerPing:
					{
						/// ��������� �������� � ��������� ������� �������� ��� ��������.
						/// ����� ��������� ��������� ����� ���������� �������
						/// �������������� ������� ��������� ������� � ���� �������� ping
						std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
						std::chrono::system_clock::time_point timeThen;
						msg >> timeThen;
						std::cout << "ping: " << std::chrono::duration<double>(timeNow - timeThen).count() << "\n";
					}
					break;

					case CustomMsgTypes::SayHello:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: ���� �������� ������� ������!\n";
					}
					break;

					case CustomMsgTypes::GoodBye:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: �������� ����������� � �����, ��������� ;(\n";
					}
					break;
					 
					case CustomMsgTypes::SendPeace:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: ���� ����� PEACE !\n";
					}
					break;

					case CustomMsgTypes::GoOffline:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: ��, ���, ������� ���������� � �����!\n";
					}
					break;

					case CustomMsgTypes::AskMood:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: �����, ��� ���������, ��� �������?\n";
					}
					break;

					case CustomMsgTypes::SendOK:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: � ���� ��� ����������, ����� ����!\n";
					}
					break;

					case CustomMsgTypes::SendBadMood:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: ��������� ������, ����� �� ���� � �����\n";
					}
					break;

					case CustomMsgTypes::FeelHungry:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: ��������, ����� ������ �������!\n";
					}
					break;

				}
			}
		}
		/// ����������� �� �������
		else
		{
			std::cout << "������ ����, ���� �� �� ���� �����������... \n";
			bQuit = true;
		}

	}

	return 0;
}