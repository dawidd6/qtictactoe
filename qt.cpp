#include <QApplication>
#include <QPushButton>
#include <QAbstractButton>
#include <QGridLayout>
#include <QString>
#include <QLabel>
#include <QFont>

int main(int argc, char *argv[])
{
	/* IMPORTANT */
	//order of variables DO matter
	//QMainWindow has it's own Layout
	QApplication a(argc, argv);
	QWidget window;
	QGridLayout grid;
	QLabel turn("Whose turn:");
	QLabel current_icon;
	QPushButton button[9];
	QIcon x_icon("x.svg");
	QIcon o_icon("o.svg");
	QSize x_size(90, 90);
	QSize o_size(90, 90);
	QSize current_size(30, 30);
	int rows = 0;
	int columns = 0;
	bool xnow = true;

	window.setLayout(&grid);
	window.setWindowTitle("QTicTacToe");
	window.setFixedSize(0, 0);
	grid.setSpacing(2);
	current_icon.setPixmap(x_icon.pixmap(current_size));

	for(int i = 0; i < 9; i++)
	{
		if(columns == 3)
		{
			rows++;
			columns = 0;
		}
		button[i].setFixedSize(100, 100);
		//button[i].setFlat(true);
		button[i].setFocusPolicy(Qt::NoFocus);
		QObject::connect(&button[i], &QPushButton::clicked, [&button, i, &xnow, &o_icon, &o_size, &x_icon, &x_size, &current_icon, &current_size]
		{
			qDebug("%d", i);
			if(xnow)
			{
				button[i].setIcon(x_icon);
				button[i].setIconSize(x_size);
				current_icon.setPixmap(o_icon.pixmap(current_size));
				xnow = false;
			}
			else
			{
				button[i].setIcon(o_icon);
				button[i].setIconSize(o_size);
				current_icon.setPixmap(x_icon.pixmap(current_size));
				xnow = true;
			}
			button[i].setDisabled(true);
		});
		grid.addWidget(&button[i], rows, columns);
		columns++;
	}

	grid.addWidget(&turn, 4, 0, Qt::AlignCenter);
	grid.addWidget(&current_icon, 4, 1, Qt::AlignCenter);
	window.show();
	return a.exec();
}
