//1. Cálculo de média:
//Escreva um programa que receba três notas de um aluno e calcule sua média. Informe se ele foi
//aprovado (média >= 7), está em recuperação (média entre 5 e 6.9), ou foi reprovado (média < 5).

#include <stdio.h>

int main()
{
   float nota1, nota2, nota3, media;
    
    scanf("%f", &nota1);
    scanf("%f", &nota2);
    scanf("%f", &nota3);
     
    media = (nota1 + nota2 + nota3) / 3.0; 
    
    if (media >= 7.0){
        printf("Aprovado com média: %.1f", media);
    } else if (media >= 5.0 && media <= 6.9){
        printf("Recuperaçao com média: %.1f", media);
    }else{
        printf("Reprovado com média: %.1f", media);
    }

    return 0;
}
