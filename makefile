EXTENSION = hyperspace
EXTVERSION = 1.0
DISTVERSION = 1.0

MODULES	= $(patsubst %.c,%,$(wildcard src/**/*.c))
DATA = $(wildcard sql/*--*.sql)

REGRESS_BASE = test-base
REGRESS = $(REGRESS_BASE) $(filter-out $(REGRESS_BASE),$(patsubst test/sql/%.sql,%,$(wildcard test/sql/*.sql)))
REGRESS_OPTS = --inputdir=test

EXTRA_CLEAN = sql/$(EXTENSION)--$(EXTVERSION).sql

PG_CFLAGS = -Iinclude
PG_CPPFLAGS = -Iinclude


all: sql/$(EXTENSION)--$(EXTVERSION).sql

sql/$(EXTENSION)--$(EXTVERSION).sql: sql/type.sql sql/ops.sql sql/abs.sql sql/kd.sql
	cat $+ > $@



PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)