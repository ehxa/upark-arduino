import serial
import time
import json
import requests

with open('config.txt', 'r') as file:
    url = file.readline().strip()

arduino = serial.Serial('/dev/ttyACM1', 9600)
time.sleep(2)

sensor_data = {}

while True:
    if arduino.in_waiting > 0:
        serial_line = arduino.readline().decode('utf-8').rstrip()
        sensor_id, status = serial_line.split("-")
        sensor_data[sensor_id] = status  

        if len(sensor_data) == 4:  
            json_data = {
                "timestamp": int(time.time()),
                **sensor_data  
            }
            json_payload = json.dumps(json_data)
            print(json_payload)
            response = requests.post(f"{url}/spots", json=json_data)
            print(response.json())
            sensor_data = {}
