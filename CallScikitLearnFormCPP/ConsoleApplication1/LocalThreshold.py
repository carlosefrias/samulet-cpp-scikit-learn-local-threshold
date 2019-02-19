def add(a, b):
    return a + b

from skimage.filters import threshold_local

def adaptThres(originalImg, block_size, method, param, offset):
    return originalImg > threshold_local(originalImg, block_size, method=method, param = param, offset=offset)