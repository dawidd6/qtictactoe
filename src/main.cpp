#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QStackedLayout>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QPicture>
#include <QMessageBox>

/* TESTING CLASSESS */
class Game;

/* FUNCTIONS */
void markDisabledAll(QPushButton button[3][3])
{
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		button[x][y].setDisabled(true);
}


void paintCross(QIcon &icon, QSize &size, const int &thickness)
{
	QPixmap pic(size);
	pic.fill(Qt::transparent);

	QPainter painter(&pic);
	painter.setPen(QPen(Qt::black, thickness));
	painter.setRenderHint(QPainter::Antialiasing);

	QLineF angleline;
	angleline.setLine(7, 7, 93, 93);
	painter.drawLine(angleline);
	angleline.setLine(7, 93, 93, 7);
	painter.drawLine(angleline);

	painter.end();
	icon.addPixmap(pic);
}

void paintCircle(QIcon &icon, QSize &size, const int &thickness)
{
	QPixmap pic(size);
	pic.fill(Qt::transparent);

	QPainter painter(&pic);
	painter.setPen(QPen(Qt::black, thickness));
	painter.setRenderHint(QPainter::Antialiasing);

	painter.drawEllipse(QPointF(50, 50), 45, 45);

	painter.end();
	icon.addPixmap(pic);
}

void paintLine(QLabel &label, int angle, int len, QPointF point, const int &thickness)
{
	QPicture pic;
	QLineF angleline;
	QPainter painter(&pic);

	painter.setPen(QPen(Qt::black, thickness));
	painter.setRenderHint(QPainter::Antialiasing);

	angleline.setP1(point);
	angleline.setAngle(angle);
	angleline.setLength(len);

	painter.drawLine(angleline);
	painter.end();

	label.setPicture(pic);
}


