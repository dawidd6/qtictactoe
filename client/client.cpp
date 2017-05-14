#include <QApplication>
#include <QTcpSocket>

#include "client.h"

Client::Client()
{
	connectToHost("127.0.0.1", 60000);
	connect(this, &QTcpSocket::connected, []
	{
		qDebug("connected");
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
	a.exec();
}
