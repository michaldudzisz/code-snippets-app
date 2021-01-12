set DB_FILENAME=snippet_db.db

if exist %DB_FILENAME% rem %DB_FILENAME%

sqlite3 > setup.sql
