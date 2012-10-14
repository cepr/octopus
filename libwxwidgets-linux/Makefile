# Build rules

all: $(ConfigName)/Makefile $(ConfigName)/cxxflags $(ConfigName)/ldflags
	cd $(ConfigName) && $(MAKE)

.PHONY: $(ConfigName)

# Makefile, wx-config and cxxflags for Eclipse path and symbols discovery

FLAGS := --enable-stl --disable-shared --enable-monolithic
DEBUG := --enable-debug
CONFIGURE := ../../submodules/wxWidgets/configure

Debug/Makefile:
	mkdir -p Debug
	cd Debug && $(CONFIGURE) $(FLAGS) $(DEBUG)

Release/Makefile:
	mkdir -p Release
	cd Release && $(CONFIGURE) $(FLAGS)

$(ConfigName)/cxxflags: $(ConfigName)/Makefile
	$(ConfigName)/wx-config --cxxflags >$@

$(ConfigName)/ldflags: $(ConfigName)/Makefile
	$(ConfigName)/wx-config --libs > $@

# Clean

clean:
	cd $(ConfigName) && $(MAKE) clean
