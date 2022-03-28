#include "SGAHeader.h"
/* 
Sistema Gerenciador de Arquivos

Resumidamente, a ideia deste programa foi criar uma simulação de memória computacional, como um disco rígido, por exemplo,
onde arquivos são gravados e removidos o tempo todo. Para esse projeto, foram utilizados 2 estruturas principais de dados:
posição de parte e posição de histórico. São então criados vetores dessas posições, sendo assim, a ideia é que o vetor de historico
salve as primeiras coordenadas da primeira posição do arquivo no vetor de partes (como um índice de um livro), e o vetor de partes armazena
o conteúdo do arquivo (estritamente arquivos de texto) em suas posições. 

Este programa foi feito para fins acadêmicos, portanto, para facilitar uso
e diminuir falhas, os parâmetros do programa são:
    O vetor de histórico guarda um total de 10 arquivos
    O vetor de partes contém 150 posições sendo que cada posição armazena uma conjunto de 30 caracteres lidos do arquivo.

Como o objetivo deste projeto é representar o método, sua utilização e mecanismos, tamanhos exorbitantes de memória serão de pouca utilidade.

Este programa conta com descrição em cada seção do código para melhor entendimento
*/


/*Função para zerar os vetores de histórico e de partes deste arquivo.
Foi optado por definir como posição vazia no vetor de histórico, o indice ser igual a -1 
e no vetor de partes sua variável index também -1 e sua variavel prox igual a -3 
OBS: O status de histórico é definido como 1, que está ativo, porém para que a posição do histórico seja um arquivo válido,
seu índice é também considerado, que no caso for igual a -1 significa que o arquivo não existe.
*/
void zera(Histo * historico, Parte * vet){
    //zera o vetor de historico
    for(int i=0; i<10; i++){
        historico[i].indice=-1;
        historico[i].status=1;
    }
    //zera o vetor de partes
    for(int i=0;i<150;i++){
        vet[i].index=-1;
        vet[i].prox=-3;
    }
    
}

/* Função de inserção de arquivo no vetor memória e vetor histórico
Dada já uma posição no vetor de histórico, a função percorre o vetor de partes para encontrar uma posição vazia (cujo index = -1)
quando encontra o primeiro, salva sua localização no vetor historico, e então começa a leitura do arquivo para a posição.
É sempre salva a posição posterior daquela posição no inteiro "prox" do vetor de partes.
Quando a leitura é um sucesso, ou seja, o arquivo coube na memória sem problema, sua ultima posição é definida como -2 para indicar fim do arquivo.
Se o arquivo excede a memória, ele é removido do sistema, e uma mensagem de aviso é mostrada.
*/
void insere(Histo * historico, Parte * vet, char * noArquivo, int posHist, FILE * arq){
    int svAnt=-1;
    int svIndex;
    int flag=-1;
    char aux;
    historico[posHist].status=1;

    for(int i=0; i<=150; i++){
        
        //Indica fim do arquivo(EOF), então sai do 'for'
        if(flag==1)
            break;

        if(i==150){
            vet[i-1].prox=-2;
            printf("Arquivo excede o tamanho da memória, por favor apague alguns arquivos e tente novamente\n");
            remocao(historico,vet,noArquivo, posHist+1);
            return;
        }
        //index ser -1 indica célula vazia
        if(vet[i].index==-1){
            //copia o nome do arquivo pra célula vazia
            strcpy(vet[i].nomeAr,noArquivo);

            //svAnt ser -1 indica que esta é a primeira parte a ser salva; salva o indice do começo e o anterior. salva também no vetor de historico
            if(svAnt==-1){
                svIndex=i;
                svAnt=i;
                historico[posHist].indice=i;
                strcpy(historico[posHist].nomeAr, noArquivo);
                

            }
            else{
                //salva o proximo índice na posição anterior;
                vet[svAnt].prox=i;
                svAnt=i;
            }
            //salva a primeira pos em todas as celulas de parte daquele arquivo;
            vet[i].index=svIndex;

            for(int j=0;j<30;j++){
                aux = fgetc(arq);
                
                //se o caracter pego pelo fgetc for EOF, salva o indice prox como -2 pra indicar fim,
                //sinaliza a flag pra saida do outro for, e break;
                if(aux==EOF){
                    vet[i].prox=-2;
                    flag=1;
                    break;
                }
                
                //se não, salva o caractere na string da célula, na posição j.
                else
                    vet[i].txt[j]=aux;     
            }   
        }
    }
    printf("Arquivo inserido com sucesso!\n\n");

}
/* Função de busca de determinado arquivo. Busca primeiro no vetor de histórico se o arquivo está ativo na memória do vetor de partes, 
se foi excluído ou não existe. Se existe, é pego o índice dele no vetor de histórico que aponta diretamente para a primeira posição do arquivo 
no vetor de partes, então é declarado um "total" que é incrementado à medida que uma posição do arquivo é impressa na tela, até chegar em -2 que indica 
a string que conteve o EOF (fim de arquivo);
*/
void busca(Histo * historico, Parte * vet, char * noArquivo, int histCount){
    int a, b, pos;
    pos=verif(historico, histCount, noArquivo, 0);
    
    if(pos==histCount){
        printf("Arquivo nao encontrado.\n");
        return;
    }

    if(historico[pos].status==-1){
            printf("Arquivo ja foi removido!\n");
            return;
    }else{
        a=historico[pos].indice;
    }
        
    
    int total=0;
    printf("Posicoes alocadas para %s:\n", noArquivo);
    while(a!=-2){
        printf("%d ", a);
        b=vet[a].prox;
        a=b;
        total++;
    }
    printf("\n");
    printf("Total de blocos = %d\n", total);
    return;
}

