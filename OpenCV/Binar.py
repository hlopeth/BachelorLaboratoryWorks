import cv2

win = 'binar'
image = cv2.imread('C:/Users/hlopeth/PycharmProjects/OpenCV/kejt_mikuchchi.jpg',0)
modes = [cv2.THRESH_BINARY,cv2.THRESH_BINARY_INV,cv2.THRESH_TRUNC,cv2.THRESH_TOZERO,cv2.THRESH_TOZERO_INV]
cv2.imshow(win,image)
for mod in modes:
    ret,bin = cv2.threshold(image,127,255,mod)
    cv2.imshow(win,bin)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

image = cv2.imread('C:/Users/hlopeth/PycharmProjects/OpenCV/kejt_mikuchchi.jpg')
image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
th2 = cv2.adaptiveThreshold(image,255,cv2.ADAPTIVE_THRESH_MEAN_C,cv2.THRESH_BINARY,11,2)
cv2.imshow(win,th2)
cv2.waitKey(0)
cv2.destroyAllWindows()

th3 = cv2.adaptiveThreshold(image,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY,11,2)
cv2.imshow(win,th3)
cv2.waitKey(0)
cv2.destroyAllWindows()
