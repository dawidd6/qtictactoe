#pragma once

class CServer : public QTcpServer
{
	private:
		QTcpSocket *connection_a;
		QTcpSocket *connection_b;
		QString response;
	public:
		CServer();
		void startListening();
		void handleRead();
		void handleNewConnection();
		void handleDisconnection();
		void randomTurnAndSymbol();
};
