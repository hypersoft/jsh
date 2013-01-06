
APPLICATION := bin/jsh

MACHTYPE := $(shell build/tools/config.sh)

SOURCE := src/jsh.c

SOURCE_INCLUDES := src/include/*.c $(shell echo src/include/{init,init.native,init.etc}.inc)

PKGS := seed

PKGCONFIG := $(shell pkg-config --silence-errors --cflags --libs ${PKGS})

OPTIMIZE := -O3 -march=native -mtune=generic -fomit-frame-pointer -pipe

DYNHOME := src/dyncall-0.7
DYNCALL := src/dyncall

all: ${APPLICATION}

# The dyncall files are not "active development files" in this project
# so the make system only provides the required resources, in constant
# locations. DO NOT MODIFY THESE FILES!

${DYNCALL}:
	@build/tools/dynhacker.org ${DYNHOME}


src/include/init.inc: src/include/js/init.js
	@echo ''
	@echo Building include file $@ ...
	build/tools/bin2inc jsh_init_script src/include/js/init.js > $@
	@echo ''

src/include/init.native.inc: src/include/js/init.native.js
	@echo ''
	@echo Building include file $@ ...
	build/tools/bin2inc jsh_init_native_script src/include/js/init.native.js > $@
	@echo ''

src/include/init.etc.inc: src/include/js/init.etc.js
	@echo ''
	@echo Building include file $@ ...
	build/tools/bin2inc jsh_init_etc_script src/include/js/init.etc.js > $@
	@echo ''


# Shortnames for targets (use -B to force)
init-scripts: src/include/init.inc src/include/init.native.inc src/include/init.etc.inc
dyncall: ${DYNCALL}

# This rule builds jsh
${APPLICATION}: ${DYNCALL} ${SOURCE} ${SOURCE_INCLUDES}
	@echo 'Validating required packages...'
	pkg-config --print-errors --exists ${PKGS}
	@echo ''
	@echo 'Building jsh...'
	gcc -o "$@" "${SOURCE}" bin/*.a ${OPTIMIZE} -ldl ${PKGCONFIG}
	@echo ''

