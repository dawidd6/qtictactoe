#include <QCoreApplication>
#include <QTcpSocket>
#include <QByteArray>
#include <QDateTime>
#include <iostream>

#include "Client.h"

void Client::logger(QString msg)
{
	QDateTime date;
	qDebug().noquote().nospace() << "["<< date.currentDateTime().toString("yyyy-MM-dd | hh:mm:ss") << "] " << msg;
}

void Client::handleConnection()
{
	logger("Connected");
	connect(this, SIGNAL(readyRead()), this, SLOT(handleRead()));
	connect(this, SIGNAL(disconnected()), this, SLOT(handleDisconnection()));
}

void Client::handleRead()
{
	if(counter == 0)
	{
		response = readAll().data();
		turn = response[0].digitValue();
		symbol = response[1];
		logger("Greeting: " + response);
	}
	
	while(1)
	{
		counter++;
		if(turn)
		{
			std::cout << "Input: ";
			QString txt = QTextStream(stdin).readLine();
			write(txt.toUtf8());
			waitForBytesWritten(3000);
			logger("Sent");
			turn = false;
		}
		else
		{
			logger("Waiting for ReadyRead");
			waitForReadyRead(-1);
			logger("Reading...");
			response = readAll().data();
			logger("Received: " + response);
			turn = true;
		}
	}
}

void Client::handleDisconnection()
{
	logger("Disconnected, exiting...");
	QCoreApplication::exit(0);
}

Client::Client() : counter(0)
{
	connectToHost("127.0.0.1", 60000);
	connect(this, SIGNAL(connected()), this, SLOT(handleConnection()));
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Client client;
	return a.exec();
}
