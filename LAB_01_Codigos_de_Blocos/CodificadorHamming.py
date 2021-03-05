TAM_INFO = 4
TAM_P = 3


class CodificadorHamming:
    def __init__(self, info):
        self.info = info
        self.p = []
        self.codigo = []

    def cod(self):
        for i in range(TAM_P):
            soma = 0
            for j in range(TAM_P):
                soma = soma + self.info[(i + j) % TAM_INFO]
            self.p.append(soma % 2)
        self.codigo = self.info + self.p

    def codigo(self):
        return self.codigo

    def info(self):
        return self.info