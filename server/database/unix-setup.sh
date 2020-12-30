#! /bin/sh

DB_FILENAME="snippet_db.db"

if test -f "$DB_FILENAME"; then
    rm $DB_FILENAME
fi

sqlite3 < setup.sql
