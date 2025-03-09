-- Keep a log of any SQL queries you execute as you solve the mystery.

-- To know the tables in fiftyville.db, then to examine and understand the crime_scene_reports table
.tables
.schema crime_scene_reports

-- To find the description oof te particular crime we are interested in.
-- Found out that the crime took place by 10:15 am and there were 3 witnesses
SELECT description FROM crime_scene_reports WHERE year = 2023 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- To examine the interviews table and look for those of the witnesses.
-- Ruth mentioned checking CCTV footage. Eugene mentioned ATM at Leggett Street.
-- Raymond hints that the accomplice booked the flight for the next day around that time (10:15)
.schema interviews
SELECT name, transcript FROM interviews WHERE year = 2023 AND month = 7 AND day = 28;

-- To examine the CCTV footage around the timeframe. Ruth said the thief left the parking lot.
-- Thief suspects license plates: 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ
.schema bakery_security_logs
SELECT activity, license_plate, minute FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10;

-- To examine the atm transactions that from that morning
-- Thief suspects: (acc_no 28500762, amount withdrawn 48); (28296815, amt= 20); (76054385, amt= 60); (49610011, amt= 50)
.schema atm_transactions
SELECT account_number, transaction_type, amount, atm_location FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28;

-- To examine phone calls from around that time
-- Thief suspects phone num: (130) 555-0289, *twice*(499) 555-9472, (367) 555-5533, (286) 555-6063
-- Accomplice suspects phone num: (996) 555-8899, (892) 555-8872, (375) 555-8161, (717) 555-1342, (676) 555-6554
.schema phone_calls
SELECT caller, receiver, duration FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60;

-- To examine the bank accounts of the suspects, then get their names
-- Suspects BRUCE and TAYLOR
.schema bank_accounts
.schema people
SELECT name, phone_number, license_plate, passport_number FROM bank_accounts JOIN people ON bank_accounts.person_id = people.id
    WHERE account_number IN (28500762, 28296815, 76054385, 49610011);
