import matplotlib.pyplot as plt
import scipy.ndimage as nd
from skimage import data

# Apartado 1
img = data.brick()
plt.imshow(img)
plt.show()

# Apartado 2
print(img.dtype, img.shape)

# Apartado 3
imgSobel = nd.sobel(img, axis=0, mode='constant')

sigma = 10
imgGaus = nd.gaussian_filter(img, sigma=sigma)

# Apartado 4
fig, ax = plt.subplots(nrows=1, ncols=3, figsize=(8, 5))

ax[0].imshow(img)
ax[1].imshow(imgGaus)
ax[2].imshow(imgSobel)

fig.tight_layout()

plt.show()
