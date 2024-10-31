#!/bin/sh

if which ninja >/dev/null; then
    cmake -B build -G Ninja && \
    ninja -C build $1
else
    cmake -B build && \
    make -j $(getconf _NPROCESSORS_ONLN) -C build $1
fi
exit $?
