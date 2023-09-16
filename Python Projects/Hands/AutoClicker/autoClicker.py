from unittest.result import failfast
import pyautogui as np
import keyboard
from selenium import webdriver
import time

pyautogui.FAILSAFE = True
done = False
grandma = True
error = False
mouseX = 0
mouseY = 0
powerUp1 = False
powerUp2 = False
powerUp3 = False


pyautogui.click(1500,50)

# try:
#     pyautogui.click("Projects\Hands\HandControl\screenshotsforautoclicker\googleSearch.png")
# except:
#     print("error")
#     done = True

# while(done):
#     try:
#         pyautogui.click("Projects\Hands\HandControl\screenshotsforautoclicker\googleSearch.png")
#         if(done):
#             done = False
#     except:
#         print("error")
#         done = True

pyautogui.write("https://cookie-clicker.co/")
pyautogui.press('enter')

try:
    pyautogui.click("Projects\Hands\HandControl\screenshotsforautoclicker\\newcookie.png")
    if(error):
        error = False
except:
    print("error")
    error = True

while(error):
    try:
        pyautogui.click("Projects\Hands\HandControl\screenshotsforautoclicker\\newcookie.png")
        if(error):
            error = False
    except:
        print("error")
        error = True

currentMouseX,currentMouseY = pyautogui.position()


#ADD THREADS!!!!
while(True):
    for i in range(100):
        pyautogui.tripleClick(currentMouseX, currentMouseY)
    try:
        pyautogui.click("Projects\Hands\HandControl\screenshotsforautoclicker\\newx.png")
    except:
        error = False
    else:
        error = False
    # while(error):
    #     try:
    #         pyautogui.click("Projects\Hands\HandControl\screenshotsforautoclicker\\newx.png")
    #     except:
    #         error = False
    if(not powerUp1):
        try:
            pyautogui.click("Projects\Hands\HandControl\screenshotsforautoclicker\\upgrade.png")
        except:
            powerUp1 = False
        else:
            powerUp1 = True
    if(not powerUp2):
        try:
            pyautogui.click("Projects\Hands\HandControl\screenshotsforautoclicker\\upgrade2.png")
        except:
            powerUp2 = False
        else:
            powerUp2 = True
    if(not powerUp3):
        try:
            pyautogui.click("Projects\Hands\HandControl\screenshotsforautoclicker\\upgrade3.png")
        except:
            powerUp3 = False
        else:
            powerUp3 = True
    
    try:
        pyautogui.click("Projects\Hands\HandControl\screenshotsforautoclicker\\newmouse.png")
    except:
        done = False
    else:
        mouseX, mouseY = pyautogui.position()
        for i in range(5):
            pyautogui.doubleClick(mouseX, mouseY)
    try:
        pyautogui.click("Projects\Hands\HandControl\screenshotsforautoclicker\\newgrandma.png")
    except:
        done = False
    else:
        mouseX, mouseY = pyautogui.position()
        for i in range(5):
            pyautogui.doubleClick(mouseX, mouseY)
    # try:
    #     pyautogui.doubleClick("Projects\Hands\HandControl\screenshotsforautoclicker\grandma.png")
    # except:
    #     done = True
    #     print("error1")
    # finally:
    #     pyautogui.tripleClick(currentMouseX, currentMouseY)

    if(keyboard.is_pressed('q')):
        break