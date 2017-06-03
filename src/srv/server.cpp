#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QByteArray>

#include "server.h"

void Server::logger(QString msg)
{
	qDebug
	(
		"[%s] %s",
		qPrintable(QDateTime().currentDateTime().toString("yyyy-MM-dd | hh:mm:ss")),
		qPrintable(msg)
	);
}

void Server::handleNewConnection()
{
	if(connection_a == nullptr)
	{
		connection_a = nextPendingConnection();
		connect(connection_a, &QTcpSocket::disconnected, this, &Server::handleDisconnection);
		logger("Connected a");
	}
	else if(connection_b == nullptr)
	{
		connection_b = nextPendingConnection();
		connect(connection_b, &QTcpSocket::disconnected, this, &Server::handleDisconnection);
		logger("Connected b");
	}
	else logger("two clients connected, ignoring");

	if(connection_a != nullptr && connection_b != nullptr)
	{
		connection_a->write("1x");
		connection_b->write("0o");
		connect(connection_a, &QTcpSocket::readyRead, this, &Server::handleRead);
		connect(connection_b, &QTcpSocket::readyRead, this, &Server::handleRead);
	}
}

void Server::handleRead()
{
	if(sender() == connection_a)
	{
		response = connection_a->readAll().data();
		if(connection_b != nullptr)
			connection_b->write(response.toUtf8());
		logger("Message from a to b redirected");
	}
	if(sender() == connection_b)
	{
		response = connection_b->readAll().data();
		if(connection_a != nullptr)
			connection_a->write(response.toUtf8());
		logger("Message from b to a redirected");
	}
}

void Server::handleDisconnection()
{
	if(sender() == connection_a)
	{
		logger("Disconnected a");
		if(connection_b != nullptr)
			connection_b->write("dis");
		connection_a = nullptr;
	}
	if(sender() == connection_b)
	{
		logger("Disconnected b");
		if(connection_a != nullptr)
			connection_a->write("dis");
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
		exit(1);
	}
}

Server::Server()
{
	setMaxPendingConnections(2);
	connection_a = nullptr;
	connection_b = nullptr;
	connect(this, &Server::newConnection, this, &Server::handleNewConnection);
	startListening();
}

int main(int argc, char **argv)
{
	QCoreApplication a(argc, argv);
	Server server;
	return a.exec();
}
