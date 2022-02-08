#!/usr/bin/env bash
gcc -o ../typing.so typing.c $(yed --print-cflags --print-ldflags)
