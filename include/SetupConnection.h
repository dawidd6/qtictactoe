#pragma once

class CSetupConnection : public QWidget
{
	private:
		QGridLayout layout;
		QLineEdit line_address;
		QStatusBar statusbar;
		QPushButton button_connect;
	public:
		CSetupConnection(CWindow *window, QTcpSocket &socket);
};
