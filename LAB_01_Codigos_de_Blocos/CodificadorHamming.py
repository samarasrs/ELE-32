TAM_INFO = 4
TAM_P = 3


class CodificadorHamming:
    def __init__(self, info):
        self.info = info
        self.p = []
        self.codigo = []

    def cod(self):
        #para calcular os valores de p1 utilizou-se b1, b2, b3
        # p2 utilizou-se b2, b3, b4 e para p3 utilizou-se b3, b4 e b1

        for i in range(TAM_P):
            soma = 0
            for j in range(TAM_P):
                soma = soma + self.info[(i + j) % TAM_INFO]
            self.p.append(soma % 2)
        self.codigo = self.info + self.p
        return self.codigo

    def get_codigo(self):
        return self.codigo

    def get_info(self):
        return self.info

