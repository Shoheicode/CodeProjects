import math
from itertools import count
import cv2
import turtle as trtl
import mediapipe as mp
import CoDrone
from ctypes import cast, POINTER
from comtypes import CLSCTX_ALL


#VIDEO
video = cv2.VideoCapture(0)
wn = trtl.Screen() 
screen = trtl.Screen()

#HANDS
mp_Hands = mp.solutions.hands
hands = mp_Hands.Hands()
mpDraw = mp.solutions.drawing_utils
finger_Coord = [ (8,6), (12,10), (16,14), (20,18), (29,27), (33, 31), (37, 35),(41,39)]
thumb_Coord = (4,2) 
second_thumb_Coord = (25,23)

#STATES
global isCounting
isCounting = False
global isThumbsUPDOWN
isThumbsUPDOWN = False

# drone
# drone = CoDrone.CoDrone()
# drone.pair(drone.Nearest)


# font
font = cv2.FONT_HERSHEY_SIMPLEX
  
# org
org = (50, 50)
  
# fontScale
fontScale = 5

# Blue color in BGR
color = (255, 0, 0)
  
# Line thickness of 2 px
thickness = 2

counter = trtl.Turtle()
counter.penup()
counter.hideturtle()
counter.goto(-300, 100)
counter.write("Thumbs Up    Hand Counter", font=("Arial", 40, "normal"))
# counter.goto(-300,100)
# counter.write("Thumbs Up", font=("Arial", 40, "normal"))

buttonOne = trtl.Turtle()
buttonOne.hideturtle()
buttonOne.speed(0)
buttonOne.penup()
buttonOne.goto(-150,0)
buttonOne.fillcolor("Red")
buttonOne.begin_fill()
buttonOne.circle(50)
buttonOne.end_fill()

buttonTwo = trtl.Turtle()
buttonTwo.hideturtle()
buttonTwo.speed(0)
buttonTwo.penup()
buttonTwo.goto(150,0)
buttonTwo.fillcolor("Blue")
buttonTwo.begin_fill()
buttonTwo.circle(50)
buttonTwo.end_fill()

def moveCircle(turt):
    turt.fillColor("orange")
    turt.begin_fill()
    turt.circle(50)
    turt.end_fill()

def distance(xOne,yOne, xTwo, yTwo):
    return math.sqrt((xOne-xTwo)**2 + (yOne-yTwo)**2)

def screen_clicked(x,y):
    global isCounting, isThumbsUPDOWN
    if(distance(-150,50,x,y) <= 50):
        isThumbsUPDOWN = True  
        wn.bye()
    if(distance(150,50,x,y) <= 50): 
        isCounting = True
        wn.bye()   

def turtle_clicked(x , y):
    global isCounting 
    isCounting = True

#trtl.onclick(turtle_clicked)

wn.onclick(screen_clicked)
wn.mainloop()


while isCounting:
    success, image = video.read()

    RGB_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    results = hands.process(RGB_image)

    multiLandMarks = results.multi_hand_landmarks

    if multiLandMarks:
        handList = []

        for handLms in multiLandMarks:
            mpDraw.draw_landmarks(image, handLms, mp_Hands.HAND_CONNECTIONS)

            for idx, lm in enumerate(handLms.landmark):
                h,w,c = image.shape
                
                cx,cy = int(lm.x * w) , int(lm.y * h)
                handList.append((cx,cy))
                
                for point in handList:
                    cv2.circle(image, point, 10, (255,255,0), cv2.FILLED)
        
        # print(handList)
        upCount = 0

        count = 0
        for coordinate in finger_Coord:
            if(count == 4 and len(handList) == 21):
                break
            if handList[coordinate[0]][1] < handList[coordinate[1]][1]:
                upCount += 1
            count = count + 1 
        
        if handList[12][0] > handList[2][0]:
            if handList[thumb_Coord[0]][0] < handList[thumb_Coord[1]][0]:
                upCount += 1
        if handList[12][0] < handList[2][0]:
            if handList[thumb_Coord[0]][0] > handList[thumb_Coord[1]][0]:
                upCount += 1
        if len(handList) > 21:
            if handList[33][0] > handList[23][0]:
                if handList[second_thumb_Coord[0]][0] < handList[second_thumb_Coord[1]][0]:
                    upCount += 1
            elif handList[33][0] < handList[23][0]:
                if handList[second_thumb_Coord[0]][0] > handList[second_thumb_Coord[1]][0]:
                    upCount += 1

        # if handList[thumb_Coord[0]][0] > handList[thumb_Coord[1]][0]:
        #     upCount += 1

        cv2.putText(image, str(upCount), (0,200), font, fontScale, color ,thickness,cv2.LINE_AA)

    cv2.imshow('Finger Counter', image)

    if cv2.waitKey(25) & 0xFF == ord('q'):
      break

