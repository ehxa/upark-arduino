import serial
import time
import json
import requests

with open('config.txt', 'r') as file:
    url = file.readline().strip()
    

arduino = serial.Serial('/dev/ttyACM0', 9601)
time.sleep(2)  
sensor_data = {}

while True:
    if arduino.in_waiting > 0:
        data = arduino.readline().decode('utf-8').rstrip()
        json_data = {
            "timestamp": int(time.time()),
            "location": data
        }
        json_payload = json.dumps(json_data)
        print(json_payload)
        response = requests.post(f"{url}/location", json=json_data)
        print(response.json())
        sensor_data = {}
