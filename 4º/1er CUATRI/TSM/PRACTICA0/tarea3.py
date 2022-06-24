import matplotlib.pyplot as plt
from skimage import io, img_as_float32, color

# Apartado 1
img = io.imread('https://bit.ly/2Zjkcm7')
plt.imshow(img)
plt.show()

# Apartado 2
print('Imagen original: ' + str(img.dtype)
    + ' ' + str(img.shape) + ' ' + str(img.max()))

# Apartado 3
floatImage = img_as_float32(img)
print('Imagen float: ' + str(floatImage.dtype) + ' ' + str(floatImage.shape))

# Apartado 4
hsvImage = color.rgb2hsv(floatImage)
plt.imshow(hsvImage)
plt.show()

# Apartado 5
redChannel = floatImage[:, :, 0]  # canal rojo
greenChannel = floatImage[:, :, 1]  # canal verde
blueChannel = floatImage[:, :, 2]  # canal azul

fig, ax = plt.subplots(nrows=1, ncols=3, figsize=(8, 5))

ax[0].imshow(redChannel)
ax[1].imshow(greenChannel)
ax[2].imshow(blueChannel)

fig.tight_layout()

plt.show()
