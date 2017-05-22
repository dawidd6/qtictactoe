#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QPicture>
#include <QTcpSocket>
#include <QDateTime>
#include <QByteArray>

#include "Window.h"
#include "Board2v2.h"
#include "BoardMulti.h"

BoardMulti::BoardMulti(Window *window) : Board2v2(window), counter(0)
{
	socket.connectToHost("127.0.0.1", 60000);
	connect(&socket, SIGNAL(connected()), this, SLOT(handleConnection()));
	connect(&restart, SIGNAL(clicked()), this, SLOT(handleRestart()));
	socket.waitForReadyRead(-1);

	if(symbol_my == 'x')
	{
		icon_my = &icon_x;
		size_my = &size_x;
		icon_enemy = &icon_o;
		size_enemy = &size_o;
		symbol_enemy = 'o';
	}
	else if(symbol_my == 'o')
	{
		icon_my = &icon_o;
		size_my = &size_o;
		icon_enemy = &icon_x;
		size_enemy = &size_x;
		symbol_enemy = 'x';
	}

	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		disconnect(&button[x][y], 0, 0, 0);
		connect(&button[x][y], &QPushButton::clicked, [&, x, y]
		{
			if(turn)
			{
				button[x][y].setDisabled(true);
				button[x][y].setIcon(*icon_my);
				button[x][y].setIconSize(*size_my);
				button_str[x][y] = symbol_my;
				label_current.setPixmap(icon_enemy->pixmap(size_current));
				turn = false;
				socket.write(QByteArray(QByteArray::number(x) + ',' + QByteArray::number(y)));
				socket.waitForBytesWritten(3000);
				markDisabledAll();
				checkConditions();
			}
		});
	}
	if(!turn) markDisabledAll();
}

BoardMulti::~BoardMulti()
{
	qDebug("called destructor");
	if(socket.state() == QAbstractSocket::ConnectedState)
		socket.disconnectFromHost();
}

void BoardMulti::logger(QString msg)
{
	QDateTime date;
	qDebug().noquote().nospace() << "["<< date.currentDateTime().toString("yyyy-MM-dd | hh:mm:ss") << "] " << msg;
}

void BoardMulti::handleRead()
{
	if(counter == 0)
	{
		response = socket.readAll().data();
		turn = response[0].digitValue();
		symbol_my = response[1];
		logger("Greeting: " + response);
		counter++;
	}
	else
	{
		logger("Reading...");
		response = socket.readAll().data();
		if(response == "restart")
		{
			label_current.setPixmap(icon_x.pixmap(size_current));
			if(symbol_my == 'x')
			{
				turn = true;
				markEnabledAll();
			}
			else
			{
				turn = false;
				markDisabledAll();
			}
			for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
			{
				button_str[x][y] = '0';
				button[x][y].setIcon(QIcon());
			}
			layout.removeWidget(&left_line);
			layout.removeWidget(&right_line);
			layout.removeWidget(&horizon_line);
			layout.removeWidget(&vertical_line);
			left_line.hide();
			right_line.hide();
			horizon_line.hide();
			vertical_line.hide();
		}
		else
		{
			int x = response[0].digitValue();
			int y = response[2].digitValue();
			button[x][y].setDisabled(true);
			button[x][y].setIcon(*icon_enemy);
			button[x][y].setIconSize(*size_enemy);
			button_str[x][y] = symbol_enemy;
			label_current.setPixmap(icon_my->pixmap(size_current));
			turn = true;
			markEnabledWhatLeft();
			checkConditions();
		}
		logger("Received: " + response);
	}
}

void BoardMulti::handleConnection()
{
	logger("Connected");
	connect(&socket, SIGNAL(readyRead()), this, SLOT(handleRead()));
	connect(&socket, SIGNAL(disconnected()), this, SLOT(handleDisconnection()));
}

void BoardMulti::handleDisconnection()
{
	logger("Disconnected, exiting...");
}

void BoardMulti::handleRestart()
{
	label_current.setPixmap(icon_x.pixmap(size_current));
	if(symbol_my == 'x')
	{
		turn = true;
		markEnabledAll();
	}
	else
	{
		turn = false;
		markDisabledAll();
	}
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		button_str[x][y] = '0';
		button[x][y].setIcon(QIcon());
	}
	layout.removeWidget(&left_line);
	layout.removeWidget(&right_line);
	layout.removeWidget(&horizon_line);
	layout.removeWidget(&vertical_line);
	left_line.hide();
	right_line.hide();
	horizon_line.hide();
	vertical_line.hide();
	socket.write("restart");
}
