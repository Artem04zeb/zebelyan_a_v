#pragma once
#include "net_common.h"

namespace olc
{
	namespace net
	{
		template <typename T>
		class client_interface
		{
		public:
			client_interface()
			{}

			virtual ~client_interface()
			{
				// Åñëè êëèåíò óíè÷òîæåí(íåêðàñèâûé âûêëþ÷åíèå), òî ïîïûòàòüñÿ îòêëþ÷èòüñÿ îò ñåðâåðà
				Disconnect();
			}

		public:
			// Ïîäæêëþ÷åíèå ê ñåðâåðó ñ ïîìîùüþ èìÿ õîñòà/ip-address and port
			bool Connect(const std::string& host, const uint16_t port)
			{
				try
				{
					// Ïðåîáðàçîâàíèå èìÿ_õîñòà/ip-àäðåñà â ôèçè÷åñêèé àäðåñ
					asio::ip::tcp::resolver resolver(m_context);
					asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

					// Ñîçäàíèå ñîåäèíåíèÿ
					m_connection = std::make_unique<connection<T>>(connection<T>::owner::client, m_context, asio::ip::tcp::socket(m_context), m_qMessagesIn);

					// Óêàçàíèå îáúåêòó ïîäêëþ÷åíèÿ, ÷òîáû îí ïîêäëþ÷èëñÿ ê ñåðâåðó
					m_connection->ConnectToServer(endpoints);

					// Çàïóñê êîíòåêñòà è ïîòîêà
					thrContext = std::thread([this]() { m_context.run(); });
				}
				catch (std::exception& e)
				{
					std::cerr << "Client Exception: " << e.what() << "\n";
					return false;
				}
				return true;
			}

			// Îòêëþ÷åíèå(êðàñèâîå) îò ñåðâåðà
			void Disconnect()
			{
				// Åñëè ñîåäèíåíèå ñóùåñòâóåò - ðàçîðâàòü åãî
				if (IsConnected()) m_connection->Disconnect();

				// Ïðè ëþáîì ðàñêëàäå ïðåðûâàåì êîíòåêñò è ïîòîê		
				m_context.stop();
				if (thrContext.joinable()) thrContext.join();

				// Óíè÷òîæàåì îáúåêò ñîåäèíåíèÿ
				m_connection.release();
			}

			/// Ïðîâåðêà, äåéñòâèòåëüíî ëè êëèåíò ïîäêëþ÷åí ê ñåðâåðó
			bool IsConnected()
			{
				if (m_connection)
					return m_connection->IsConnected();
				else
					return false;
			}

		public:
			/// Îòïðàâèòü ñîîáùåíèå íà ñåðâåð
			void Send(const message<T>& msg)
			{
				if (IsConnected())
					m_connection->Send(msg);
			}

			/// Èçâëåêàòü î÷åðåäü ñîîáùåíèé ñ ñåðâåðà
			tsqueue<owned_message<T>>& Incoming()
			{
				return m_qMessagesIn;
			}

		protected:
			/*
			Êîíòåêñò Asio îáðàáàòûâàåò ïåðåäà÷ó äàííûõ, 
			íî äëÿ âûïîëíåíèÿ ñâîåé ðàáîòû åìó íóæåí ñîáñòâåííûé ïîòîê 
			*/			
			asio::io_context m_context;
			std::thread thrContext;
			/// Ó êëèåíòà åñòü åäèíñòâåííûé ýêçåìïëÿð îáúåêòà "connection", êîòîðûé îáðàáàòûâàåò ïåðåäà÷ó äàííûõ
			std::unique_ptr<connection<T>> m_connection;

		private:
			/// Ýòî ïîòîêîáåçîïàñíàÿ î÷åðåäü âõîäÿùèõ ñîîáùåíèé ñ ñåðâåðà
			tsqueue<owned_message<T>> m_qMessagesIn;
		};
	}
}
