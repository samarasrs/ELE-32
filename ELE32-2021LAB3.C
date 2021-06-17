#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <string> 

using namespace std;
#define TAM 3

vector<int> Int2Bin(int num, int quant_bits){
	vector<int> B;
	while(num > 0)
	{
		B.insert(B.begin(),num % 2);
		num = num / 2;
	}
	
	while(int(B.size()) < quant_bits){
		B.insert(B.begin(),0);
	
	}
	
	return B;
}

int Bin2Int(vector<int> &B){
	int num = 0;
	
	int cont = 0;
	while(not B.empty()){
		if(B.back()){
			num = num + pow(2,cont);
		}
		B.pop_back();
		cont++;
	}
	
	return num;
}

vector<int> CanalBSC(vector<int> entrada, double probErro){
	
	bool acertou;
	vector<int> saida;
	for(int i : entrada){
		int a = (rand() % 100);
		acertou = a < (1 - probErro)*100;
		if(acertou){
			saida.push_back(i);
		}
		else{
			if(i==1){
				saida.push_back(0);
			}
			else{
				saida.push_back(1);
			}
		}
			
	}
	
	
	return saida;
}

vector<int> Codificador(int quant_memoria, vector<vector<int>> &pol, vector<int> &memoria, int bit){
	vector<int> saida;
	int bit_saida;
	for(vector<int> vec : pol){
		bit_saida = bit;
		for(int j = 0; j < int(memoria.size()); j++){
			if(vec[j+1]){
				bit_saida = bit_saida + memoria[j];
			}
		}
		bit_saida = bit_saida % 2;
		saida.push_back(bit_saida);	
	}
	
	memoria.pop_back();
	memoria.insert(memoria.begin(),bit);

	return saida;
}

vector<int> Decodificador(int quant_memoria, vector<vector<int>> &pol, vector<int> &recebida, vector<int> &pesos_acumulados, vector<int> &anterior){
	
	vector<int> atual(pow(2, quant_memoria),-1);
	vector<int> pesos(pow(2, quant_memoria), 0);
	vector<int> codificado;
	vector<int> memoria;
	int custo;
	

	for(int i = 0 ; i < pow(2, quant_memoria); i++){
		if(anterior[i] != -1){
			
			for(int j = 0; j<2; j++){
				codificado.clear();
				memoria.clear();
				memoria = Int2Bin(i, quant_memoria);
				
				
				int idx;
				
				codificado = Codificador(quant_memoria, pol, memoria, j);
		
				custo = 0;
				for (int k = 0; k<int(recebida.size()); k++){
					custo = custo + (recebida[k] + codificado[k])%2;
				} 
				
				idx = Bin2Int(memoria);
				
				if (atual[idx] == -1){
					atual[idx] = i;
					pesos[idx] = pesos_acumulados[i] + custo;
				}
				else if(pesos[idx] > pesos_acumulados[i] + custo){
					atual[idx] = i;
					pesos[idx] = pesos_acumulados[i] + custo;
				}
				else if(pesos[idx] == pesos_acumulados[i] + custo){
					int trocar = 0;
					trocar = rand() % 2;
					if(trocar){
						atual[idx] = i;
						pesos[idx] = pesos_acumulados[i] + custo;
					}
				}
			}
		}
	}
	pesos_acumulados.clear();
	pesos_acumulados = pesos;
	return atual;
}

vector<int> Calcular_estimada(int quant_memoria, vector<int> &pesos_acumulado, vector<vector<int>> &caminhos){

	vector<int> estimada;
	vector<int> vec;
	int idx_min = 0;
	int trocar;

	for(int j = 0; j< pow(2, quant_memoria); j++){
		if(pesos_acumulado[j] < pesos_acumulado[idx_min]){
			idx_min = j;
		}
		else if(pesos_acumulado[j] == pesos_acumulado[idx_min]){	
			trocar = rand() % 2;
			if(trocar){
				idx_min = j;
			}
		
		}
	}
	
	
	while(not caminhos.empty()){
		vec = caminhos.back();
		estimada.insert(estimada.begin(), idx_min);
		idx_min = vec[idx_min];
		caminhos.pop_back();
	}
	

	
	for(int j = 0; j< int(estimada.size()); j++){
		if(estimada[j] >= pow(2,quant_memoria-1)){
			estimada[j] = 1;
		}
		else{
			estimada[j] = 0;
		}
	}
	
	return estimada;
}



int main(){
	int REP = 10000;
	vector<double> PROB_P;
	PROB_P = {0.5,0.2, 0.1, 0.05, 0.02, 0.001, 0.0005, 0.0002, 0.0001, 0.00005, 0.00002, 0.00001, 0.000005, 0.000002,
          0.000001};
	
	
	vector<float> Pb;
	vector<int> transmitida;
	vector<int> enviado;
	vector<int> estimada;
	vector<vector<int>> pol;
	int quant_memoria;
	
	/*
	
	vector<int> memoria(3,0);
	quant_memoria = 3;
	printf("\nquant_memoria = 3\n");
	pol = {{1, 0, 1, 1}, {1, 1, 0, 1}, {1, 1, 1, 1}};
	
	
	vector<int> memoria(4,0);
	quant_memoria = 4;
	printf("\nquant_memoria = 4\n");
	pol = {{1, 0, 1, 0, 1}, {1, 1, 0, 1, 1}, {1, 1, 1, 1, 1}};
	*/
	
	
	vector<int> memoria(6,0);
	quant_memoria = 6;
	printf("\nquant_memoria = 6\n");
	pol = {{1, 0, 0, 1, 1, 1, 1}, {1, 0, 1, 0, 1, 1, 1}, {1, 1, 0, 1, 1, 0, 1}};
	
	
	
	srand (time(0));
	for(double j : PROB_P){
		printf("%lf\n", j);
		vector<vector<int>> caminhos;
		vector<int> pesos_acumulado(pow(2, quant_memoria), 0);
		float soma_erro;
		vector<int> anterior(pow(2, quant_memoria),-1);
		anterior[0] = 0;
		
		
		for(int i = 0; i < REP; i++){
			int bit = rand() % 2;
			enviado.push_back(bit);
			transmitida = Codificador(quant_memoria, pol,memoria, bit);
			transmitida = CanalBSC(transmitida, j);
			anterior = Decodificador(quant_memoria, pol, transmitida, pesos_acumulado, anterior);
			caminhos.push_back(anterior);
		}
		
		estimada = Calcular_estimada(quant_memoria, pesos_acumulado, caminhos);
		
		soma_erro = 0;
			
		for(int j = 0; j < REP; j++){
			if(estimada[j] != enviado[j]){
				soma_erro++;			
			}
		}
		
		Pb.push_back(soma_erro/REP);
		
		pesos_acumulado.clear();
		anterior.clear();
		estimada.clear();
		enviado.clear();
		caminhos.clear();
		transmitida.clear();
		
	}
	
	
	printf("\nPb\n");
	for(float i : Pb){
		printf("%f, ",i);
	
	}
	printf("\n");
	
	return 0;
}

