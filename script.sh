#!/bin/sh

curl -X GET "https://api.openweathermap.org/data/2.5/weather?q={$1}&appid=a2e7b468ff34f76343177fccca3a39a5&units=metric" > weather.json
