def add(a, b):
    return a + b

from skimage.filters import threshold_local
import cv2.cv2 as cv2 #Use only: import cv2

def adaptThres(path, block_size, method, param, offset, resultPath):
    originalImg = cv2.imread(path, cv2.IMREAD_UNCHANGED)
    thresholdedImg = originalImg > threshold_local(originalImg, block_size, method=method, param = param, offset=offset)
    thresholdedImg = thresholdedImg.astype('uint16')
    cv2.imwrite(resultPath, thresholdedImg)

adaptThres("image.tif", 201, "gaussian", 30, 0, "result.tif")
