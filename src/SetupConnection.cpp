#include <QtWidgets>
#include <QtNetwork>

#include "Window.h"

#include "SetupConnection.h"

SetupConnection::SetupConnection(Window *window, QTcpSocket &socket)
{
	window->setCentralWidget(this);

	line_address.setFixedSize(300, 40);
	button_connect.setFixedSize(100, 40);
	button_connect.setText("Connect");
	line_address.setText("localhost");

	setLayout(&layout);
	layout.setSpacing(30);
	layout.addWidget(&line_address);
	layout.addWidget(&button_connect, 0, 0, Qt::AlignRight);
	layout.addWidget(&statusbar);

	statusbar.setSizeGripEnabled(false);

	connect(&button_connect, &QPushButton::clicked, [&]
	{
		socket.connectToHost(line_address.text(), 60000);
		if(socket.waitForConnected(5000))
			statusbar.showMessage("Connected, waiting for opponent");
		else
			statusbar.showMessage(socket.errorString());
	});

	show();
	window->adjustSize();
}
