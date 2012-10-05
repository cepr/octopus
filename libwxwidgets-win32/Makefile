
# Makefile creation

FLAGS := --enable-stl --disable-shared --host=i586-mingw32msvc
DEBUG := --enable-debug
CONFIGURE := ../../submodules/wxWidgets/configure

Debug/Makefile:
	mkdir -p Debug
	cd Debug && $(CONFIGURE) $(FLAGS) $(DEBUG)

Release/Makefile:
	mkdir -p Release
	cd Release && $(CONFIGURE) $(FLAGS)

# Build rules

.PHONY: $(ConfigName)

all: $(ConfigName)/Makefile
	cd $(ConfigName) && $(MAKE)

# Clean

clean:
	cd $(ConfigName) && $(MAKE) clean
