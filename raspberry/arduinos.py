import serial
import time
import json
import requests

with open('config.txt', 'r') as file:
    url = file.readline().strip()

arduino1 = serial.Serial('/dev/ttyACM1', 9600)
arduino2 = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(2)

sensor_data_1 = {}
sensor_data_2 = {}

def read_arduino_data(arduino, sensor_data, device_id, num_sensors):
    if arduino.in_waiting > 0:
        serial_line = arduino.readline().decode('utf-8').rstrip()
        sensor_id, status = serial_line.split("-")
        sensor_data[sensor_id] = status

        if len(sensor_data) == num_sensors:
            return {
                "timestamp": int(time.time()),
                "device_id": device_id,
                **sensor_data
            }
    return None

while True:
    data_1 = read_arduino_data(arduino1, sensor_data_1, "Arduino1", 4)
    data_2 = read_arduino_data(arduino2, sensor_data_2, "Arduino2", 1)  

    if data_1 or data_2:
        combined_data = {
            "timestamp": int(time.time()),
            "Arduino1": data_1 if data_1 else {},
            "Arduino2": data_2 if data_2 else {}
        }
        json_payload = json.dumps(combined_data)
        print(json_payload)
        response = requests.post(url, json=combined_data)
        print(response.json())
        
        if data_1:
            sensor_data_1.clear()
        if data_2:
            sensor_data_2.clear()
