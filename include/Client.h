#ifndef QTICTACTOE_CLIENT_H
#define QTICTACTOE_CLIENT_H

#include <QTcpSocket>

class Client : public QTcpSocket
{
	Q_OBJECT
	private:
		QString response;
		QChar symbol;
		bool isFirst;
	signals:
	public slots:
		void handleConnection();
		void handleDisconnection();
		void handleRead();
	public:
		void logger(QString msg);
		void sendMessage();
		Client();
};

#endif
