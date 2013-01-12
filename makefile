
APPLICATION := bin/jsh

SOURCE := src/jsh.c

PKGS := javascriptcoregtk-3.0

PKGCONFIG := $(shell pkg-config --silence-errors --cflags --libs ${PKGS})

OPTIMIZE := -O3 -march=native -mtune=generic

DYNCALL := src/include/dyncall
AUTO_INCLUDES := $(shell build/tools/autoincludes)
REQUIRES := ${DYNCALL} ${AUTO_INCLUDES} $(shell find . -type f -wholename '*.c' -o -wholename '*.h' -o -wholename '*.js' -o -wholename '*.inc') 

all: ${APPLICATION}

# The dyncall files are not "active development files" in this project
# so the make system only provides the required resources, in constant
# locations. DO NOT MODIFY THESE FILES!

${DYNCALL}:
	@build/tools/dynhacker

src/js/common.inc: src/js/common.js
	@echo ''
	@echo Building include file $@ ...
	build/tools/bin2inc js_common_source src/js/common.js > $@
	@echo ''

src/js/core.inc: src/js/core.js
	@echo ''
	@echo Building include file $@ ...
	build/tools/bin2inc js_core_source src/js/core.js > $@
	@echo ''

# This rule builds jsh
${APPLICATION}: ${SOURCE} ${REQUIRES}
	@echo 'Validating required packages...'
	pkg-config --print-errors --exists ${PKGS}
	@echo ''
	@echo 'Building jsh...'
	gcc -o "$@" "${SOURCE}" bin/*.a ${OPTIMIZE} -ldl ${PKGCONFIG}
	@echo ''

