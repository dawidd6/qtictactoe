#Assembled by dawidd6
PROGRAM=qtictactoe
COMPILER=g++
PKG_CONFIG=pkg-config

CXXFLAGS=-Wall -fPIC -std=c++11
INCLUDES=$(shell $(PKG_CONFIG) --cflags Qt5Core Qt5Gui Qt5Network Qt5Widgets) -Iinclude -Iinclude/srv

LIBS=-lQt5Widgets -lQt5Gui -lQt5Core -lQt5Network
LDFLAGS=

SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)

START_COLOR=\033[0;33m
CLOSE_COLOR=\033[m

all: banner $(PROGRAM)

src/%.o: src/%.cpp
	@echo "$(START_COLOR)[CXX]$(CLOSE_COLOR)   $<"
	@$(COMPILER) -c -o $@ $< $(CXXFLAGS) $(INCLUDES)

$(PROGRAM): $(OBJ)
	@echo "$(START_COLOR)[LD]$(CLOSE_COLOR)   $@"
	@$(COMPILER) -o $@ $^ $(LIBS) $(LDFLAGS)

install:
	@echo "$(START_COLOR)[INSTALL]$(CLOSE_COLOR)   /usr/bin/$(PROGRAM)"
	@echo "$(START_COLOR)[INSTALL]$(CLOSE_COLOR)   /usr/share/applications/$(PROGRAM).desktop"
	@install -d $(DESTDIR)/usr/bin
	@install -d $(DESTDIR)/usr/share/applications
	@install $(PROGRAM) $(DESTDIR)/usr/bin
	@install data/$(PROGRAM).desktop $(DESTDIR)/usr/share/applications

uninstall:
	@echo "$(START_COLOR)[RM]$(CLOSE_COLOR)   /usr/bin/$(PROGRAM)"
	@echo "$(START_COLOR)[RM]$(CLOSE_COLOR)   /usr/share/applications/$(PROGRAM).desktop"
	@rm -rf /usr/bin/$(PROGRAM)
	@rm -rf /usr/share/applications/$(PROGRAM).desktop

clean:
	@echo "$(START_COLOR)[RM]$(CLOSE_COLOR)   src/*.o $(PROGRAM)"
	@rm -rf src/*.o $(PROGRAM)

debian:
	@echo "$(START_COLOR)[DH]$(CLOSE_COLOR)   debian"
	@debuild -us -uc
	@debuild clean

docs:
	@echo "$(START_COLOR)[DOXYGEN]$(CLOSE_COLOR)   docs"
	@rm -rf docs
	@doxygen Doxyfile > /dev/null
	@touch docs/.nojekyll

vim:
	@vim src/*.cpp include/*.h

banner:
	@head -n 8 src/main.cpp |cut -d '*' -f2

win:
	$(eval export PATH=/home/dawidd6/git/mxe/usr/bin:$(PATH))
	i686-w64-mingw32.static-qmake-qt5
	make -f Makefile
	@cat .gitignore |grep -v release| xargs rm -rf

.PHONY: install uninstall clean debian docs vim banner win
