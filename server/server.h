#ifndef QTICTACTOE_SERVER_H
#define QTICTACTOE_SERVER_H

class Server : public QTcpServer
{
	private:
		QTcpSocket *connection_a;
		QTcpSocket *connection_b;
		QDateTime date;
		QByteArray msg;
	public:
		Server();
};

#endif
