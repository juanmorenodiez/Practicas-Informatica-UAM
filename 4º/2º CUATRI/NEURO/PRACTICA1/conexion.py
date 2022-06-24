class Conexion:
    def __init__(self, peso, neurona):
        self.peso = peso
        self.neurona = neurona
        self.peso_anterior = 0.0
        self.valor = 0.0
        
    def liberar(self):
        pass

    def propagar(self, valor):
        self.valor = valor 
        
