import cv2
import math
import numpy as np
import os


def getEuclideanMetric(code1, code2):
    dic1= [0,0,0,0,0,0,0,0,0,0]
    dic2 = [0,0,0,0,0,0,0,0,0,0]
    minLen = min(len(code1), len(code2))
    maxLen = max(len(code1), len(code2))
    sum = 0
    for i in range(0, len(code1)):
        dic1[code1[i]] +=1
    for i in range(0, len(code2)):
        dic2[code2[i]] +=1
    for i in range(0, len(dic1)):
        sum += abs(dic1[i]-dic2[i])
    return sum

def getStupidMetric(code1, code2):
    return math.sqrt((len(code1) - len(code2))**2)

def getFreemanCode(cnt):
    n = len(cnt)
    freemanCode = []
    for i in range(0, n - 1):
        currPoint = cnt[i + 0][0]
        nextPoint = cnt[i + 1][0]
        dir = nextPoint - currPoint
        x = dir[0]
        y = dir[1]
        num = 0
        if x == 0 and y > 0:
            num =0
        elif x > 0 and y > 0:
            num = 1
        elif x > 0 and y == 0:
            num = 2
        elif x > 0 and y < 0:
            num = 3
        elif x == 0 and y < 0:
            num = 4
        elif x < 0 and y < 0:
            num = 5
        elif x < 0 and y == 0:
            num = 6
        elif x < 0 and y > 0:
            num = 7
        if len(freemanCode) == 0 or (len(freemanCode) > 0 and  freemanCode[len(freemanCode)-1] != num):
            freemanCode.append(num)
    return freemanCode

def getContours(fileName):
    im = cv2.imread(fileName)
    #makeBetter(im)
    imgray = cv2.cvtColor(im, cv2.COLOR_RGB2GRAY)
    ret, thresh = cv2.threshold(imgray, 127, 255, 0)
    im2, contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    cnt = contours[1]
    return cnt

def getEuclideanMetricParadniiVhod(img1Name, img2Name):
    return getEuclideanMetric(getFreemanCode(getContours(img1Name)), getFreemanCode(getContours(img2Name)))

per = 0
for j in range(0,10):
    minLen=999.0
    mi = 10
    img1 = "image"+ str(j) + ".png"
    for i in range(0, 10):
        img2 = "Arial_" + str(i) + ".png"
        leng = getEuclideanMetricParadniiVhod(img1, img2)
        #print(i, leng, (getFreemanCode(getContours(img2))))
        if(leng <= minLen):
            minLen = leng
            mi=i
    if(mi == j):
        per += 1
    print("result: ",j, " is ", mi, (getFreemanCode(getContours(img1))))
print(per*10, "%")