import numpy as np
import cv2

win = 'template'
filename = 'C:/Users/hlopeth/PycharmProjects/OpenCV/kejt_mikuchchi.jpg'
image1 = cv2.imread(filename)
image = cv2.imread(filename,0)
template = cv2.imread('C:/Users/hlopeth/PycharmProjects/OpenCV/kejt_mikuchchi_template.jpg',0)
w, h = template.shape[::-1]

methods = [cv2.TM_CCOEFF, cv2.TM_CCOEFF_NORMED, cv2.TM_CCORR, cv2.TM_CCORR_NORMED, cv2.TM_SQDIFF, cv2.TM_SQDIFF_NORMED]
for method in methods:
    res = cv2.matchTemplate(image, template, method)
    min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)

    if method in [cv2.TM_SQDIFF, cv2.TM_SQDIFF_NORMED]:
        top_left = min_loc
    else:
        top_left = max_loc
    bottom_right = (top_left[0] + w, top_left[1] + h)
    image_c = image1.copy()
    cv2.rectangle(image_c, top_left, bottom_right, 255, 2)
    cv2.imshow(win,image_c)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


# All the 6 methods for comparison in a list
