
from skimage.filters import threshold_local
import cv2.cv2 as cv2 #Use only: import cv2
import numpy as np

def add(a, b):
    return a + b

def adaptThres(imageArray, block_size, method, param, offset):
    print("Python\t\timageArray[500][425]\t", imageArray[500][425])
    print(imageArray[0:10][0:10])
    result =  imageArray > threshold_local(imageArray, block_size, method=method, param = param, offset=offset)
    print(result[0:10][0:10])
    return result
    

def convert_1d_to_2d_array(array):
    size = int(np.sqrt(len(array)))
    return np.reshape(array, (-1, size))

# adaptThres("image.tif", 201, "gaussian", 30, 0, "result.tif")
# imgArray = np.array([1,2,3,4,5,6,20000,30000,50000,30000,40000,12,13,14,15,16])
# imgArray = convert_1d_to_2d_array(imgArray)
# result = adaptThres(imgArray, 5, "gaussian", 30, 0)
# print(result)