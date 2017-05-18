#include <QCoreApplication>
#include <QTcpSocket>
#include <QByteArray>
#include <QDateTime>

#include "client.h"

void Client::logger(QString msg)
{
	QDateTime date;
	qDebug().noquote().nospace() << "["<< date.currentDateTime().toString("yyyy-MM-dd | hh:mm:ss") << "] " << msg;
}

void Client::handleConnection()
{
	logger("connected");
}

void Client::sendMessage()
{
	if(state() == QAbstractSocket::ConnectedState)
	{
		logger("readLine: ");
		QTextStream qtin(stdin);
		QString txt = qtin.readLine();
		write(txt.toUtf8());
		waitForBytesWritten(3000);
		flush();
	}
}

void Client::handleDisconnection()
{
	logger("disconnected");
	QCoreApplication::exit(0);
}

void Client::handleRead()
{
	QString r = readAll().data();
	logger("(response from server) " + r);
	sendMessage();
}

Client::Client()
{
	connectToHost("127.0.0.1", 60000);
	connect(this, SIGNAL(connected()), this, SLOT(handleConnection()));
	connect(this, SIGNAL(disconnected()), this, SLOT(handleDisconnection()));
	connect(this, SIGNAL(readyRead()), this, SLOT(handleRead()));
}

int main(int argc, char **argv)
{
	QCoreApplication a(argc, argv);
	Client client;
	return a.exec();
}
