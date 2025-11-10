#!/bin/sh
# $Id$
echo '/* $Id$ */' > src/$1.c
echo '#include "kleidi.h"' >> src/$1.c
echo '' >> src/$1.c
xxd -i -n $1 $2 >> src/$1.c
