#!/bin/sh

FILE=".unischedrc"
if [[ -n "$1" ]]; then
    FILE="$1"
fi

. "$(pwd)/$FILE"

if [[ -z "$UNISCHED" ]]; then
    echo "UNISCHED is not set!" >&2
    exit 1
fi

UNISCHED_ARGS=

if [[ -z "$IFACE" ]]; then
    echo "Warning: IFACE is not set, using default!" >&2
else
    UNISCHED_ARGS="$UNISCHED_ARGS --iface $IFACE"
fi

if [[ -z "$STORAGE" ]]; then
    echo "Warning: STORAGE is not set, your work will not be saved!" >&2
else
    UNISCHED_ARGS="$UNISCHED_ARGS --storage $STORAGE"

    case "$STORAGE" in
    SQLITE)
        if [[ -z "$SQLITE_DB" ]]; then
            SQLITE_DB=".raspisator.db"
        else
            UNISCHED_ARGS="$UNISCHED_ARGS --sqlite-db $SQLITE_DB"
        fi
        if [[ ! ( -e "$SQLITE_DB" ) ]]; then
            UNISCHED_ARGS="$UNISCHED_ARGS --sqlite-create"
        fi
        ;;
    *)
        ;;
    esac
fi

echo "$UNISCHED_ARGS"

UNISCHED_MODULES_PATH="$MODULES_PATH" \
UNISCHED_ALGORITHMS_PATH="$ALGORITHMS_PATH" \
UNISCHED_ALGORITHMS="$ALGORITHMS" \
"$UNISCHED" $UNISCHED_ARGS $EXTRA_ARGS
exit $?

