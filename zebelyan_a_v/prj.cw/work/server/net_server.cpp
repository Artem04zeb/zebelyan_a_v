#include <iostream>
#include <helpers/olc_net.h>
//#include <Windows.h>

/*
Набор возможных состояний объекта.
Каждое состояние описывает маркеры заголовков сообщения, отправленные и полученные с сервера.
*/
enum class CustomMsgTypes : uint32_t
{
	ServerAccept, ///< Сервер одобрил подключение клиента
	ServerDeny, ///< Сервер отклонил клиентское соединение
	ServerMessage,

	ServerPing, ///< Запрашивает пинг сервера
	SayHello, ///< Отправляет соответствующую команду на сервер
	GoodBye, ///<  Отправляет соответствующую команду на сервер
	SendPeace, ///< Отправляет соответствующую команду на сервер
	GoOffline, ///< Отправляет соответствующую команду на сервер
	AskMood, ///< Отправляет соответствующую команду на сервер
	SendBadMood, ///< Отправляет соответствующую команду на сервер 
	SendOK, ///< Отправляет соответствующую команду на сервер
	FeelHungry ///< Отправляет соответствующую команду на сервер

};


/*
Описывает работу сервера при получении сообщений от клиента
*/
class CustomServer : public olc::net::server_interface<CustomMsgTypes>
{
public:
	CustomServer(uint16_t nPort) : olc::net::server_interface<CustomMsgTypes>(nPort){}

protected:

	/*
	Описание: когда клиент подключается к серверу, он создает сообщение, помечая
	заголовок заголовком "ServerAccept". Затем отправляет это сообщение клиенту.
	Далее клиент обработает это сообщение в соответствии с инструкциями.
	*/
	virtual bool OnClientConnect(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client)
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::ServerAccept;
		client->Send(msg);
		return true;
	}

	// Вызывается, когда кажется, что клиент отключился
	virtual void OnClientDisconnect(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client)
	
	{
		std::cout << "Отключаю пользователя [" << client->GetID() << "]\n";
	}

	// Вызывается при поступлении сообщения
	virtual void OnMessage(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client, olc::net::message<CustomMsgTypes>& msg)
	{

		/*
		Вызывается при поступлении сообщения При получении сообщения от клиента проверяется его заголовок.
		Далее выполняются следующие действия:
		1. Сервер отображает соответствующую информацию о действиях клиента.
		2. Генерируется сообщение требуемого формата, которое отправляется всем клиентам сети.
		((смотрите каждый случай отдельно)s
		*/
		switch (msg.header.id)
		{
			case CustomMsgTypes::ServerPing:
			{
				std::cout << "[" << client->GetID() << "]: проверяет пинг\n";
				/*
				Просто отправьте сообщение обратно.
				Он уже содержит необходимую информацию для клиента,
				поскольку в него встроена временная метка отправки
				*/
				client->Send(msg);
			}
			break;

			case CustomMsgTypes::SayHello:
			{
				 std::cout << "[" << client->GetID() << "]: приветствует всех \n";

				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::SayHello;
				msg << client->GetID();
				MessageAllClients(msg, client);

			}
			break;

			case CustomMsgTypes::GoodBye:
			{
				std::cout << "[" << client->GetID() << "]: прощается со всеми! \n";

				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::GoodBye;
				msg << client->GetID();
				MessageAllClients(msg, client);
			}
			break;
			
			case CustomMsgTypes::SendPeace:
			{
				std::cout << "[" << client->GetID() << "]: шлет всем PEACE \n";
				
				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::SendPeace;
				msg << client->GetID();
				MessageAllClients(msg, client);
			}
			break;

			case CustomMsgTypes::GoOffline:
			{
				std::cout << "[" << client->GetID() << "]: хочет перейти в оффлайн! \n";
				
				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::GoOffline;
				msg << client->GetID();
				MessageAllClients(msg, client);
			}
			break;

			case CustomMsgTypes::AskMood:
			{
				std::cout << "[" << client->GetID() << "]: интересуется настроением чата\n";
				
				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::AskMood;
				msg << client->GetID();
				MessageAllClients(msg, client);
			}
			break;

			case CustomMsgTypes::SendBadMood:
			{
				std::cout << "[" << client->GetID() << "]: сообщает о плохом настроении\n";
				
				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::SendBadMood;
				msg << client->GetID();
				MessageAllClients(msg, client);
			}
			break;

			case CustomMsgTypes::SendOK:
			{
				std::cout << "[" << client->GetID() << "]: сообщает о хорошем настроении\n";
				
				olc::net::message<CustomMsgTypes> msg;
				msg.header.id = CustomMsgTypes::SendOK;
				msg << client->GetID();
				MessageAllClients(msg, client);
			}
			break;

			case CustomMsgTypes::FeelHungry:
			{
				std::cout << "[" << client->GetID() << "]: сообщает о голоде\n";
				
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
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	_setmode(_fileno(stdout), _O_U16TEXT);
    	_setmode(_fileno(stdin),  _O_U16TEXT);
    	_setmode(_fileno(stderr), _O_U16TEXT);
	/// TODO Загружает параметр порта не с прямым значением, а считывает его из конфигурационного файла и подключает через переменную
	CustomServer server(6000);


	server.Start();

	while (1)
	{
		server.Update(-1, true);
	}

	return 0;
}
