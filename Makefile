build:
	@g++ qt.cpp -o qt $(shell pkg-config --cflags --libs Qt5Widgets) -Wall -fPIC -std=c++14
