#include <QApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QByteArray>

#include "server.h"

Server::Server()
{
	setMaxPendingConnections(2);
	connection_a = nullptr;
	connection_b = nullptr;
	listen(QHostAddress::Any, 60000);
	connect(this, &QTcpServer::newConnection, [&]
	{
		if(connection_a == nullptr)
		{
			connection_a = nextPendingConnection();
			connect(connection_a, &QTcpSocket::disconnected, [&]
			{
				connection_a = nullptr;
				qDebug().noquote().nospace() << "["<< date.currentDateTime().toString("yyyy-MM-dd | hh:mm:ss") << "] a disconnected";
				if(!isListening()) listen(QHostAddress::Any, 60000);
			});
			qDebug().noquote().nospace() << "["<< date.currentDateTime().toString("yyyy-MM-dd | hh:mm:ss") << "] a connected";
			connect(connection_a, &QTcpSocket::readyRead, [&]
			{
				msg = connection_a->readAll();
				qDebug("message received from a: %s", msg.data());
				msg.prepend("received from a: ");
				msg = "";
			});
		}
		else if(connection_b == nullptr)
		{
			connection_b = nextPendingConnection();
			connect(connection_b, &QTcpSocket::disconnected, [&]
			{
				connection_b = nullptr;
				qDebug().noquote().nospace() << "["<< date.currentDateTime().toString("yyyy-MM-dd | hh:mm:ss") << "] b disconnected";
				if(!isListening()) listen(QHostAddress::Any, 60000);
			});
			qDebug().noquote().nospace() << "["<< date.currentDateTime().toString("yyyy-MM-dd | hh:mm:ss") << "] b connected";
			connection_b->write(msg);
		}
		else if(connection_a != nullptr && connection_b != nullptr)
		{
			close();
			qDebug().noquote().nospace() << "["<< date.currentDateTime().toString("yyyy-MM-dd | hh:mm:ss") << "] pause accepting";
		}
	});
}

int main(int argc, char **argv)
{
	QApplication a(argc, argv);
	Server server;
	return a.exec();
}
