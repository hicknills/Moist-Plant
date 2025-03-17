import os
from flask import Flask, Response, request, jsonify
from dotenv import load_dotenv
from pymongo import MongoClient
from bson.json_util import dumps

load_dotenv()

app = Flask(__name__)
mongo_db_url = "mongodb+srv://MOIST-PLANT:MOIST-PLANT@moist-plant-db.1ar5z.mongodb.net/?retryWrites=true&w=majority&appName=MOIST-PLANT-DB" # DB url
mongo_db_name = "Plant-Project" # get DB name

client = MongoClient(mongo_db_url)
db = client[mongo_db_name]

@app.route('/')
def home():
    return "Welcome to the Flask App! Navigate to /api/sensors to interact with sensors."

# this will respond to any HTTP GET request with the path "/api/sensors", with args looks like /api/sensors?sensor_id=led_1
@app.get("/api/sensors")
def get_sensors():
    sensor_id = request.args.get('sensor_id')  # Use 'sensor_id' instead of 'name'
    filter = {"sensor_id": sensor_id}  # Update the filter to use 'sensor_id'
    print("filter: ", filter)
    sensors = list(db.Sensors.find(filter))  # query MongoDB with the updated filter
    
    # Convert BSON object to JSON and send the response
    response = Response(response=dumps(sensors), status=200, mimetype="application/json")
    return response

# respond to POST, add the json doc that is passed, 
# has form of http://localhost:5000/api/sensors -H 'Content-Type: application/json' -d '<json_object>'
# THIS FORM WORKS:
# http://localhost:5000/api/sensors -H "Content-Type: application/json" -d "{\"sensor_id\": \"led_2\", \"description\": \"This is our 2nd LED\", \"enabled\": true, \"type\": \"toggle\",\"value\": \"off\"}"

@app.post("/api/sensors")
def add_sensor():
    if not request.is_json:  # Check if request contains JSON
        return jsonify({"error": "Request must be JSON"}), 415

    _json = request.get_json()  # Safe way to parse JSON
    if not _json:
        return jsonify({"error": "Invalid JSON"}), 400  # Bad Request

    # Insert data into MongoDB
    db.Sensors.insert_one(_json)

    return jsonify({"message": "Sensor added successfully"}), 201  # Use 201 for created

@app.route('/helloesp')
def helloHandler():
    return 'Hello ESP8266, from Flask'
 
if __name__ == "__main__":
   app.run(host='0.0.0.0', port=80) # open app to all IPs on port 80
