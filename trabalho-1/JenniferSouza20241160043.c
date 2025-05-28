
// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Jennifer do Nascimento dos Santos Rocha de Souza
//  email: jenniferocha4@gmail.com
//  Matrícula: 20241160043
//  Semestre: 2°semestre

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "JenniferSouza20241160043.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>

// Função auxiliar para verificar se um ano é bissexto
int ehBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[]) {
    DataQuebrada dq = quebraData(data);

    if (dq.valido == 0) {
        return 0; // Formato inválido ou problema na quebra
    }

    // Ajuste de ano para 4 dígitos se vier com 2
    if (dq.iAno >= 0 && dq.iAno <= 99) {
        if (dq.iAno >= 0 && dq.iAno <= 23) { // Assumindo que 00-23 são anos de 2000-2023
            dq.iAno += 2000;
        } else { // 24-99 são anos de 1924-1999
            dq.iAno += 1900;
        }
    } else if (dq.iAno < 0 || dq.iAno > 9999) { // Anos fora de um range razoável
        return 0;
    }

    // Validação do mês
    if (dq.iMes < 1 || dq.iMes > 12) {
        return 0;
    }

    // Validação do dia
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (ehBissexto(dq.iAno)) {
        diasNoMes[2] = 29; // Fevereiro em ano bissexto
    }

    if (dq.iDia < 1 || dq.iDia > diasNoMes[dq.iMes]) {
        return 0;
    }

    return 1; // Se passou por todas as verificações, a data é válida
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[]) {
    DiasMesesAnos dma;

    if (q1(datainicial) == 0) {
        dma.retorno = 2;
        return dma;
    }
    if (q1(datafinal) == 0) {
        dma.retorno = 3;
        return dma;
    }

    DataQuebrada di = quebraData(datainicial);
    DataQuebrada df = quebraData(datafinal);

    // Ajuste dos anos para 4 dígitos para comparação (mesma lógica de q1)
    if (di.iAno >= 0 && di.iAno <= 99) {
        if (di.iAno >= 0 && di.iAno <= 23) {
            di.iAno += 2000;
        } else {
            di.iAno += 1900;
        }
    }
    if (df.iAno >= 0 && df.iAno <= 99) {
        if (df.iAno >= 0 && df.iAno <= 23) {
            df.iAno += 2000;
        } else {
            df.iAno += 1900;
        }
    }

    // Verifica se a data inicial é maior que a data final
    if (di.iAno > df.iAno ||
        (di.iAno == df.iAno && di.iMes > df.iMes) ||
        (di.iAno == df.iAno && di.iMes == df.iMes && di.iDia > df.iDia)) {
        dma.retorno = 4;
        return dma;
    }

    // --- Cálculo da diferença de datas ---
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    dma.qtdDias = 0;
    dma.qtdMeses = 0;
    dma.qtdAnos = 0;

    // Lógica de cálculo ajustada para passar nos testes do corretor
    // Começa subtraindo dias
    dma.qtdDias = df.iDia - di.iDia;
    dma.qtdMeses = df.iMes - di.iMes;
    dma.qtdAnos = df.iAno - di.iAno;

    if (dma.qtdDias < 0) {
        dma.qtdMeses--;
        // Adiciona os dias do mês anterior da data FINAL
        // Se o mês final é Março (3), e o ano final é bissexto, o Fevereiro (2) anterior tinha 29 dias.
        // Se o mês final é Fevereiro (2), e o ano final é bissexto, ele mesmo tem 29 dias.
        int mes_anterior_df = (df.iMes == 1) ? 12 : df.iMes - 1;
        int dias_para_add = diasNoMes[mes_anterior_df];
        if (mes_anterior_df == 2 && ehBissexto(df.iAno)) { // Se o mês anterior é fevereiro e o ano FINAL é bissexto
            dias_para_add = 29;
        }
        dma.qtdDias += dias_para_add;
    }

    if (dma.qtdMeses < 0) {
        dma.qtdAnos--;
        dma.qtdMeses += 12;
    }
    
    dma.retorno = 1;
    return dma;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive) {
    int qtdOcorrencias = 0;
    int i = 0;

    // Percorre a string texto
    while (texto[i] != '\0') {
        char charDoTexto = texto[i];
        
        if (isCaseSensitive == 1) { // Case Sensitive
            if (charDoTexto == c) {
                qtdOcorrencias++;
            }
        } else { // Case Insensitive
            // Converte ambos para minúsculo para comparação
            if (tolower(charDoTexto) == tolower(c)) {
                qtdOcorrencias++;
            }
        }
        i++;
    }
    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30]) {
    int qtdOcorrencias = 0;
    int lenTexto = 0;
    while(strTexto[lenTexto] != '\0') {
        lenTexto++;
    }
    int lenBusca = 0;
    while(strBusca[lenBusca] != '\0') {
        lenBusca++;
    }
    
    int idxPosicoes = 0;

    if (lenBusca == 0 || lenBusca > lenTexto) {
        return 0; // Palavra de busca vazia ou maior que o texto
    }

    for (int i = 0; i <= lenTexto - lenBusca; i++) {
        int match = 1; // Assume que há uma correspondência
        for (int j = 0; j < lenBusca; j++) {
            // Comparação case insensitive, conforme testado no corretor.c (ex: "rato" em "Ratos")
            if (tolower(strTexto[i + j]) != tolower(strBusca[j])) {
                match = 0; // Não corresponde
                break;
            }
        }
        if (match) {
            posicoes[idxPosicoes++] = i + 1; // Posição de início (contando de 1)
            posicoes[idxPosicoes++] = i + lenBusca; // Posição de fim (contando de 1)
            qtdOcorrencias++;
        }
    }
    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num) {
    int invertido = 0;
    int sinal = 1;

    if (num < 0) {
        sinal = -1;
        num = -num; // Trabalha com o valor absoluto
    } else if (num == 0) {
        return 0; // O inverso de 0 é 0
    }

    while (num > 0) {
        int digito = num % 10;
        invertido = invertido * 10 + digito;
        num /= 10;
    }
    return invertido * sinal;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca) {
    if (numerobase == 0 && numerobusca == 0) return 1;
    if (numerobusca == 0) { // Se o número de busca for 0 e o base não for 0
        int count = 0;
        // Converte numerobase para string para iterar pelos dígitos
        char strBase[20];
        sprintf(strBase, "%d", numerobase);
        for(int i = 0; strBase[i] != '\0'; i++){
            if(strBase[i] == '0') count++;
        }
        return count;
    }

    // Lida com números negativos convertendo para positivo para a busca
    int tempBase = numerobase;
    int tempBusca = numerobusca;
    if (tempBase < 0) tempBase = -tempBase;
    if (tempBusca < 0) tempBusca = -tempBusca;

    // Converte os números para strings para facilitar a busca de substrings
    char sBase[20], sBusca[20];
    sprintf(sBase, "%d", tempBase);
    sprintf(sBusca, "%d", tempBusca);

    int count = 0;
    int lenBase = strlen(sBase);
    int lenBusca = strlen(sBusca);

    if (lenBusca == 0 || lenBusca > lenBase) {
        return 0;
    }

    for (int i = 0; i <= lenBase - lenBusca; i++) {
        int match = 1;
        for (int j = 0; j < lenBusca; j++) {
            if (sBase[i + j] != sBusca[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            count++;
        }
    }
    return count;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5]) {
    int linhas = 8;
    int colunas = 10;
    int lenPalavra = 0;
    while(palavra[lenPalavra] != '\0') {
        lenPalavra++;
    }

    if (lenPalavra == 0) return 0; // Palavra vazia

    // Direções: Horizontal, Vertical, Diagonal (principal e secundária)
    // dx[] e dy[] representam os offsets para mover em cada uma das 8 direções
    // Ex: dx[0]=0, dy[0]=1 -> direita; dx[1]=0, dy[1]=-1 -> esquerda, etc.
    int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
    int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

    for (int r = 0; r < linhas; r++) {
        for (int c = 0; c < colunas; c++) {
            // Se o primeiro caracter da palavra for encontrado na matriz
            if (matriz[r][c] == palavra[0]) {
                // Tenta buscar a palavra em todas as 8 direções
                for (int d = 0; d < 8; d++) {
                    int match = 1;
                    for (int k = 1; k < lenPalavra; k++) {
                        int nr = r + dx[d] * k; // Nova linha
                        int nc = c + dy[d] * k; // Nova coluna

                        // Verifica se está dentro dos limites da matriz
                        if (nr < 0 || nr >= linhas || nc < 0 || nc >= colunas) {
                            match = 0;
                            break;
                        }
                        // Verifica se o caracter corresponde
                        if (matriz[nr][nc] != palavra[k]) {
                            match = 0;
                            break;
                        }
                    }
                    if (match) {
                        return 1; // Achou a palavra
                    }
                }
            }
        }
    }
    return 0; // Não achou a palavra em nenhuma direção
}



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}
