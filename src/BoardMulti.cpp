#include <QtWidgets>
#include <QtNetwork>

#include "Window.h"
#include "AbstractSymbol.h"
#include "Circle.h"
#include "Cross.h"
#include "AbstractBoard.h"
#include "SetupConnection.h"
#include "Game.h"

#include "BoardMulti.h"

CBoardMulti::CBoardMulti(CWindow *window, CGame *game) : CAbstractBoard(window), w(window), g(game)
{
	hide();
	w->centralWidget()->setParent(0);
	setup_connection = new CSetupConnection(window, socket);

	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		connect(&button[x][y], &QPushButton::clicked, [&, x, y]
		{
			makeMove(x, y, symbol_my, symbol_char_my, false, "Opponent's turn");
			socket.write(QByteArray(QByteArray::number(x) + ',' + QByteArray::number(y)));
			socket.waitForBytesWritten(3000);
			markDisabledAll();
		});
	}

	connect(&socket, &QTcpSocket::connected, this, &CBoardMulti::handleConnection);
	connect(&button_restart, &QPushButton::clicked, this, &CBoardMulti::handleRestart);

	statusbar.setSizeGripEnabled(false);
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
	CGame::logger("Received: " + response);
	if(setup_connection != nullptr)
	{
		setup_connection->hide();
		delete setup_connection;
		setup_connection = nullptr;
		w->setCentralWidget(this);
		show();

		handleRandom();
	}
	else
	{
		if(response.contains("restart"))
		{
			enum QMessageBox::StandardButton btn = QMessageBox::question(this, "Restart request", "Opponent wants to restart the game\n\nAgreed?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			if(btn == QMessageBox::Yes)
				socket.write("ry");
			else
				socket.write("rn");
		}
		else if(response.contains("rn"))
		{
			QMessageBox::information(this, "Info", "Opponent has not agreed");
			if(turn)
			{
				if(!win) markEnabledWhatLeft();
				else if(win) statusbar.showMessage("LOST");
				else if(!yallGotAnyMoreOfThemButtons()) statusbar.showMessage("DRAW");
				else statusbar.showMessage("Your turn");
			}
			else
			{
				if(win) statusbar.showMessage("WIN");
				else if(!win) statusbar.showMessage("LOST");
				else if(!yallGotAnyMoreOfThemButtons()) statusbar.showMessage("DRAW");
				else statusbar.showMessage("Opponent's turn");

				markDisabledAll();
			}
			button_restart.setEnabled(true);
		}
		else if(response.contains("r-"))
		{
			restartBoard();
			handleRandom();
			button_restart.setEnabled(true);
		}
		else if(response.contains("dis"))
		{
			QMessageBox::information(this, "Info", "Opponent has disconnected\n\nPress OK to return to menu");
			g->handleReturn();
		}
		else
		{
			makeMove(response[0].digitValue(), response[2].digitValue(), symbol_enemy, symbol_char_enemy, true, "Your turn");
			markEnabledWhatLeft();
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
	checkConditions();
	if(win && turn) statusbar.showMessage("LOST");
	else if(win && !turn) statusbar.showMessage("WIN");
	else if(!yallGotAnyMoreOfThemButtons())
		statusbar.showMessage("DRAW");
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
	button_restart.setDisabled(true);
	socket.write("restart");
	statusbar.showMessage("Waiting for response");
}

void CBoardMulti::handleRandom()
{
	turn = response[2].digitValue();
	symbol_char_my = response[3];

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
