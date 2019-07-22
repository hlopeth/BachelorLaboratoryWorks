import cv2

win = 'smooth'
image = cv2.imread('C:/Users/hlopeth/PycharmProjects/OpenCV/kejt_mikuchchi.jpg',0)
blur = cv2.GaussianBlur(image,(111,1),0)
cv2.imshow(win,blur)
cv2.waitKey(0)
cv2.destroyAllWindows()