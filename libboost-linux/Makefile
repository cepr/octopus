
ROOT_DIR:=$(abspath ..)
BOOST_DIR:=$(ROOT_DIR)/submodules/boost-svn
BOOST_LIBS:=system

all: release debug

release debug: $(BOOST_DIR)/b2
	mkdir -p $@
	echo "using gcc : : g++ ;" > $(abspath $@)/user-config.jam
	cd $(BOOST_DIR) && BOOST_BUILD_PATH=$(abspath $@) ./b2 \
		--stagedir=$(abspath $@) \
		--build-dir=$(abspath $@) \
		variant=$@ \
		toolset=gcc \
		target-os=linux \
		link=static \
		threading=multi \
		runtime-link=static \
		stage

$(BOOST_DIR)/b2:
	cd $(BOOST_DIR) && ./bootstrap.sh --with-libraries=$(BOOST_LIBS)
	-rm $(BOOST_DIR)/tools/build/v2/user-config.jam

clean:
	rm -rf release debug

.PHONY: release debug all clean

