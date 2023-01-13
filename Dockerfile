from postgres:15

workdir /usr/src/hyperspace
copy makefile hyperspace.control ./
copy include include/
copy sql sql/
copy src src/

run apt update \
 && apt install -y build-essential postgresql-server-dev-15 \
#  install
 && make && make install \
# clean
 && rm -rf /usr/src/hyperspace \
 && apt purge -y --autoremove build-essential postgresql-server-dev-15 \
 && apt clean \
 && rm -rf /var/lib/apt/lists/*

workdir /

copy load-extensions.sql /docker-entrypoint-initdb.d/