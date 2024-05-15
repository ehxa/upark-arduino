import serial
import time
import json
from AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient

filePath = "certs.txt"
with open(filePath, 'r') as file:
    lines = file.readlines()

mqttClient = AWSIoTMQTTClient(lines[0].strip())
mqttClient.configureEndpoint(lines[1].strip(), 8883)
mqttClient.configureCredentials(lines[2].strip(), lines[3].strip(), lines[4].strip())
mqttClient.connect()

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
            mqttClient.publish("Arduino1", json_payload, 1)
            sensor_data = {}  
