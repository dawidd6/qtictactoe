#Assembled by dawidd6
COMPILER=g++
CXXFLAGS=$(shell pkg-config --cflags --libs Qt5Widgets) -Wall -fPIC -std=c++11 -Iinclude
PROGRAM=qtictactoe
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)
START_COLOR=\033[0;33m
CLOSE_COLOR=\033[m
DESTDIR=

src/%.o: src/%.cpp
	@echo "$(START_COLOR)[CXX]$(CLOSE_COLOR)   $<"
	@$(COMPILER) -c -o $@ $< $(CXXFLAGS)

$(PROGRAM): $(OBJ)
	@echo "$(START_COLOR)[LD]$(CLOSE_COLOR)   $@"
	@$(COMPILER) -o $@ $^ $(CXXFLAGS)

install:
	@echo "$(START_COLOR)[INSTALL]$(CLOSE_COLOR)   /usr/bin/$(PROGRAM)"
	@echo "$(START_COLOR)[INSTALL]$(CLOSE_COLOR)   /usr/share/applications/$(PROGRAM).desktop"
	@echo "$(START_COLOR)[INSTALL]$(CLOSE_COLOR)   /etc/xdg/autostart/$(PROGRAM).desktop"
	@install -d $(DESTDIR)/usr/bin
	@install -d $(DESTDIR)/usr/share/applications
	@install -d $(DESTDIR)/etc/xdg/autostart
	@install $(PROGRAM) $(DESTDIR)/usr/bin
	@install $(PROGRAM).desktop $(DESTDIR)/usr/share/applications
	@install $(PROGRAM).desktop $(DESTDIR)/etc/xdg/autostart

uninstall:
	@echo "$(START_COLOR)[RM]$(CLOSE_COLOR)   /usr/bin/$(PROGRAM)"
	@echo "$(START_COLOR)[RM]$(CLOSE_COLOR)   /usr/share/applications/$(PROGRAM).desktop"
	@echo "$(START_COLOR)[RM]$(CLOSE_COLOR)   /etc/xdg/autostart/$(PROGRAM).desktop"
	@rm -rf /usr/bin/$(PROGRAM)
	@rm -rf /usr/share/applications/$(PROGRAM).desktop
	@rm -rf /etc/xdg/autostart/$(PROGRAM).desktop

clean:
	@echo "$(START_COLOR)[RM]$(CLOSE_COLOR)   $(OBJ) $(PROGRAM)"
	@rm -rf $(OBJ) $(PROGRAM)

debian:
	debuild --no-tgz-check
	dh clean

.PHONY: install uninstall clean debian
