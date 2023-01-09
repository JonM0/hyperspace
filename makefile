EXTENSION = hyperspace
EXTVERSION = 1.0
DISTVERSION = 1.0

MODULES	= $(patsubst %.c,%,$(wildcard src/*.c))
DATA	= $(wildcard sql/*--*.sql)

REGRESS = $(patsubst test/sql/%.sql,%,$(wildcard test/sql/*.sql))
REGRESS_OPTS = --inputdir=test

EXTRA_CLEAN = sql/$(EXTENSION)--$(EXTVERSION).sql


all: sql/$(EXTENSION)--$(EXTVERSION).sql

sql/$(EXTENSION)--$(EXTVERSION).sql: sql/*.sql
	cat $^ > $@


PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)