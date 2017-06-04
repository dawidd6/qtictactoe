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
#include <QMessageBox>
#include <QPainter>

#include "Window.h"
#include "AbstractSymbol.h"
#include "Circle.h"
#include "Cross.h"
#include "AbstractBoard.h"
#include "SetupConnection.h"
#include "Game.h"

#include "BoardMulti.h"

CBoardMulti::CBoardMulti(CWindow *window, CGame *game) : CAbstractBoard(window), counter(0)
{
	hide();
	win = window;
	g = game;
	win->removeFromLayout(this);
	win->adjustSize();
	setup_connection = new CSetupConnection(window, socket);
	setup_connection->show();

	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
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

	connect(&socket, &QTcpSocket::connected, this, &CBoardMulti::handleConnection);
	connect(&restart, &QPushButton::clicked, this, &CBoardMulti::handleRestart);

	layout.setRowMinimumHeight(7, 30);
	layout.addWidget(&statusbar, 7, 0, 1, 5);
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
	response = socket.readAll().data();
	CGame::logger("Reading...");
	if(counter == 0)
	{
		setup_connection->hide();
		delete setup_connection;
		setup_connection = nullptr;
		win->addToLayout(this);
		show();
		counter++;

		handleRandom();
	}
	else
	{
		if(response == "restart")
		{
			enum QMessageBox::StandardButton btn = QMessageBox::question(this, "Restart request", "Opponent wants to restart the game\n\nAgreed?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			if(btn == QMessageBox::Yes)
				socket.write("ry");
			else
				socket.write("rn");

		}
		else if(response == "rn")
		{
			QMessageBox::information(this, "Info", "Opponent has not agreed");
			if(turn)
				statusbar.showMessage("Your turn");
			else
				statusbar.showMessage("Opponent's turn");
			markEnabledWhatLeft();
		}
		else if(response[0] == 'r' && response[1] == '-')
		{
			handleRandom();
			restartBoard();
		}
		else if(response == "dis")
		{
			QMessageBox::information(this, "Info", "Opponent has disconnected\n\nPress OK to return to menu");
			g->handleReturn();
		}
		else
		{
			makeMove(response[0].digitValue(), response[2].digitValue(), symbol_enemy, symbol_char_enemy, true, "Your turn");
			markEnabledWhatLeft();
			checkConditions();
			CGame::logger("Received: " + response);
		}
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

void CBoardMulti::handleRestart()
{
	markDisabledAll();
	socket.write("restart");
	statusbar.showMessage("Waiting for response");
}

void CBoardMulti::handleRandom()
{
	turn = response[2].digitValue();
	symbol_char_my = response[3];
	CGame::logger("Greeting: " + response);

	if(symbol_char_my == 'x')
	{
		symbol_my = &cross;
		symbol_enemy = &circle;
		symbol_char_enemy = 'o';
	}
	else if(symbol_char_my == 'o')
	{
		symbol_my = &circle;
		symbol_enemy = &cross;
		symbol_char_enemy = 'x';
	}

	if(turn)
	{
		statusbar.showMessage("Your turn");
		markEnabledAll();
	}
	else
	{
		statusbar.showMessage("Opponent's turn");
		markDisabledAll();
	}

	label_turn.setText("Your symbol:");
	label_current.setPixmap(symbol_my->getIcon().pixmap(size_current));
}
