from random import choices

#CanalBSC

class CanalBSC:
    def __init__(self, entrada, probErro):
        self.entrada = entrada
        self.saida = []
        self.probErro = probErro

    def transmitir(self):
        acertou = [True, False]
        prob = [1 - self.probErro, self.probErro]
        for i in self.entrada:
            aux = choices(acertou, weights=prob, k=1)
            if aux[0]:
                self.saida.append(i)
            else:
                if i == 1:
                    self.saida.append(0)
                else:
                    self.saida.append(1)
        return self.saida