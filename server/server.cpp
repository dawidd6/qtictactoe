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

void Server::sendGreeting(char c)
{
	if(c == 'a')
	{
		connection_a->write("1x");
		logger("greeting sent to a");
	}
	else if(c == 'b')
	{
		connection_b->write("0o");
		logger("greeting sent to b");
	}
}

void Server::handleRead()
{
	if(sender() == connection_a)
	{
		response_a = connection_a->readAll().data();
		logger("response from a: " + response_a);
		connection_b->write(QByteArray("from a: ").append(response_a));
		connection_b->waitForBytesWritten(3000);
	}
	else if(sender() == connection_b)
	{
		response_b = connection_b->readAll().data();
		logger("response from b: " + response_b);
		connection_a->write(QByteArray("from b: ").append(response_b));
		connection_a->waitForBytesWritten(3000);
	}
}

void Server::handleNewConnection()
{
	if(connection_a == nullptr)
	{
		connection_a = nextPendingConnection();
		connect(connection_a, SIGNAL(disconnected()), this, SLOT(handleDisconnection()));
		logger("connected a");
		sendGreeting('a');
	}
	else if(connection_b == nullptr)
	{
		connection_b = nextPendingConnection();
		connect(connection_b, SIGNAL(disconnected()), this, SLOT(handleDisconnection()));
		logger("connected b");
		sendGreeting('b');
	}
	else logger("two clients connected, ignoring");

	if(connection_a != nullptr && connection_b != nullptr)
	{
		connect(connection_a, SIGNAL(readyRead()), this, SLOT(handleRead()));
		connect(connection_b, SIGNAL(readyRead()), this, SLOT(handleRead()));
	}
}

void Server::handleDisconnection()
{
	if(sender() == connection_a)
	{
		logger("disconnected a");
		connection_a = nullptr;
	}
	else if(sender() == connection_b)
	{
		logger("disconnected b");
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