while isThumbsUPDOWN:

    success, image = video.read()

    RGB_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    results = hands.process(RGB_image)

    multiLandMarks = results.multi_hand_landmarks

    upCount = ""

    if multiLandMarks:
        handList = []

        for handLms in multiLandMarks:
            mpDraw.draw_landmarks(image, handLms, mp_Hands.HAND_CONNECTIONS)

            for idx, lm in enumerate(handLms.landmark):
                h,w,c = image.shape
                
                cx,cy = int(lm.x * w) , int(lm.y * h)
                handList.append((cx,cy))
                
                for point in handList:
                    cv2.circle(image, point, 10, (255,255,0), cv2.FILLED)
        
        # print(handList)
        upCount = ""
        upOtherhand=""

        if handList[12][0] > handList[2][0]:
            if handList[thumb_Coord[0]][1] < handList[thumb_Coord[1]][1]:
                upCount ="UP"
            elif handList[thumb_Coord[0]][1] > handList[thumb_Coord[1]][1]:
                upCount ="DOWN"
            elif (handList[thumb_Coord[0]][1]-handList[thumb_Coord[1]][1]) < 100 and handList[thumb_Coord[0]][0] > handList[thumb_Coord[1]][0]:
                upCount ="left"
            elif handList[thumb_Coord[0]][1] > handList[thumb_Coord[1]][1]:
                upCount ="DOWN"
        if handList[12][0] < handList[2][0]:
            if handList[thumb_Coord[0]][1] < handList[thumb_Coord[1]][1]:
                upCount ="UP"
            elif handList[thumb_Coord[0]][1] > handList[thumb_Coord[1]][1]:
                upCount ="DOWN"
        if len(handList) > 21:
            if handList[33][0] > handList[23][0]:
                if handList[second_thumb_Coord[0]][1] < handList[second_thumb_Coord[1]][1]:
                    upOtherhand ="UP"
                elif handList[second_thumb_Coord[0]][1] > handList[second_thumb_Coord[1]][1]:
                    upOtherhand ="DOWN"
            elif handList[33][0] < handList[23][0]:
                if handList[second_thumb_Coord[0]][1] < handList[second_thumb_Coord[1]][1]:
                    upOtherhand ="UP"
                elif handList[second_thumb_Coord[0]][1] > handList[second_thumb_Coord[1]][1]:
                    upOtherhand ="DOWN"

        # if handList[thumb_Coord[0]][0] > handList[thumb_Coord[1]][0]:
        #     upCount += 1

        cv2.putText(image, str(upCount), (0,200), font, fontScale, color ,thickness,cv2.LINE_AA)
        cv2.putText(image, str(upOtherhand), (100,100), font, fontScale, color ,thickness,cv2.LINE_AA)

    if upCount == "UP":
        movingCircle.clear()

        moveCircle(movingCircle)
        
        screen.update()

        movingCircle.forward(0.5)

    
    # if upCount == "DOWN":
    #     print("WE'RE GOING DOWN")

    cv2.imshow('ThumbsUpDown', image)

    if cv2.waitKey(25) & 0xFF == ord('q'):
      break

