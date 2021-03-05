import numpy as np

TAM_COD = 7
H = np.array([[1, 0, 1], [1, 1, 0], [1, 1, 1], [0, 1, 1], [1, 0, 0], [0, 1, 0], [0, 0, 1]])


class DecodificadorHamming:
    def __init__(self, recebida):
        self.recebida = recebida
        self.estimada = []
        self.erro = []

    def calcular_erro(self):
        s = np.dot(np.array(self.recebida), H)
        for i in range(len(s)):
            s[i] = s[i] % 2

        if np.array_equal(np.array([0,0,0]),s):
            return np.zeros((TAM_COD,), dtype=int)
        else:
            e = []

            for i in range(TAM_COD):
                if np.array_equal(H[i],s):

                    e.append(1)
                else:
                    e.append(0)

            return e


    def get_erro(self):
        return self.erro

    def calcular_estimada(self):
        e = self.calcular_erro()
        for i in range(TAM_COD):
            self.estimada.append((e[i]+self.recebida[i]) % 2)
        return self.estimada

    def get_estimada(self):
        return self.estimada
