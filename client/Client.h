#ifndef QTICTACTOE_CLIENT_H
#define QTICTACTOE_CLIENT_H

#include <QTcpSocket>

class Client : public QTcpSocket
{
	Q_OBJECT
	private:
		QString response;
		QChar symbol;
		int turn;
		int counter;
	public slots:
		void handleRead();
		void handleConnection();
		void handleDisconnection();
	public:
		void logger(QString msg);
		Client();
};

#endif
