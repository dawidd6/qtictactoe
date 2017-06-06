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
#include <QCoreApplication>
#include <QtWidgets>
#include <QtNetwork>

#include "Game.h"
#include "Server.h"

int main(int argc, char *argv[])
{
	QCoreApplication *a = nullptr;
	Game *game = nullptr;
	Server *server = nullptr;

	try
	{
		if(argc < 2)
		{
			a = new QApplication(argc, argv);
			game = new Game;
		}
		else if(QString(argv[1]) == "server")
		{
			a = new QCoreApplication(argc, argv);
			server = new Server;
		}
		else
		{
			qDebug("Wrong argument\n\n"
					"\tqtictactoe server - run headless server\n"
					"\tqtictactoe - run graphical client\n");
			return 1;
		}
	}
	catch(std::bad_alloc &ba)
	{
		qDebug("Exception caught: %s", ba.what());
		abort();
	}

	QObject::connect(a, &QCoreApplication::aboutToQuit, [&game, &server]
	{
		if(game != nullptr) delete game;
		if(server != nullptr) delete server;
	});

	return a->exec();
}
