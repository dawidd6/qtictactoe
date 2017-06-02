#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QTcpSocket>
#include <QStatusBar>
#include <QWidget>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QStackedLayout>

#include "Window.h"

#include "SetupConnection.h"

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
