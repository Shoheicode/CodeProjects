import cv2
import keyboard
import cv2
import numpy as np
import math
import os
import time
import pyautogui

pyautogui.FAILSAFE = True
screenWidth, screenHeight = pyautogui.size()
print(screenWidth, screenHeight)

currentMouseX, currentMouseY = pyautogui.position()
print(currentMouseX, currentMouseY)

# try:
#     pyautogui.click('Projects\Hands\HandControl\Screenshot2022-07-05234915.png')
# except:
#     print("exception occured")

# pyautogui.moveTo(140,120)

#screenshot

counter = 0
while(True):
    try:
        pyautogui.click()
    except:
        if(counter == 0):
            print("exception occured")
            counter +=1
