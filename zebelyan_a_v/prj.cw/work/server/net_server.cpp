#include <iostream>
#include <helpers/olc_net.h>

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
��������� ������ ������� ��� ��������� ��������� �� �������
*/
class CustomServer : public olc::net::server_interface<CustomMsgTypes>
{
public:
	CustomServer(uint16_t nPort) : olc::net::server_interface<CustomMsgTypes>(nPort){}

protected:

	/*
	��������: ����� ������ ������������ � �������, �� ������� ���������, �������
	��������� ���������� "ServerAccept". ����� ���������� ��� ��������� �������.
	����� ������ ���������� ��� ��������� � ������������ � ������������.
	*/
	virtual bool OnClientConnect(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client)
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::ServerAccept;
		client->Send(msg);
		return true;
	}

	// ����������, ����� �������, ��� ������ ����������
	virtual void OnClientDisconnect(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client)
	
	{
		std::cout << "�������� ������������ [" << client->GetID() << "]\n";
	}

	// ���������� ��� ����������� ���������
	virtual void OnMessage(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client, olc::net::message<CustomMsgTypes>& msg)
	{

		/*
		���������� ��� ����������� ��������� ��� ��������� ��������� �� ������� ����������� ��� ���������.
		����� ����������� ��������� ��������:
		1. ������ ���������� ��������������� ���������� � ��������� �������.
		2. ������������ ��������� ���������� �������, ������� ������������ ���� �������� ����.
		((�������� ������ ������ ��������)s
		*/
		switch (msg.header.id)
		{
			case CustomMsgTypes::ServerPing:
			{
				std::cout << "[" << client->GetID() << "]: ��������� ����\n";
				/*
				������ ��������� ��������� �������.
				�� ��� �������� ����������� ���������� ��� �������,
				��������� � ���� �������� ��������� ����� ��������
				*/
				client->Send(msg);
			}
			break;

			case CustomMsgTypes::SayHello:
			{
				 std::cout << "[" << client->GetID() << "]: ������������ ���� \n";

				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::SayHello;
				msg << client->GetID();
				MessageAllClients(msg, client);

			}
			break;

			case CustomMsgTypes::GoodBye:
			{
				std::cout << "[" << client->GetID() << "]: ��������� �� �����! \n";

				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::GoodBye;
				msg << client->GetID();
				MessageAllClients(msg, client);
			}
			break;
			
			case CustomMsgTypes::SendPeace:
			{
				std::cout << "[" << client->GetID() << "]: ���� ���� PEACE \n";
				
				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::SendPeace;
				msg << client->GetID();
				MessageAllClients(msg, client);
			}
			break;

			case CustomMsgTypes::GoOffline:
			{
				std::cout << "[" << client->GetID() << "]: ����� ������� � �������! \n";
				
				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::GoOffline;
				msg << client->GetID();
				MessageAllClients(msg, client);
			}
			break;

			case CustomMsgTypes::AskMood:
			{
				std::cout << "[" << client->GetID() << "]: ������������ ����������� ����\n";
				
				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::AskMood;
				msg << client->GetID();
				MessageAllClients(msg, client);
			}
			break;

			case CustomMsgTypes::SendBadMood:
			{
				std::cout << "[" << client->GetID() << "]: �������� � ������ ����������\n";
				
				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::SendBadMood;
				msg << client->GetID();
				MessageAllClients(msg, client);
			}
			break;

			case CustomMsgTypes::SendOK:
			{
				std::cout << "[" << client->GetID() << "]: �������� � ������� ����������\n";
				
				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::SendOK;
				msg << client->GetID();
				MessageAllClients(msg, client);
			}
			break;

			case CustomMsgTypes::FeelHungry:
			{
				std::cout << "[" << client->GetID() << "]: �������� � ������\n";
				
				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::FeelHungry;
				msg << client->GetID();
				MessageAllClients(msg, client);
			}
			break;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");

	/// TODO ��������� �������� ����� �� � ������ ���������, � ��������� ��� �� ����������������� ����� � ���������� ����� ����������
	CustomServer server(6000);


	server.Start();

	while (1)
	{
		server.Update(-1, true);
	}

	return 0;
}