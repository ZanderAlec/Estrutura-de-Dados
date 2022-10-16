int main(){

    int vet[10];
    int aux;

    for(int i = 0 ; i < 10; i++ ){
         printf("Digite um numero: ");
         scanf("%d", &vet[i]);
    }

    printf("Alinhamento inicial\n");

     for(int i = 0 ; i < 10; i++ ){
         printf("%d ", vet[i]);
    }

    printf("\n");


    //selection sort melhorado:

    /*p/ melhorar o selection sort foram adotadas 2 estratégias:
        1- Além de, a cada looping, colocar o menor valor na primeira posição, colocar também o maior valor na última posição.
            reduzindo o numero de laços.
        2- parar o looping quando ambos os verificadores de posição(i,m) passarem da metade do vetor, pois isso significa que o vetor ja foi completamente ordenado.


    */

    //i começa a partir do primeiro índice e m começa a partir do último
    for(int i = 0, m = 9; i < 10; i++, m--){

        //se m < i então todos os índices já foram comparados.
        if(m < i){
            break;
        }

        int menor = i;
        int maior = m;

        for(int j = i, k = maior; j < 10; j++, k--){

            //guarda o indice do menor valor
            if(vet[menor] > vet[j]){
                menor = j;
            }

            //guarda o indice do maior valor
            if(vet[maior] < vet[k]){
                maior = k;
            }
        }   

        //colocar o maior valor na "última" posição:

        //Verifica se o valor maior está na "primeira" posição(i), se estiver, troca a posição do primeiro com a "ultima" posição(m)
        if(i == maior){
            aux = vet[m];
            vet[m] = vet[i]; 
            vet[i] = aux;

        //Caso não seja, troca o maior normalmente:
        }else{
            aux = vet[maior];
            vet[maior] = vet[m];
            vet[m] = aux;
        }

        //colocar o menor valor na "primeira" posição:
         //Verifica se o valor menor está na "ultima" posição, se estiver, o valor foi trocado de lugar, então
         // troca a posição do primeiro[i] com o antigo maior[vet[maior]]
        if(menor == m){
            aux = vet[maior];
            vet[maior] = vet[i]; 
            vet[i] = aux;

        //Caso não seja, troca o menor normalmente:
        }else{
            aux = vet[menor];
            vet[menor] = vet[i]; 
            vet[i] = aux;  
        }
    }

    printf("Alinhamento final\n");

    for(int i = 0 ; i < 10; i++ ){
         printf("%d ", vet[i]);
    }

    printf("\n");


    return 0;
}