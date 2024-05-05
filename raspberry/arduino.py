import serial
import time
import boto3
from AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient

print("Hello! Sending from Arduino to AWS IoT...")
filePath = "certs.txt"

with open(filePath, 'r') as file:
    lines = file.readlines()  
    

mqttClient = AWSIoTMQTTClient(lines[0].strip())
mqttClient.configureEndpoint(lines[1].strip(), 8883)
mqttClient.configureCredentials(lines[2].strip(), lines[3].strip(), lines[4].strip())

mqttClient.connect()

arduino_Output = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(2)

while True:
    if arduino_Output.in_waiting > 0:
        serial_Line = arduino_Output.readline().decode('utf-8').rstrip()
        print(serial_Line)
        mqttClient.publish("arduino", serial_Line, 1)

