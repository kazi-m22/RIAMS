from pel_project import project_lib 

p= project_lib()
p.init_pin_direction()
p.init_adafruit_feeds()
while True:
    p.parsing_json_from_arduino_serial()
    p.IoT_controller()