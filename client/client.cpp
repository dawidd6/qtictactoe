#include <QApplication>
#include <QTcpSocket>
#include <QByteArray>

#include "client.h"

Client::Client()
{
	connectToHost("127.0.0.1", 60000);
	connect(this, &QTcpSocket::connected, [&]
	{
		qDebug("connected");
		msg.append("message from client");
		write(msg);

		connect(this, &QTcpSocket::readyRead, [&]
		{
			QByteArray msg = readAll();
			qDebug("received: %s", msg.data());
		});

	});
	connect(this, &QTcpSocket::disconnected, []
	{
		qDebug("disconnected");
	});

}

int main(int argc, char **argv)
{
	QApplication a(argc, argv);
	Client client;
	return a.exec();
}
