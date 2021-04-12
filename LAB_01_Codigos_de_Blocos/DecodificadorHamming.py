# Decodificador

class Decodificador:
    def __init__(self, recebida, H):
        self.H = H
        self.recebida = recebida
        self.estimada = []
        self.erro = []

    def calcular_erro(self):
        s = np.dot(np.array(self.recebida), self.H)
        for i in range(len(s)):
            s[i] = s[i] % 2

        if np.array_equal(np.array([0, 0, 0]), s):
            return np.zeros((len(self.recebida),), dtype=int)
        else:
            e = []

            for i in range(len(self.recebida)):
                if np.array_equal(self.H[i], s):

                    e.append(1)
                else:
                    e.append(0)

            return e

    def calcular_estimada(self):
        e = self.calcular_erro()
        r = self.recebida
        for i in range(len(e)):
            self.estimada.append((e[i] + r[i]) % 2)

        return self.estimada