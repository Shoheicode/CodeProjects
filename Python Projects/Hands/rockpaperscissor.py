import math
from itertools import count
import cv2
import turtle as trtl
import mediapipe as mp

video = cv2.VideoCapture(0)
mp_Hands = mp.solutions.hands
hands = mp_Hands.Hands()
mpDraw = mp.solutions.drawing_utils

finger_Coord = [ (8,6), (12,10), (16,14), (20,18), (29,27), (33, 31), (37, 35),(41,39)]
thumb_Coord = (4,2) 
second_thumb_Coord = (25,23)

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

while True:
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

        upCount = 0
        count = 0
        word = ""

        if handList[12][0] < handList[2][0]:
            word = "left"
        elif handList[12][0] > handList[2][0]:
            word = "right"

        for coordinate in finger_Coord:
            if(count == 4 and len(handList) == 21):
                break
            if handList[coordinate[0]][0] < handList[coordinate[1]][0]:
                upCount += 1
            count = count + 1 
        if handList[12][0] > handList[2][0]:
            if handList[thumb_Coord[0]][0] < handList[thumb_Coord[1]][0]:
                upCount += 1
        elif handList[12][0] < handList[2][0]:
            if handList[thumb_Coord[0]][0] > handList[thumb_Coord[1]][0]:
                upCount += 1
        cv2.putText(image, word, (0,200), font, fontScale, color ,thickness,cv2.LINE_AA)

    cv2.imshow('Finger Counter', image)

    if cv2.waitKey(25) & 0xFF == ord('q'):
      break