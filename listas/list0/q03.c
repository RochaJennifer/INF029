/******************************************************************************

3. Contador de pares e ímpares:
Leia 10 números inteiros e exiba quantos são pares e quantos são ímpares.

*******************************************************************************/
#include <stdio.h>

int main()
{
    int n, pares = 0, impares = 0;
    
    for(int i = 0; i <10; i++){
        
        printf("\nInforme 10 números inteiros para saber quantos são pares e quantos são impares: ");
        scanf("%d", &n);
        
        if(n % 2 == 0){
            pares++;
        }else{
            impares++;
        }
        
        printf("Pares: %d e impares: %d", pares, impares);
    }
    

    return 0;
}
