import pygame_widgets
import pygame
from pygame_widgets.slider import Slider
from pygame_widgets.textbox import TextBox
from pygame_widgets.toggle import Toggle
import serial,struct
from time import sleep
pygame.init()
comport = 'COM3'#change this to the com port
pygame.display.set_caption("Octupuss shooter")
win = pygame.display.set_mode((500, 600))
transmit = serial.Serial(comport,9600,)#transmit
servo = Slider(win, 20, 100, 470, 40, min=0, max=180, step=1,initial=90,handleColour=(122,0,220))
output = TextBox(win, 225, 200, 50, 50, fontSize=30)
flywheel = Toggle(win,60,250,70,50,onColour=(122,0,220),handleOnColour=(122,15,240))
fire = Toggle(win,60,340,70,50,onColour=(240,100,0),handleOnColour=(240,120,12))
output.disable()  # Act as label instead of textbox
dedsec = pygame.image.load('Logo_dedsec.png').convert()
tiny = pygame.transform.scale(dedsec,(200,140))
run = True
while run:
    events = pygame.event.get()
    for event in events:
        if event.type == pygame.QUIT:
            pygame.quit()
            run = False
            quit()
    win.fill((60, 60, 60))
    a = servo.getValue()
    b = flywheel.getValue()
    d = fire.getValue()
    win.blit(tiny,(240,400))
    data_string = str(int(a)) + ',' + str(bool(b)) + ',' + str(bool(d))
    print(data_string.encode())
    transmit.write(b'>')
    transmit.write(data_string.encode())
    output.setText(servo.getValue())
    pygame_widgets.update(events)
    pygame.display.update()