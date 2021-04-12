import numpy as np

#Codificador

class Codificador:
    def __init__(self, info, G):
        self.G = G
        self.info = info
        self.codigo = []

    def cod(self):
        self.codigo = np.dot(np.array(self.info), self.G)
        for i in range(len(self.codigo)):
            self.codigo[i] = self.codigo[i] % 2
        return self.codigo

    def get_codigo(self):
        return self.codigo

    def get_info(self):
        return self.info