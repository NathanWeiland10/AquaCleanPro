CREATE DATABASE aquacleanpro;
DROP TABLE water_data;
DROP ROLE web_anon;

CREATE TABLE water_data (
	time	TIMESTAMP DEFAULT current_timestamp,
	temp	NUMERIC(5,2),
	ph	NUMERIC(3,1)
);

CREATE ROLE web_anon;
GRANT SELECT ON water_data TO web_anon;
GRANT INSERT ON water_data TO web_anon;
