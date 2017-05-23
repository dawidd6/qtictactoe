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
		emit signalExit();
	}
}

Server::Server()
{
	setMaxPendingConnections(2);
	connection_a = nullptr;
	connection_b = nullptr;
	connect(this, &Server::newConnection, this, &Server::handleNewConnection);
	connect(this, &Server::signalExit, this, &QCoreApplication::quit, Qt::QueuedConnection);
	startListening();
}

int main(int argc, char **argv)
{
	QCoreApplication a(argc, argv);
	Server server;
	return a.exec();
}
