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

#include "Game.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CGame game;
	return a.exec();
}
