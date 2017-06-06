#pragma once

class SetupConnection : public QWidget
{
	private:
		QGridLayout layout;
		QLineEdit line_address;
		QStatusBar statusbar;
		QPushButton button_connect;
	public:
		SetupConnection(Window *window, QTcpSocket &socket);
};
