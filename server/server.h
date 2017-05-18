#ifndef QTICTACTOE_SERVER_H
#define QTICTACTOE_SERVER_H

#include <QTcpServer>

class Server : public QTcpServer
{
	Q_OBJECT
	private:
		QTcpSocket *connection_a;
		QTcpSocket *connection_b;
		QString response_a;
		QString response_b;
	signals:
		void signalTurn();

	public slots:
		void handleNewConnection();
		void handleDisconnection();
		void handleRead();
	public:
		Server();
		void logger(QString msg);
		void startListening();
		void sendGreeting(char c);
};

#endif
