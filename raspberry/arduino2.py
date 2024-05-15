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

arduino = serial.Serial('/dev/ttyACM0', 9600)
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
        mqttClient.publish("Arduino2", json_payload, 1)
