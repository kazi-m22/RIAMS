import serial
import cv2
import json
import digitalio
import board
import RPI.GPIO as io 
from Adafruit_IO import Client,Feed,RequestError
import time

###required function and library for project
class project_lib():
    def __init__(self,ADAFRUIT_IO_KEY='06676552600f44b1aba24e01e6471cfe',ADAFRUIT_IO_USERNAME ='222misbah',timeout=20):
        
        self.ADAFRUIT_IO_KEY = ADAFRUIT_IO_KEY
        self.ADAFRUIT_IO_USERNAME = ADAFRUIT_IO_USERNAME
        self.parsed_datas = '{"current_sensor":0,"temp":0}'
        #initialize adafruit api
        self.aio= Client(self.ADAFRUIT_IO_USERNAME,self.ADAFRUIT_IO_KEY)
        #initialize arduino serial connection
        self.ser = serial.Serial('/dev/ttyACM0',9600,self.timeout)

        ###initializaing required gpio pin
    def init_pin_direction(self):
        io.setmode(io.BCM)
        io.setwarnings(False)
        io.setup(23,io.OUT)
        io.setup(24,io.OUT)
        bulb_data_direction = digitalio.DigitalInOut(board.D5)
        bulb_data_direction.direction= digitalio.Direction.OUTPUT
        movement_sensor_pin_direction = digitalio.DigitalInOut(board.D2)
        movement_sensor_pin_direction.direction=digitalio.Direction.INPUT
        
    def init_adafruit_feeds(self):
        try:
            self.current_feed = aio.feeds('current')
            self.temp_feed = aio.feeds('temp')
        except:
            feed1 = Feed(name="current")
            feed2 = Feed(name="temp")
            self.current_feed = aio.create_feed(feed1)
            self.temp_feed = aio.create_feed(feed2)

    def parsing_json_from_arduino_serial(self):
        #initilize parsed_data     
        try:
            buffer = self.ser.readline()
            received_json = buffer.decode('utf8').replace("'", '"')
            received_json = buffer.decode('utf8').replace('\r', '')
            self.parsed_datas = json.loads(received_json)
        except:
            print('Error: try to parse incomplete message.')
        print(self.parsed_datas)

    def IoT_controller(self):
        #dumping data from list
        current_reading = self.parsed_datas["current"]
        temp_reading = self.parsed_datas["temp"]    
        print('current sensor: '+current_reading+',temp: '+temp_reading)
        self.aio.send_data(self.current_feed.key,current_reading)
        self.aio.send_data(self.temp_feed.key,temp_reading)
        bulb_data=aio.receive(bulb1.key)
   
        time.sleep(2)



        







        