/* MAIN */
int main(int argc, char *argv[])
{
	/* VARIABLES */
	QApplication a(argc, argv);
	QWidget window;
	QStackedLayout layout;
	QMenuBar menubar;
	QMenu help("Help");
	QAction about("About", &help);

	/* GRID_GAME */
	QWidget widget_game;
	QGridLayout grid_game;
	
	/* BOX_MENU */
	QWidget widget_menu;
	QVBoxLayout box_menu;

	QPushButton restart("Restart");
	QPushButton play_single("Play Singleplayer");
	QPushButton play_2v2("Play 2v2");
	QPushButton play_multi("Play Multiplayer");
	QPushButton return_to_menu("Return");
	QPushButton button[3][3];
	QSize size_current(30, 30);

	int thickness = 8;
	int rows = 0;
	int columns = 0;
	char button_str[3][3];
	bool xnow = true;
	char win = 'n';

	QIcon icon_x;
	QIcon icon_o;

	QSize size_x(100, 100);
	QSize size_o(100, 100);
	
	QFrame line[4];

	QLabel left_line;
	QLabel right_line;
	QLabel horizon_line;
	QLabel vertical_line;
	QLabel turn("Whose turn:");
	QLabel icon_current;

	/* PAINT STUFF */
	paintCross(icon_x, size_x, thickness);
	paintCircle(icon_o, size_o, thickness);
	paintLine(vertical_line, 90, 298, QPointF(112, 0), thickness);
	paintLine(horizon_line, 0, 298, QPointF(0, 100), thickness);
	paintLine(left_line, 45, 420, QPointF(0, 100), thickness);
	paintLine(right_line, -45, 420, QPointF(0, 100), thickness);

	/* INITS */
	icon_current.setPixmap(icon_x.pixmap(size_current));
	restart.setFocusPolicy(Qt::NoFocus);
	play_2v2.setFixedSize(305, 40);
	play_single.setFixedSize(305, 40);
	play_multi.setFixedSize(305, 40);
	window.setWindowTitle("QTicTacToe");
	window.setWindowFlags(Qt::Window);
	window.setFixedSize(0, 0);
	window.setLayout(&layout);
	layout.setMenuBar(&menubar);

	widget_game.setLayout(&grid_game);
	widget_menu.setLayout(&box_menu);

	box_menu.setAlignment(Qt::AlignTop);
	box_menu.setSpacing(50);

	layout.addWidget(&widget_game);
	layout.addWidget(&widget_menu);

	grid_game.setSpacing(0);
	grid_game.setRowMinimumHeight(5, 20);
	grid_game.setRowMinimumHeight(6, 40);
	menubar.addMenu(&help);
	help.addAction(&about);
	line[0].setFrameShape(QFrame::HLine);
	line[1].setFrameShape(QFrame::HLine);
	line[2].setFrameShape(QFrame::VLine);
	line[3].setFrameShape(QFrame::VLine);
	line[0].setLineWidth(2);
	line[1].setLineWidth(2);
	line[2].setLineWidth(2);
	line[3].setLineWidth(2);
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		button[x][y].setFixedSize(100, 100);
		button[x][y].setFlat(true);
		button[x][y].setFocusPolicy(Qt::NoFocus);
	}

	/* CONNECTS */
	QObject::connect(&about, &QAction::triggered, [&]
	{
		qDebug("action");
		QMessageBox::about(&window, "About", "QTicTacToe");
	});

	QObject::connect(&restart, &QPushButton::clicked, [&]
	{
		xnow = true;
		win = 'n';
		icon_current.setPixmap(icon_x.pixmap(size_current));
		for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		{
			button_str[x][y] = '0';
			button[x][y].setEnabled(true);
			button[x][y].setIcon(QIcon());
		}
		grid_game.removeWidget(&left_line);
		grid_game.removeWidget(&right_line);
		grid_game.removeWidget(&horizon_line);
		grid_game.removeWidget(&vertical_line);
		left_line.hide();
		right_line.hide();
		horizon_line.hide();
		vertical_line.hide();

	});

	QObject::connect(&play_2v2, &QPushButton::clicked, [&]
	{
		widget_game.show();
		widget_menu.hide();

	});

	QObject::connect(&play_single, &QPushButton::clicked, [&]
	{
		widget_game.show();
		widget_menu.hide();
	});

	QObject::connect(&play_multi, &QPushButton::clicked, [&]
	{
		widget_game.show();
		widget_menu.hide();
	});

	QObject::connect(&return_to_menu, &QPushButton::clicked, [&]
	{
		widget_game.hide();
		widget_menu.show();
	});


	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		QObject::connect(&button[x][y], &QPushButton::clicked, [&, x, y]
		{
			if(xnow)
			{
				button[x][y].setIcon(icon_x);
				button[x][y].setIconSize(size_x);
				button_str[x][y] = 'x';
				icon_current.setPixmap(icon_o.pixmap(size_current));
				xnow = false;
			}
			else
			{
				button[x][y].setIcon(icon_o);
				button[x][y].setIconSize(size_o);
				button_str[x][y] = 'o';
				icon_current.setPixmap(icon_x.pixmap(size_current));
				xnow = true;
			}
			button[x][y].setDisabled(true);

			//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
			if(button_str[0][0] == 'x' && button_str[0][1] == 'x' && button_str[0][2] == 'x')
			{
				grid_game.addWidget(&horizon_line, 0, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll(button);
			}
			else if(button_str[1][0] == 'x' && button_str[1][1] == 'x' && button_str[1][2] == 'x')
			{
				grid_game.addWidget(&horizon_line, 2, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll(button);
			}
			else if(button_str[2][0] == 'x' && button_str[2][1] == 'x' && button_str[2][2] == 'x')
			{
				grid_game.addWidget(&horizon_line, 4, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll(button);
			}
			/*else if(button_str[0] == 'x' && button_str[3] == 'x' && button_str[6] == 'x')
			{
				grid_game.addWidget(&vertical_line, 0, 0, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[1] == 'x' && button_str[4] == 'x' && button_str[7] == 'x')
			{
				grid_game.addWidget(&vertical_line, 0, 2, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[2] == 'x' && button_str[5] == 'x' && button_str[8] == 'x')
			{
				grid_game.addWidget(&vertical_line, 0, 4, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[0] == 'x' && button_str[4] == 'x' && button_str[8] == 'x')
			{
				grid_game.addWidget(&right_line, 0, 0, 5, 5, Qt::AlignJustify);
				right_line.show();
				markDisabledAll();
			}
			else if(button_str[2] == 'x' && button_str[4] == 'x' && button_str[6] == 'x')
			{
				grid_game.addWidget(&left_line, 0, 0, 5, 5, Qt::AlignJustify);
				left_line.show();
				markDisabledAll();
			}
			// OOOOOOOOOOOOOOOOOOOOOOOOOOO
			if(button_str[0] == 'o' && button_str[1] == 'o' && button_str[2] == 'o')
			{
				grid_game.addWidget(&horizon_line, 0, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll();
			}
			else if(button_str[3] == 'o' && button_str[4] == 'o' && button_str[5] == 'o')
			{
				grid_game.addWidget(&horizon_line, 2, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll();
			}
			else if(button_str[6] == 'o' && button_str[7] == 'o' && button_str[8] == 'o')
			{
				grid_game.addWidget(&horizon_line, 4, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll();
			}
			else if(button_str[0] == 'o' && button_str[3] == 'o' && button_str[6] == 'o')
			{
				grid_game.addWidget(&vertical_line, 0, 0, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[1] == 'o' && button_str[4] == 'o' && button_str[7] == 'o')
			{
				grid_game.addWidget(&vertical_line, 0, 2, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[2] == 'o' && button_str[5] == 'o' && button_str[8] == 'o')
			{
				grid_game.addWidget(&vertical_line, 0, 4, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[0] == 'o' && button_str[4] == 'o' && button_str[8] == 'o')
			{
				grid_game.addWidget(&right_line, 0, 0, 5, 5, Qt::AlignJustify);
				right_line.show();
				markDisabledAll();
			}
			else if(button_str[2] == 'o' && button_str[4] == 'o' && button_str[6] == 'o')
			{
				grid_game.addWidget(&left_line, 0, 0, 5, 5, Qt::AlignJustify);
				left_line.show();
				markDisabledAll();
			}*/

		});
	}

	/* GRID ADDONS */
	box_menu.addWidget(&play_single);
	box_menu.addWidget(&play_2v2);
	box_menu.addWidget(&play_multi);
	grid_game.addWidget(&turn, 6, 0);
	grid_game.addWidget(&icon_current, 6, 2);
	grid_game.addWidget(&restart, 6, 4, Qt::AlignRight);
	grid_game.addWidget(&return_to_menu, 7, 4, Qt::AlignRight);
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		if(columns == 5)
		{
			rows++;
			columns = 0;
		}
		if(columns == 1 || columns == 3)
		{
			grid_game.addWidget(&line[2], 0, 1, 5, 1);
			grid_game.addWidget(&line[3], 0, 3, 5, 1);
			columns++;
		}
		if(rows == 1 || rows == 3)
		{
			grid_game.addWidget(&line[0], 1, 0, 1, 5);
			grid_game.addWidget(&line[1], 3, 0, 1, 5);
			rows++;
		}
		grid_game.addWidget(&button[x][y], rows, columns);
		columns++;
	}

	/* SHOW AND RUN */
	window.show();
	widget_menu.show();
	widget_game.hide();
	return a.exec();
}
