import numpy as np
import cv2

win = 'segmentation'
filename = 'C:/Users/hlopeth/PycharmProjects/OpenCV/kejt_mikuchchi.jpg'
image1 = cv2.imread(filename)
image = cv2.imread(filename,0)
ret,thresh = cv2.threshold(image,127,255,cv2.THRESH_TOZERO_INV)
contours, _ = cv2.findContours(thresh,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)[-2:]
i=0
for contour in contours:
    cv2.drawContours(image1, contours, i, (0,255,0), 5)
    i+=1
cv2.imshow(win,image1)
cv2.waitKey(0)
cv2.destroyAllWindows()