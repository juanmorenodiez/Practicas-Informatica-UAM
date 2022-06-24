class RedNeuronal:
    def __init__(self):
        self.capas = []

    def liberar(self):
        pass

    def inicializar(self):
        for capa in self.capas:
            capa.inicializar()

    def añadir(self, capa):
        self.capas.append(capa)

    def disparar(self):
        for capa in self.capas:
            capa.disparar()

    def propagar(self):
        for capa in self.capas:
            capa.propagar()
                