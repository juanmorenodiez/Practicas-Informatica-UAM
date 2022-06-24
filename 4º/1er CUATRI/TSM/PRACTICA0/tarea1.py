import numpy as np

# Apartado 1
print("Vector 10x1 aleatorio:")
uno = np.random.random(10)
print(uno)

# Apartado 2
print("\nArray 10x10 de ceros:")

dos = np.zeros((10, 10))
print(dos)

# Apartado 3
print("\nArray 10x10 con bordes de unos:")

tres = dos
ones = np.ones(10)

tres[0] = ones
tres[-1] = ones
tres[:, 0] = ones
tres[:, -1] = ones

print(tres)

# Apartado 4
print("\nArray con indices impares:")

cuatro = np.array(tres[1::2, 1::2], copy=True)
print(cuatro)

# Apartado 5
print("\nArray con indices pares:")

cinco = np.array(tres[::2, ::2], copy=True)
print(cinco)

# Apartado 6
print("\nSegunda fila con valor cambiado a 3:")

seis = np.array(tres, copy=True)
seis[1, 2] = 3
print(seis[1, :])
