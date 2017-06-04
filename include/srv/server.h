#pragma once

class Server : public QTcpServer
{
	private:
		QTcpSocket *connection_a;
		QTcpSocket *connection_b;
		QString response;
	public:
		Server();
		void logger(QString msg);
		void startListening();
		void handleRead();
		void handleNewConnection();
		void handleDisconnection();
		void randomTurnAndSymbol();
};
