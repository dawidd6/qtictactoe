#ifndef QTICTACTOE_CLIENT_H
#define QTICTACTOE_CLIENT_H

class Client : public QTcpSocket
{
	private:
		QByteArray msg;
	public:
		Client();
};

#endif
