#include <QtNetwork>

#include "Game.h"

#include "Server.h"

void CServer::handleNewConnection()
{
	if(connection_a == nullptr)
	{
		connection_a = nextPendingConnection();
		connect(connection_a, &QTcpSocket::disconnected, this, &CServer::handleDisconnection);
		CGame::logger("Connected a");
	}
	else if(connection_b == nullptr)
	{
		connection_b = nextPendingConnection();
		connect(connection_b, &QTcpSocket::disconnected, this, &CServer::handleDisconnection);
		CGame::logger("Connected b");
	}
	else CGame::logger("two clients connected, ignoring");

	if(connection_a != nullptr && connection_b != nullptr)
	{
		randomTurnAndSymbol();
		connect(connection_a, &QTcpSocket::readyRead, this, &CServer::handleRead);
		connect(connection_b, &QTcpSocket::readyRead, this, &CServer::handleRead);
	}
}

void CServer::randomTurnAndSymbol()
{
	QByteArray request_a = "r-";
	QByteArray request_b = "r-";
	if(qrand() % 2)
	{
		request_a.append("1");
		request_b.append("0");
	}
	else
	{
		request_a.append("0");
		request_b.append("1");
	}
	if(qrand() % 2)
	{
		request_a.append("x");
		request_b.append("o");
	}
	else
	{
		request_a.append("o");
		request_b.append("x");
	}
	connection_a->write(request_a);
	connection_b->write(request_b);
}

void CServer::handleRead()
{
	if(sender() == connection_a)
	{
		response = connection_a->readAll().data();
		if(connection_b != nullptr)
		{
			if(response == "ry")
				randomTurnAndSymbol();
			else
				connection_b->write(response.toUtf8());
			CGame::logger("Message from a to b redirected");
		}
		else connection_a->write("dis");
	}
	if(sender() == connection_b)
	{
		response = connection_b->readAll().data();
		if(connection_a != nullptr)
		{
			if(response == "ry")
				randomTurnAndSymbol();
			else
				connection_a->write(response.toUtf8());
			CGame::logger("Message from b to a redirected");
		}
		else connection_b->write("dis");
	}
}

void CServer::handleDisconnection()
{
	if(sender() == connection_a)
	{
		CGame::logger("Disconnected a");
		if(connection_b != nullptr)
			connection_b->write("dis");
		connection_a = nullptr;
	}
	if(sender() == connection_b)
	{
		CGame::logger("Disconnected b");
		if(connection_a != nullptr)
			connection_a->write("dis");
		connection_b = nullptr;
	}
}

void CServer::startListening()
{
	if(listen(QHostAddress::Any, 60000))
		CGame::logger("Listening...");
	else
	{
		CGame::logger("Could not start server");
		CGame::logger("Exiting...");
		exit(1);
	}
}

CServer::CServer()
{
	setMaxPendingConnections(2);
	qsrand(QTime::currentTime().msec());
	connection_a = nullptr;
	connection_b = nullptr;
	connect(this, &CServer::newConnection, this, &CServer::handleNewConnection);
	startListening();
}
