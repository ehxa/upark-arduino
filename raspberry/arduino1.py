import serial
import time
import json
import requests

with open('config.txt', 'r') as file:
    url = file.readline().strip()

def reset_arduino(arduino):
    arduino.dtr = False
    time.sleep(1)
    arduino.dtr = True
    time.sleep(2)

def read_from_arduino_1():
    try:
        arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
        reset_arduino(arduino)
        sensor_data = {}
        while True:
            if arduino.in_waiting > 0:
                data = arduino.readline().decode('utf-8').rstrip()
                sensor_id, status = data.split("-")
                sensor_data[sensor_id] = status
                if len(sensor_data) == 4:
                    json_data = {
                        "timestamp": int(time.time()),
                        "device_id": "Arduino1",
                        **sensor_data
                    }
                    json_payload = json.dumps(json_data)
                    print(json_payload)
                    try:
                        response = requests.post(f"{url}/spots", json=json_data)
                        print(response.json())
                    except requests.exceptions.RequestException as e:
                        print(f"Request error: {e}")
                    sensor_data = {}
    except serial.SerialException as e:
        print(f"Serial error: {e}")
    finally:
        if arduino and arduino.is_open:
            arduino.close()

if __name__ == "__main__":
    read_from_arduino_1()
