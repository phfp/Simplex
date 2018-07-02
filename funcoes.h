/* 
 * File:   funcoes.h
 * Author: paulo
 *
 * Created on 11 de Maio de 2015, 17:29
 */

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

#ifndef FUNCOES_H
#define	FUNCOES_H


void Solucao(string nome, int m, int n, char tipo);
void Det_Dimensoes(string nome, int &linhas, int &colunas);
float **Carregar_Matriz (int m, int n);
void Preenche_Mat_Ab(float **mat_A, float *vet_B, float **&mat_Ab, int m, int n);
void Calcular_Custo(float *&vet_C_Aux, float *vet_C, float **mat_A, float *vet_D, int tam_C, int tam_D);
bool Verifica_Otimizacao(float *vet_C_Aux, int tam_C);
int Quem_Entra(float *vet_C_Aux, int tam_C);
int Quem_Sai(float **mat_Ab, float *&vet_D, int entra, int tam_C, int tam_D);
void Pivoteamento(float **&mat_Ab, float *&vet_B, int tam_B, int tam_C, int sai, int entra);
float Calcular_Z(float *vet_B, float *vet_C, float *vet_D, int tam_B);
void Resultados(float *vet_Res, float *vet_D, float *vet_B, float z, int it, int tam_B, int tam_C);
bool Simplex();


#endif	/* FUNCOES_H */

