#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QByteArray>

#include "server.h"

void Server::logger(QString msg)
{
	QDateTime date;
	qDebug().noquote().nospace() << "["<< date.currentDateTime().toString("yyyy-MM-dd | hh:mm:ss") << "] " << msg;
}

void Server::handleNewConnection()
{
	if(connection_a == nullptr)
	{
		connection_a = nextPendingConnection();
		connect(connection_a, SIGNAL(disconnected()), this, SLOT(handleDisconnection()));
		logger("Connected a");
	}
	else if(connection_b == nullptr)
	{
		connection_b = nextPendingConnection();
		connect(connection_b, SIGNAL(disconnected()), this, SLOT(handleDisconnection()));
		logger("Connected b");
	}
	else logger("two clients connected, ignoring");

	if(connection_a != nullptr && connection_b != nullptr)
	{
		connection_a->write("1x");
		connection_b->write("0o");
		connect(connection_a, SIGNAL(readyRead()), this, SLOT(handleRead()));
		connect(connection_b, SIGNAL(readyRead()), this, SLOT(handleRead()));
	}
}

void Server::handleRead()
{
	if(sender() == connection_a)
	{
		QString response = connection_a->readAll().data();
		connection_b->write(response.toUtf8());
		logger("Message from a to b redirected");
	}
	else if(sender() == connection_b)
	{
		QString response = connection_b->readAll().data();
		connection_a->write(response.toUtf8());
		logger("Message from b to a redirected");
	}
}

void Server::handleDisconnection()
{
	if(sender() == connection_a)
	{
		logger("Disconnected a");
		connection_a = nullptr;
	}
	else if(sender() == connection_b)
	{
		logger("Disconnected b");
		connection_b = nullptr;
	}
}

void Server::startListening()
{
	if(listen(QHostAddress::Any, 60000))
		logger("Listening...");
	else
	{
		logger("Could not start server");
		logger("Exiting...");
		QCoreApplication::exit(1);
	}
}

Server::Server()
{
	setMaxPendingConnections(2);
	connection_a = nullptr;
	connection_b = nullptr;
	startListening();
	connect(this, SIGNAL(newConnection()), this, SLOT(handleNewConnection()));
}

int main(int argc, char **argv)
{
	QCoreApplication a(argc, argv);
	Server server;
	return a.exec();
}
