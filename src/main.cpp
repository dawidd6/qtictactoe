/*     ________  __________  __________  __________
 *    /  __   /\/___   ___/\/___   ___/\/___   ___/\
 *   /  / /  / /\__/  / ___/\__/  / ___/\__/  / ___/
 *  /  /_/  / /   /  / /      /  / /      /  / /
 * /____   / /   /__/ /      /__/ /      /__/ /
 * \___/__/ /    \___/       \___/       \___/
 *     \___/
 *
 */

#include <QApplication>
#include <QtWidgets>
#include <QtNetwork>

#include "Game.h"
#include "Server.h"

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		QApplication a(argc, argv);
		Game game;
		return a.exec();
	}
	else if(QString(argv[1]) == "server")
	{
		QCoreApplication a(argc, argv);
		Server server;
		return a.exec();
	}
	else
	{
		qDebug("Wrong argument\n\n"
				"\tqtictactoe server - run headless server\n"
				"\tqtictactoe - run graphical client\n");
		return 1;
	}
}
