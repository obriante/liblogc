#!/bin/sh

indent $(cat indent.flag) $* $(find -name "*.c" -not -path "*/.git*")

indent $(cat indent.flag) $* $(find -name "*.h" -not -path "*/.git*")

rm $(find -name "*~" -not -path "*/.git*")
