# Moist-Plant
Hackathon project for Rockethacks 2025. Written by Nick Hills &amp; Kyle Hixon.

Moist-Plant is a project that measures soil moisture levels for a plant and will water the plant if necessary.

Ardiuno UNO (ELEGOO UNO R3) handles GPIO to read sensor data.

It interfaces with an ESP8266MOD to send HTTP requests to a server running on a laptop.

Built a REST API with Flask to handle HTTP requests on the laptop.

Logs sensor data in a MongoDB database.
