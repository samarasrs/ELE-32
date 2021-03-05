import numpy as np

TAM_COD = 7
H = np.array([[1, 0, 1], [1, 1, 0], [1, 1, 1], [0, 1, 1], [1, 0, 0], [0, 1, 0], [0, 0, 1]])


class DecodificadorHamming:
    def __init__(self, recebida):
        self.recebida = np.array(recebida)
        self.estimada = []
        self.erro = []

    def calcular_erro(self):
        s = self.recebida.dot(H)
        if len(s) == 1:
            e = np.zeros((TAM_COD,), dtype=int)
        else:
            e = []
            for i in range(TAM_COD):
                if np.array_equal(H[i],s):
                    e.append(1)
                else:
                    e.append(0)

    def get_erro(self):
        return self.erro

    def corrigir_erro(self):
        self.calcular_erro()
        e = self.get_erro()
        for i in range(TAM_COD):
            self.estimada.append((e[i]+self.recebida) % 2)

    def get_estimada(self):
        return self.estimada
