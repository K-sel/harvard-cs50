select * from crime_scene_reports
where year=2024 and month=7 and day=28 and street='humphrey street';

select * from interviews
where year=2024 and month=7 and day=28;

select account_number
from atm_transactions
where year=2024 and month=7 and day=28
  and atm_location='leggett street'
  and transaction_type='withdraw';

select person_id, account_number
from bank_accounts
where account_number in (28500762,28296815,76054385,49610011,16153065,25506511,81061156,26013199);

select id, name, phone_number, license_plate
from people
where id in (395717,396669,438727,449774,458378,467400,469845,490173);

select license_plate, minute
from bakery_security_logs
where year=2024 and month=7 and day=28
  and activity='exit'
  and hour=10
  and minute between 15 and 25;

select name, phone_number, license_plate
from people
where license_plate in ('5P2BI95','94KL13X','6P58WS2','4328GD8','G412CB7','L93JTIZ','322W7JE','0NTHK55')
and id in (395717,396669,438727,449774,458378,467400,469845,490173);

select caller, receiver, duration
from phone_calls
where year=2024 and month=7 and day=28
  and duration < 60
  and caller in ('(367) 555-5533','(499) 555-9472','(609) 555-5876','(286) 555-6063','(770) 555-1861','(031) 555-6622','(826) 555-1652','(338) 555-6650');

select name from people
where phone_number = '(375) 555-8161';

select id from airports where city='fiftyville';

select id, destination_airport_id, hour, minute
from flights
where year=2024 and month=7 and day=29
  and origin_airport_id = 8
order by hour, minute
limit 1;

select city from airports
where id = 4;

select passport_number
from passengers
where flight_id = 36;

select name, passport_number
from people
where passport_number in (5773159633, 5773159632, 5773159634, 5773159635, 5773159636);
