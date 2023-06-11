#include <iostream>
#include <helpers/olc_net.h>
#include <fstream>
#include <string>


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
\date 12 Май 2023
Предоставляет интерфейс для работы клиента с сервером.
*/
class CustomClient : public olc::net::client_interface<CustomMsgTypes>
{
	public:

		/*
		На сервер отправляется сообщение с отметкой времени
		*/
		void PingServer()
		{
			/// Создание сообщения специального формата
			olc::net::message<CustomMsgTypes> msg;
			
			/// Маркировка заголовка
			msg.header.id = CustomMsgTypes::ServerPing;

			/// Создание временной точки
			std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

			/// Сохранение данных в сообщении
			msg << timeNow;

			/// Отправка сообщения
			Send(msg);
		}

		/*
		На сервер отправляется пустое сообщение с маркером SayHello
		*/
		void SayHello()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::SayHello;
			Send(msg);
		}

		/*
		На сервер отправляется пустое сообщение с маркером GoodBye
		*/
		void GoodBye()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::GoodBye;
			Send(msg);
		}

		/*
		На сервер отправляется пустое сообщение с маркером SendPeace
		*/
		void SendPeace()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::SendPeace;
			Send(msg);
		}

		/*
		На сервер отправляется пустое сообщение с маркером GoOffline
		*/
		void GoOffline()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::GoOffline;
			Send(msg);
		}

		/*
		На сервер отправляется пустое сообщение с маркером AskMood
		*/
		void AskMood()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::AskMood;
			Send(msg);
		}

		/*
		На сервер отправляется пустое сообщение с маркером SendBadMood
		*/
		void SendBadMood()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::SendBadMood;
			Send(msg);
		}

		/*
		На сервер отправляется пустое сообщение с маркером SendOK
		*/
		void SendOK()
		{
			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::SendOK;
			Send(msg);
		}

		/*
		На сервер отправляется пустое сообщение с маркером FeelHungry
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

	/// Вывод приветствия
	std::cout << "--------------------\nДобро пожаловать в чат Flag Connection!\n\nПытаюсь подключиться к серверу...\n\n";
	
	/// Создание объекта класса
	CustomClient c;

	/// Подключение к серверу
	c.Connect("127.0.0.1", 6000);

	/// Подключение к серверным массивам, в которых будут храниться состояния кнопок
	bool key[10]{ false };
	bool old_key[10]{ false };

	/// bQuit - Флаг для выхода из цикла прослушивания сервера
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
			/// Проверка клавиш на клавиатуре от 0 до 9 для вызова соответствующих функций
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

		/// Проверка подключения
		if (c.IsConnected())
		{
			if (!c.Incoming().empty())
			{
				auto msg = c.Incoming().pop_front().msg;

				/*
				После того, как сообщение принято, его заголовок повторяется.
				В зависимости от значения заголовка клиенту выводятся соответствующие сообщения
				*/
				switch (msg.header.id){
					case CustomMsgTypes::ServerAccept:
					{
						std::cout << "Сервер одобрил подключение. Подключаюсь!\n"; 
						std::cout << "Общайтесь флагами, отправляйте друзьям короткие сообщения. \nДля отправки команд используйте цифры от 0 до 9.\nВаши сообщения видны всем участникам сервера.\n\nКоманды для использования:\n";
						std::cout << "\t [ 1 ] - Отправить привет всем участникам чата\n";
						std::cout << "\t [ 2 ] - Попрощаться со всеми :f\n";
						std::cout << "\t [ 3 ] - Отправить PEACE!\n";
						std::cout << "\t [ 4 ] - Выразить желание увидеться в offline\n";
						std::cout << "\t [ 5 ] - Поинтересоваться настроением конфичей\n";
						std::cout << "\t [ 6 ] - Продемонстрировать плохое настроение\n";
						std::cout << "\t [ 7 ] - Продемонстрировать хорошее настроении\n";
						std::cout << "\t [ 8 ] - Сообщить всем о своем голоде\n";
						std::cout << "\t [ 9 ] - Проверить ping\n";
						std::cout << "\t [ 0 ] - Отключиться от сервера и покинуть чат\n";
						std::cout << "\nПомните, не стоит уходить по-английски!\n";
					}
					break;

					case CustomMsgTypes::ServerPing:
					{
						/// Сообщение получено с указанием момента создания его отправки.
						/// Затем создается временная точка настоящего времени
						/// Результирующая разница выводится клиенту в виде значения ping
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
						std::cout << "---[" << clientID << "]: Всем конфичам передаю привет!\n";
					}
					break;

					case CustomMsgTypes::GoodBye:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: Вынужден попрощаться с чатом, отчаливаю ;(\n";
					}
					break;
					 
					case CustomMsgTypes::SendPeace:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: Всем кисам PEACE !\n";
					}
					break;

					case CustomMsgTypes::GoOffline:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: Эй, все, давайте встретимся в жизни!\n";
					}
					break;

					case CustomMsgTypes::AskMood:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: Народ, как поживаете, как настрой?\n";
					}
					break;

					case CustomMsgTypes::SendOK:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: У меня все потрясающе, жизнь кайф!\n";
					}
					break;

					case CustomMsgTypes::SendBadMood:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: Признаюсь честно, могло бы быть и лучше\n";
					}
					break;

					case CustomMsgTypes::FeelHungry:
					{
						uint32_t clientID;
						msg >> clientID;
						std::cout << "---[" << clientID << "]: Голодняк, готов съесть мамонта!\n";
					}
					break;

				}
			}
		}
		/// Отключитесь от сервера
		else
		{
			std::cout << "Сервер упал, даже не от чего отключаться... \n";
			bQuit = true;
		}

	}

	return 0;
}