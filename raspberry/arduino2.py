import serial
import time
import json
import requests

with open('config.txt', 'r') as file:
    url = file.readline().strip()

def read_from_arduino():
    arduino = None
    try:
        arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
        time.sleep(2)
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
    except serial.SerialException as e:
        print(f"Serial error: {e}")
    finally:
        if arduino and arduino.is_open:
            arduino.close()

if __name__ == "__main__":
    read_from_arduino()

