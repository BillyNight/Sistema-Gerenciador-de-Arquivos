#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

/**
 *  \brief Estrutura de uma parte da memória interna do programa 
 */
typedef struct parte{
    int prox; ///< É a proxima posição da memória daquele arquivo, se -2 então é a ultima parte.
    char txt[30]; ///< É a parte do texto salva naquela posição de memória.
    char nomeAr[20]; ///< É o nome do arquivo na qual aquela parte pertence.
    int index; ///< É a posição inicial do arquivo daquela parte.
} Parte;

/** 
 * \brief Estrutura de uma posição de histórico de inserção e deleção de arquivos.
 */
typedef struct histo{
    int indice; ///< Indica a primeira posição num vetor de partes daquele arquivo.
    char nomeAr[20]; ///< É o nome do arquivo salvo naquela posição de histórico.
    int status; ///< Indica o estado atual do arquivo, se ainda está gravado ou foi removido.
} Histo;


/**
 * \brief Zera o vetor de histórico e o vetor de partes
*/
void zera(Histo * historico, Parte * vet){
/**
    \param historico: Ponteiro para o vetor de histórico de arquivos.
    \param vet: Ponteiro para o vetor de partes dos arquivos.
    \return Retorna os vetores zerados.
*/
}

/**
 * \brief Verifica a posição de um arquivo no vetor histórico.
 * Se a condição for 1, indicará ao sistema que se está tentando inserir um arquivo, então verificará
 * se o arquivo já está inserido. Se for 0, retorna a posição do arquivo no vetor histórico. 
 */
int verif(Histo * historico, int histCount, char * noArquivo, int cond){
    /**
     * \param historico: Ponteiro para o vetor de histórico de arquivos.
     * \param histCount: Contagem de arquivos no vetor de histórico.
     * \param noArquivo: Ponteiro para a string de nome do arquivo.
     * \param cond: Muda a condição de retorno da função.
     */
}

/**
 * \brief Insere um novo arquivo na memória do script.
 * É feita uma checagem no vetor de histórico se o arquivo já foi inserido uma vez, se já
 * suas coordenadas da primeira posição do arquivo no vetor de partes, é salva no mesmo lugar, no vetor de histórico.
 * Se isso não ocorre, uma nova posição no vetor de histórico é designada. Após essa etapa, são verificadas posições vazias no vetor
 * de partes para alocação do arquivo, se o tamanho do arquivo for maior que a memória livre, o arquivo não é salvo.
 */
void insere(Histo * historico, Parte * vet, char * noArquivo, int posHist, FILE * arq){
    /**
     * \param historico: Ponteiro para o vetor de histórico de arquivos.
     * \param vet: Ponteiro para o vetor de partes dos arquivos.
     * \param noArquivo: Ponteiro para a string de nome do arquivo.
     * \param posHist: A posição daquele arquivo no vetor de histórico.
     * \param arq: Ponteiro para o arquivo de onde serão lidas e salvas as partes de string;
     */
}

/** \brief Busca um arquivo na memória pelo seu nome.
 * Percorre o vetor de histórico tentando encontrar o arquivo com o nome especificado,
 * se encontrado, é verificado se ainda se encontra ativo, ou já foi excluido, se ainda ativo,
 * descreve-se os blocos de memória utilizados pelo arquivo e o total deles.
 */
void busca(Histo * historico, Parte * vet, char * noArquivo, int histCount){
    /**
     * \param historico: Ponteiro para o vetor de histórico de arquivos.
     * \param vet: Ponteiro para o vetor de partes dos arquivos.
     * \param noArquivo: Ponteiro para a string de nome do arquivo.
     * \param histCount: Contagem de arquivos no vetor de histórico.
     */
}

/** \brief Remove um arquivo do vetor de partes.
 * Primeiro é verificado se o arquivo existe e ainda não foi excluído, passando essa
 * verificação, o programa começa pelo índice do arquivo, tornando os indices imediatamente anteriores
 * como -1 que significa uma posição livre para ser usada, também é alterado o status desse arquivo 
 * no vetor de histórico para -1 que significa arquivo excluído.
 */
void remocao(Histo * historico, Parte * vet, char * noArquivo, int histCount){
    /**
     * \param historico: Ponteiro para o vetor de histórico de arquivos.
     * \param vet: Ponteiro para o vetor de partes dos arquivos.
     * \param noArquivo: Ponteiro para a string de nome do arquivo.
     * \param histCount: Contagem de arquivos no vetor de histórico.
     */
}

/**
 *  \brief Verifica uma posição específica do vetor de partes.
 */
void slot(Histo * historico, int histCount, int posVet, Parte * vet){
    /**
     * \param historico: Ponteiro para o vetor de histórico de arquivos.
     * \param histCount: Contagem de arquivos no vetor de histórico.
     * \param noArquivo: Ponteiro para a string de nome do arquivo.
     */
}
