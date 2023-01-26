import json
import serial
import time

connection = serial.Serial("COM3", 9600)
connection.reset_input_buffer()

while True:
    data = connection.readline().decode("utf-8")
    # print(data)
    try:
        dict_json = json.loads(data)
        print(dict_json)
    except json.JSONDecodeError as e:
        print("JSON:", e)
    if int(time.time() % 60) % 10 < 5:
        data = {}
        data["temp"] = 10.00005
        data["humidity"] = 20.00005
        data = json.dumps(data)

        if connection.isOpen():
            connection.write(data.encode('ascii'))
            connection.flush()
