
APPLICATION := bin/jsh

SOURCE := src/jsh.c

PKGS := javascriptcoregtk-3.0

PKGCONFIG := $(shell pkg-config --silence-errors --cflags --libs ${PKGS})

OPTIMIZE := -O3 -march=native -mtune=generic

DYNCALL := src/include/dyncall
AUTO_INCLUDES := $(shell build/tools/autoincludes)
REQUIRES := ${DYNCALL} ${AUTO_INCLUDES} $(shell find src -type f -wholename '*.c' -o -wholename '*.h' -o -wholename '*.js' -o -wholename '*.inc') 

all: ${APPLICATION}

# The dyncall files are not "active development files" in this project
# so the make system only provides the required resources, in constant
# locations. DO NOT MODIFY THESE FILES!

${DYNCALL}:
	@build/tools/dynhacker
	@echo ''

src/js/common.inc: src/js/common.js
	@echo Building include file $@ ...
	build/tools/bin2inc js_common_source src/js/common.js > $@
	@echo ''

src/js/core.inc: src/js/core.js
	@echo Building include file $@ ...
	build/tools/bin2inc js_core_source src/js/core.js > $@
	@echo ''

src/include/contributors.inc: share/docs/LICENSE/Hypersoft-Contributary.md
	@echo Generating contributive work license...
	build/tools/bin2inc help_license_contributors share/docs/LICENSE/Hypersoft-Contributary.md > src/include/contributors.inc
	@echo ''

contributors: src/include/contributors.inc

# This rule builds jsh
${APPLICATION}: ${SOURCE} ${REQUIRES} contributors
	@echo 'Validating required packages...'
	@pkg-config --print-errors --exists ${PKGS}
	@echo ''
	@echo 'Building jsh...'
	gcc -o "$@" "${SOURCE}" bin/*.a ${OPTIMIZE} -ldl ${PKGCONFIG}
	@echo ''

