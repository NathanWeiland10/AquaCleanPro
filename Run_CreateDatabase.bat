REM This batch file runs the 'CreateDatabase.sql' script using postgres
REM Using Postgres v16
REM Assumes psql has been added to PATH
psql -U postgres postgres < CreateDatabase.sql