/*Cria função de remoção de arquivo: Percorre o vetor de histórico para verificar se o arquivo ainda se encontra na memoria, foi excluído, ou não existe.
Se existe, então é pego o índice salvo em sua posição de histórico que aponta diretamente para a primeira posição do arquivo no vetor de partes, 
daí então passa atribuir o índice do vetor de partes como -1 que indica livre para gravação. Muda-se o estado de "status" no vetor de historico para -1 
que indica que o arquivo foi excluído.
*/
void remocao(Histo * historico, Parte * vet, char * noArquivo, int histCount){
    int a, b, pos;
    pos=verif(historico, histCount, noArquivo, 0);
    
    if(pos==histCount){
        printf("Arquivo nao encontrado.\n");
        return;
    }
        
    if(historico[pos].status==-1){
        printf("Arquivo ja foi removido!\n");
        return;

    }else{
        a=historico[pos].indice;
        historico[pos].status=-1;
    }

    while(a!=-2){
        b=vet[a].prox;
        vet[a].index=-1;
        a=b;
    }
    printf("Arquivo removido com sucesso!\n");
            return;
}

/*Função que verifica a posição de um arquivo no vetor de histórico, se não existir, retorna uma nova posição. O inteiro "cond" indica se
a função deve retornar uma nova posição no histórico, ou se deve indicar que o arquivo já está inserido no sistema.
*/
int verif(Histo * historico, int histCount, char * noArquivo, int cond){
    for(int i=0; i<histCount; i++){
        if(strcmp(noArquivo, historico[i].nomeAr)==0){
            if(cond && historico[i].status==1){
                printf("O arquivo ja esta inserido no sistema!\n\n");
                return -2;
            }
            return i;
        }
    }
    return histCount;
}

/* Função que verifica um slot especifico da memória do vetor de partes (posição) e mostra alguns dados ao usuário sobre ela e seu arquivo
*/
void slot(Histo * historico, int histCount, int posVet, Parte * vet){
    
    if(vet[posVet].index == -1 && vet[posVet].prox==-3){
        printf("Este slot de memoria esta vazio e nunca foi usado por nenhum arquivo\n");
        return;
    }

    if(vet[posVet].index==-1 && vet[posVet].prox!=-3){
        printf("Este slot de memoria esta vazio mas foi utilizado pelo arquivo %s em sua ultima gravacao\n", vet[posVet].nomeAr);
    
    }else{

        printf("Este slot de memoria esta sendo usado no momento pelo arquivo %s\n", vet[posVet].nomeAr);
    }

    for(int i=0; i<histCount; i++){

        if(strcmp(vet[posVet].nomeAr, historico[i].nomeAr)==0){
            printf("O arquivo %s foi o %dº a ser inserido no sistema\n\n", vet[posVet].nomeAr, i+1);
            return;
        }
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese_Brasil");
    printf("\n");
    printf("=======================================================\n");
    printf("Seja bem-vindo ao SGA (Sistema Gerenciador de arquivos\n");
    printf("=======================================================\n");
    printf("\nO SGA opera da seguinte forma: dado um arquivo inserido pelo usuario,\n");
    printf("o sistema ira fazer a leitura deste arquivo e armazena-lo em um vetor de partes\n");
    printf("como simulacao do funcionamento de um disco rigido ou outro tipo de memoria.\n");
    printf("\n");

    //Cria-se um ponteiro pra arquivo
    FILE* arq;

    //Um vetor de historico de arquivos que passaram pelo programa;
    Histo historico[10];

    //Um vetor de partes onde os arquivos serão gravados
    Parte vet[150];

    //Contagem de arquivos do histórico;
    int histCount=0;

    //Zera os vetores de histórico e memória;
    zera(historico,vet);

    char noArquivo[20];// salva o nome do arquivo
    int aux, posHist; //int aux serve para diversos propósitos auxiliares, e posHist salvará a posição no vetor histórico.
    int ans=1;
    /*ans é a variavel que armazena a resposta do usuário quanto a: insercao(1), deleção(2), busca(3), 
    verifica slot da memoria (4)e saida(ans<=0 ou ans>=5)
    */
    while(ans>0 && ans<5){

        printf("\nO que deseja fazer?\nInserir arquivo(1)\nRemover arquivo(2)\nBuscar arquivo(3)\nVerificar slot da memoria (4)\nSair (5)\n");
        scanf("%d", &ans);
        printf("\n");

        if(ans==1){
            if(histCount==10){
                printf("O limite de gravacoes foi excedido, execute outra opcao\n");
                continue;
            }
            printf("Qual o nome do arquivo?(ate 20 caracteres)\n");
            scanf("%s", &noArquivo);
            arq = fopen(noArquivo,"rt");
            if(arq == NULL){
                printf( "Erro na abertura do arquivo\n");
                continue;
            }else{
                aux=histCount;
                posHist=verif(historico,histCount,noArquivo, 1);
                if(posHist==-2)
                    continue;
                if(aux==posHist)
                    histCount++;

                insere(historico,vet,noArquivo,posHist,arq);
            }

        }
        else if(ans==2){
            printf("Nome do arquivo a ser deletado (com extensao):\n");
            scanf("%s", &noArquivo);
            
            remocao(historico,vet,noArquivo,histCount);
            
        }
        else if(ans==3){
            printf("Qual o nome do arquivo?(ate 20 caracteres)\n");
            scanf("%s", &noArquivo);
            busca(historico,vet,noArquivo,histCount);
            
        }
        else if(ans==4){
            printf("Qual slot de memoria deseja verificar? (1-150)\n");
            scanf("%d", &aux);
            slot(historico, histCount, aux, vet);


        }
    }


    return 0;

}