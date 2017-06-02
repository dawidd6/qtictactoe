#include <QPushButton>
#include <QGridLayout>
#include <QIcon>
#include <QSize>
#include <QLineEdit>
#include <QTcpSocket>
#include <QStatusBar>
#include <QLabel>
#include <QAction>
#include <QMenuBar>
#include <QStackedLayout>

#include "Window.h"
#include "Symbols.h"
#include "Board2v2.h"
#include "Game.h"

#include "BoardMulti.h"

CBoardMulti::CBoardMulti(CWindow *window) : CBoard2v2(window), counter(0)
{
	hide();
	disconnect(&restart, 0, 0, 0);
	win = window;
	win->layout.removeWidget(this);
	window->adjustSize();
	setup_connection = new CSetupConnection(window, socket);
	setup_connection->show();
	connect(&socket, &QTcpSocket::connected, this, &CBoardMulti::handleConnection);
	connect(&restart, &QPushButton::clicked, this, &CBoardMulti::handleRestart);

	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		disconnect(&button[x][y], 0, 0, 0);
		connect(&button[x][y], &QPushButton::clicked, [&, x, y]
		{
			if(turn)
			{
				makeMove(x, y, symbol_my, symbol_char_my, false, "Opponent's turn");
				socket.write(QByteArray(QByteArray::number(x) + ',' + QByteArray::number(y)));
				socket.waitForBytesWritten(3000);
				markDisabledAll();
				checkConditions();
			}
		});
	}

	layout.setRowMinimumHeight(7, 30);
	layout.addWidget(&statusbar, 7, 0, 1, 5);
	markDisabledAll();
}

CBoardMulti::~CBoardMulti()
{
	if(socket.state() == QAbstractSocket::ConnectedState)
		socket.disconnectFromHost();
	if(setup_connection != nullptr)
		delete setup_connection;
}

void CBoardMulti::handleRead()
{
	if(counter == 0)
	{
		setup_connection->hide();
		delete setup_connection;
		setup_connection = nullptr;
		win->layout.addWidget(this);
		show();

		response = socket.readAll().data();
		turn = response[0].digitValue();
		symbol_char_my = response[1];
		CGame::logger("Greeting: " + response);
		counter++;
		
		if(symbol_char_my == 'x')
		{
			symbol_my = &cross;
			symbol_enemy = &circle;
			symbol_char_enemy = 'o';
			markEnabledAll();
			turn = true;
		}
		else if(symbol_char_my == 'o')
		{
			symbol_my = &circle;
			symbol_enemy = &cross;
			symbol_char_enemy = 'x';
			turn = false;
		}
		
		if(turn)
			statusbar.showMessage("Your turn");
		else
			statusbar.showMessage("Opponent's turn");

		label_turn.setText("Your symbol:");
		label_current.setPixmap(symbol_my->getIcon().pixmap(size_current));
	}
	else
	{
		CGame::logger("Reading...");
		response = socket.readAll().data();
		if(response == "restart") restartBoard();
		else
		{
			makeMove(response[0].digitValue(), response[2].digitValue(), symbol_enemy, symbol_char_enemy, true, "Your turn");
			markEnabledWhatLeft();
			checkConditions();
		}
		CGame::logger("Received: " + response);
	}
}

void CBoardMulti::makeMove(const int &x, const int &y, const CAbstractSymbol *symbol, QChar symbol_char, bool isMyTurn, QString message)
{
	button[x][y].setDisabled(true);
	button[x][y].setIcon(symbol->getIcon());
	button[x][y].setIconSize(symbol->getSize());
	button_str[x][y] = symbol_char;
	turn = isMyTurn;
	statusbar.showMessage(message);
}

void CBoardMulti::handleConnection()
{
	CGame::logger("Connected");

	connect(&socket, &QTcpSocket::readyRead, this, &CBoardMulti::handleRead);
	connect(&socket, &QTcpSocket::disconnected, this, &CBoardMulti::handleDisconnection);
}

void CBoardMulti::handleDisconnection()
{
	CGame::logger("Disconnected");
}

void CBoardMulti::restartBoard()
{
	if(symbol_char_my == 'x')
	{
		turn = true;
		statusbar.showMessage("Your turn");
		markEnabledAll();
	}
	else
	{
		turn = false;
		statusbar.showMessage("Opponent's turn");
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

void CBoardMulti::handleRestart()
{
	restartBoard();
	socket.write("restart");
}

CSetupConnection::CSetupConnection(CWindow *window, QTcpSocket &socket)
{
	window->layout.addWidget(this);
	window->adjustSize();

	setLayout(&layout);
	layout.setSpacing(30);

	line_address.setFixedSize(300, 40);
	button_connect.setFixedSize(100, 40);

	line_address.setText("Address");
	button_connect.setText("Connect");

	layout.addWidget(&line_address);
	layout.addWidget(&button_connect, 0, 0, Qt::AlignRight);
	layout.addWidget(&statusbar);

	connect(&button_connect, &QPushButton::clicked, [&]
	{
		socket.connectToHost(line_address.text(), 60000);
		if(socket.waitForConnected(5000))
			statusbar.showMessage("Connected, waiting for opponent");
		else
			statusbar.showMessage(socket.errorString());
	});
}
