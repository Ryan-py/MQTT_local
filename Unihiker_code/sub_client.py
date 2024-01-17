import time
from unihiker import GUI
import paho.mqtt.client as mqtt

gui=GUI()

# Replace these values with your MQTT broker information
mqtt_broker = "192.168.100.5"
mqtt_port = 1883
mqtt_topic = "nums/val"

in_val = None

def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT broker with result code " + str(rc))
    client.subscribe(mqtt_topic)

def on_message(client, userdata, msg):
    global in_val
    global info_text
    new_val = int(msg.payload.decode())
    print(f"Received message on topic {msg.topic}: {msg.payload.decode()}")
    if in_val is None or new_val != in_val:
        in_val = new_val
        gui.clear()
        
    info_text = gui.draw_text(x=120, y=160, text=in_val, origin='bottom', font_size=70,color="black")
    gui.update()
    time.sleep(0.2)
    

#def display_update(in_val):
 #   info_text = gui.draw_text(x=120, y=160, text=in_val, origin='bottom', font_size=70)
  #  gui.update()
   # print("Working")
    #time.sleep(0.2)

def mqtt_function(mqtt_broker,mqtt_port,mqtt_topic):
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(mqtt_broker, mqtt_port, 60)
    client.loop_forever()


#thread2=gui.start_thread(display_update(in_val))
thread1=gui.start_thread(mqtt_function(mqtt_broker,mqtt_port,mqtt_topic))



while True:
    time.sleep(0.2)