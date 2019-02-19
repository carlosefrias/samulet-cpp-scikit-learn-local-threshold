
import matplotlib.pyplot as plt
import numpy as np
# from skimage import data
from skimage.filters import threshold_local

import cv2.cv2 as cv2 # Write just: import cv2

filepath = '2mmBrinell250_31.400_-1.000.tif'

image = cv2.imread(filepath, cv2.IMREAD_UNCHANGED)

block_size = 201
binary_adaptive = image > threshold_local(image, block_size, method="gaussian", param = 30, offset=0)

fig, axes = plt.subplots(nrows=2, figsize=(7, 8))
ax0, ax1 = axes
plt.gray()

ax0.imshow(image)
ax0.set_title('Image')

ax1.imshow(binary_adaptive)
ax1.set_title('Adaptive thresholding')

for ax in axes:
    ax.axis('off')

plt.show()
