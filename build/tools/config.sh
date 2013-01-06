#!/bin/bash

[[ -n "$MACHTYPE" ]] && {
	echo $MACHTYPE;
	exit;
}

echo $0: error: unsupported system >&2;

exit 1;
