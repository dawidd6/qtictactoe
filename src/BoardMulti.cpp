#include "Window.h"
#include "Board2v2.h"
#include "BoardMulti.h"
#include "Game.h"

BoardMulti::BoardMulti(Window *window) : Board2v2(window), counter(0)
{
	hide();
	win = window;
	win->layout.removeWidget(this);
	window->adjustSize();
	setup_connection = new SetupConnection(window, socket);
	setup_connection->show();
	connect(setup_connection, &SetupConnection::signalSuccess, this, &BoardMulti::handleConnection);
	//connect(&socket, SIGNAL(connected()), this, SLOT(handleConnection()));
	connect(&restart, SIGNAL(clicked()), this, SLOT(handleRestart()));

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
	markDisabledAll();
}

BoardMulti::~BoardMulti()
{
	if(socket.state() == QAbstractSocket::ConnectedState)
		socket.disconnectFromHost();
	if(setup_connection != nullptr)
		delete setup_connection;
}

void BoardMulti::handleRead()
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
		symbol_my = response[1];
		Game::logger("Greeting: " + response);
		counter++;
		if(symbol_my == 'x')
		{
			icon_my = &icon_x;
			size_my = &size_x;
			icon_enemy = &icon_o;
			size_enemy = &size_o;
			symbol_enemy = 'o';
			markEnabledAll();
			turn = true;
		}
		else if(symbol_my == 'o')
		{
			icon_my = &icon_o;
			size_my = &size_o;
			icon_enemy = &icon_x;
			size_enemy = &size_x;
			symbol_enemy = 'x';
			turn = false;
		}
	}
	else
	{
		Game::logger("Reading...");
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
		Game::logger("Received: " + response);
	}
}

void BoardMulti::handleConnection()
{
	Game::logger("Connected");

	connect(&socket, SIGNAL(readyRead()), this, SLOT(handleRead()));
	connect(&socket, SIGNAL(disconnected()), this, SLOT(handleDisconnection()));
}

void BoardMulti::handleDisconnection()
{
	Game::logger("Disconnected");
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

SetupConnection::SetupConnection(Window *window, QTcpSocket &socket)
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
		{
			statusbar.showMessage("Connected, waiting for opponent");
			emit signalSuccess();
		}
		else
		{
			statusbar.showMessage(socket.errorString());
			Game::logger("Connection failed");
		}
	});
}
