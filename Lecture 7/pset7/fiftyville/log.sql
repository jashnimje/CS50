-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 1) Check crime_scene_reports
SELECT * FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2020 AND street = "Chamberlin Street";

-- Output
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time
-- — each of their interview transcripts mentions the courthouse.

-- First Clue is to Check courthouse logs


-- 2) Check courthouse_security_logs
SELECT * FROM courthouse_security_logs WHERE hour >= 10 AND day = 28 AND month = 7 AND year = 2020;

-- Suspects

-- 231 | 2020 | 7 | 28 | 8 | 18 | entrance | L93JTIZ
-- 232 | 2020 | 7 | 28 | 8 | 23 | entrance | 94KL13X
-- 240 | 2020 | 7 | 28 | 8 | 36 | entrance | 322W7JE
-- 243 | 2020 | 7 | 28 | 8 | 42 | entrance | 0NTHK55
-- 254 | 2020 | 7 | 28 | 9 | 14 | entrance | 4328GD8
-- 255 | 2020 | 7 | 28 | 9 | 15 | entrance | 5P2BI95
-- 256 | 2020 | 7 | 28 | 9 | 20 | entrance | 6P58WS2
-- 257 | 2020 | 7 | 28 | 9 | 28 | entrance | G412CB7
-- 258 | 2020 | 7 | 28 | 10 | 8 | entrance | R3G7486 - Brandon
-- 259 | 2020 | 7 | 28 | 10 | 14 | entrance | 13FNH73 - Sophia


-- 260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95
-- 261 | 2020 | 7 | 28 | 10 | 18 | exit | 94KL13X
-- 262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2
-- 263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8
-- 264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7
-- 265 | 2020 | 7 | 28 | 10 | 21 | exit | L93JTIZ
-- 266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE
-- 267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55

-- 3) Interview logs
SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2020;

-- 161 | Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- 162 | Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- 163 | Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Clues after 3)
-- Thief left before 10:25

-- ATM
-- Seen at ATM Fifer Street - withdraw
-- Known by Eugene

-- Phone Call Duration under 1 min after 10:15
-- Earliest Flight from fiftyville tomorrow
-- Other Partner Purchased tickets

-- 4) Phone Call Records
SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2020 AND duration <= 60 ORDER BY duration;

-- Suspects
-- 224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
-- 261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38
-- 254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
-- 233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45 - Ernest -> Berthold
-- 255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
-- 251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50 - Evelyn -> Melissa
-- 221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51 - Roger -> Jack
-- 281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54
-- 279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55

-- ATM
SELECT * FROM atm_transactions WHERE day = 28 AND month = 7 AND year = 2020 AND atm_location = "Fifer Street" AND transaction_type = "withdraw";

-- Suspects
-- id | account_number | year | month | day | atm_location | transaction_type | amount
-- 246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
-- 264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
-- 266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
-- 267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
-- 269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
-- 288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
-- 313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
-- 336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35

-- Flights
SELECT * FROM flights WHERE day = 29 AND month = 7 AND year = 2020 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") ORDER BY hour, minute;
-- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
-- 36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20

-- Destination
SELECT * FROM airports WHERE id = 4;
-- id | abbreviation | full_name | city
-- Destination = 4 | LHR | Heathrow Airport | London

-- Passengers
SELECT * FROM passengers WHERE flight_id = 36;

SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);
-- id | name | phone_number | passport_number | license_plate
-- 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X - Ernest -> Berthold
-- 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8 - x
-- 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55 - Evelyn -> Melissa
-- 398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7 - Roger -> Jack

SELECT * FROM bank_accounts WHERE person_id IN (SELECT id FROM people WHERE passport_number = "5773159633");

-- Final Verdict
-- Accused - Ernest and Berthold