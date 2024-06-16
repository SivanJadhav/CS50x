-- Keep a log of any SQL queries you execute as you solve the mystery.
-- The Only info: Crime happened on July 28 2023, Humphrey Street.

-- Schema of All Tables:
-- CREATE TABLE crime_scene_reports (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     street TEXT,
--     description TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE interviews (
--     id INTEGER,
--     name TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     transcript TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE atm_transactions (
--     id INTEGER,
--     account_number INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     atm_location TEXT,
--     transaction_type TEXT,
--     amount INTEGER,
--     PRIMARY KEY(id)
-- );

-- CREATE TABLE bank_accounts (
--     account_number INTEGER,
--     person_id INTEGER,
--     creation_year INTEGER,
--     FOREIGN KEY(person_id) REFERENCES people(id)
-- );
-- CREATE TABLE airports (
--     id INTEGER,
--     abbreviation TEXT,
--     full_name TEXT,
--     city TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE flights (
--     id INTEGER,
--     origin_airport_id INTEGER,
--     destination_airport_id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     PRIMARY KEY(id),
--     FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
--     FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
-- );
-- CREATE TABLE passengers (
--     flight_id INTEGER,
--     passport_number INTEGER,
--     seat TEXT,
--     FOREIGN KEY(flight_id) REFERENCES flights(id)
-- );
-- CREATE TABLE phone_calls (
--     id INTEGER,
--     caller TEXT,
--     receiver TEXT,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     duration INTEGER,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE people (
--     id INTEGER,
--     name TEXT,
--     phone_number TEXT,
--     passport_number INTEGER,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );
-- CREATE TABLE bakery_security_logs (
--     id INTEGER,
--     year INTEGER,
--     month INTEGER,
--     day INTEGER,
--     hour INTEGER,
--     minute INTEGER,
--     activity TEXT,
--     license_plate TEXT,
--     PRIMARY KEY(id)
-- );

-- Getting Description:
-- Time of Theft = 10:15am
-- Street = Humphrey Street
-- Suspected Location = Location
-- No. Of Interviews = 3
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';

-- IMPORTANT TRANSCRIPT:
SELECT * FROM interviews 
WHERE transcript LIKE '%bakery%';

-- Using Information From Ruth -- Bakery Stuff
SELECT hour, minute, activity, name FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE month = 7
AND day = 28
AND hour = 10
AND minute >= 9 AND minute <= 21;

-- Using Information From Eugene -- ATM Transactions
SELECT name, transaction_type, atm_location FROM atm_transactions

JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON bank_accounts.person_id = people.id

WHERE atm_transactions.month = 7 
AND atm_transactions.day = 28
AND atm_transactions.transaction_type = 'withdraw'
AND atm_transactions.atm_location LIKE '%Legget%';

-- Using Information From Raymond -- Phone Call
SELECT
    caller.name AS Caller,
    receiver.name AS Receiver,
    phone_calls.duration AS Duration
FROM
    phone_calls
JOIN people AS caller ON caller.phone_number = phone_calls.caller
JOIN people AS receiver ON receiver.phone_number = phone_calls.receiver
WHERE
    phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration < 60;

-- Using Information From Raymond -- Flight Ticket
SELECT people.name, destination_airport_id, flights.hour, flights.destination_airport_id FROM flights 

JOIN passengers ON passengers.flight_id = flights.id 
JOIN people ON people.passport_number = passengers.passport_number 
JOIN airports ON airports.id = flights.destination_airport_id 

WHERE flights.month = 7 
AND flights.day = 29 
AND flights.origin_airport_id = 8

ORDER BY flights.hour, flights.minute;

-- Joining All Information
SELECT p.name FROM bakery_security_logs AS bsl

  -- Joining Stuff
JOIN people AS p ON bsl.license_plate = p.license_plate
JOIN bank_accounts AS ba ON ba.person_id = p.id
JOIN atm_transactions ON atm_transactions.account_number = ba.account_number
JOIN phone_calls ON phone_calls.caller = p.phone_number  

  -- Line By Line Conditions
WHERE (bsl.month = 7 AND bsl.day = 28 AND bsl.hour = 10 AND bsl.activity = 'exit' AND bsl.minute BETWEEN 15 AND 25)
AND (atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.transaction_type = 'withdraw' AND atm_transactions.atm_location LIKE '%Legget%')
AND (phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration < 60);
