from CodificadorHamming import CodificadorHamming
from DecodificadorHamming import DecodificadorHamming
from canalBSC import CanalBSC
from random import getrandbits
import numpy as np
import matplotlib.pyplot as plt

PROB_P = [0.5, 0.2, 0.1, 0.05, 0.02, 0.001, 0.0005, 0.0002, 0.0001, 0.00005, 0.00002, 0.00001, 0.000005, 0.000002,
          0.000001]

REPETICAO = 250000
TAM_INFO = 4

if __name__ == '__main__':
    Pb = []
    for k in PROB_P:
        print(k)
        soma_erro = 0
        for i in range(REPETICAO):
            info = []
            for j in range(TAM_INFO):
                info.append(getrandbits(1))


            tramistida = CodificadorHamming(info).cod()

            recebida = CanalBSC(tramistida, k).transmitir()

            estimada = DecodificadorHamming(recebida).calcular_estimada()


            for i in range(TAM_INFO):
                if estimada[i] != tramistida[i]:
                    soma_erro = soma_erro + 1

            '''
            if not np.array_equal(np.array(tramistida), np.array(estimada)):
                soma_erro = soma_erro + 1
            '''

        Pb.append(soma_erro/(REPETICAO*4))
