#!/bin/sh
# $Id$
echo '/* $Id$ */' > src/resource/$1.c
echo '#include "kleidi.h"' >> src/resource/$1.c
echo '' >> src/resource/$1.c
xxd -i -n res_$1 $2 >> src/resource/$1.c
