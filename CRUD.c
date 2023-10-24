#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ANO 1
#define MARCA 2
#define PLACA 3

typedef struct car {
    char ano[1000];
    char marca[1000];
    char placa[1000];
    struct car *left;
    struct car *right;
    struct car *pai;
    int vazio;

} carro;

int compare (const char *placa1, const char *placa2);
carro *insertCarro (carro *raiz, carro *novo, int escolha);
carro *insere_lista (carro *LISTA, carro *novo);
carro *remove_lista(carro *LISTA, const char *placa);
carro *remove_arvore (carro *raiz, const char *placa); 
carro *remove_carro(carro *raiz, const char *placa);
carro *encontrarMenorNo(carro *raiz); 
void editaCarro (carro *LISTA, const char *placa, const char *novaMarca, const char *novoAno);
void liberaArvore(carro *raiz);
void listarCarros(carro *raiz);
void listar_lista (carro *raiz);
carro *inicia (); 
void menu();
carro* copia_pointer (carro *original);
carro *rebalance(carro *raiz);
carro *rotacaoDireita(carro *raiz);
carro *rotacaoEsquerda(carro *raiz);
int fatorEquilibrio(carro *raiz);
int altura(carro *raiz);


carro* copia_pointer (carro *original)
{
    carro* novo = NULL;
    
    novo = inicia();
    
    if (novo)
    {
        strcpy(novo->placa, original->placa);
        strcpy(novo->marca, original->marca);
        strcpy(novo->ano, original->ano);
    }
    return novo;
}

// Função de comparação para ordenar 
int compare (const char *str1, const char *str2) 
{
    int ex;
    ex = strcmp (str1, str2);
    
    return ex;
}

carro *insere_lista(carro *LISTA, carro *novo) 
{
    if (LISTA->ano[0] == '\0')
        LISTA->vazio = 1;
 
    if (LISTA->vazio) 
        return novo;

    carro *atual = LISTA;
    carro *atual_novo;
    atual_novo = copia_pointer (novo);
    carro *anterior = NULL;

    while (atual != NULL && compare(atual_novo->placa, atual->placa) >= 0) 
    {
        if (compare(atual_novo->placa, atual->placa) == 0 && 
        compare(atual_novo->marca, atual->marca) == 0 && compare(atual_novo->ano, atual->ano) == 0 )
        {
            printf("\n<---Elemento ja existente!--->\n");
            return LISTA; // Retorna a raiz sem mudança pois o elemento ja existe
        }
        
        anterior = atual;
        atual = atual->right;
    }

    if (anterior == NULL) 
    {
        atual_novo->right = atual;
        return atual_novo;  // Retorna o novo elemento como a nova raiz
    } 

    else 
    {     
        anterior->right = atual_novo;
        atual_novo->right = atual;
        
        return LISTA;  // Retorna a raiz original com o novo elemento inserido
    }
}

carro *insertCarro (carro *raiz, carro *novo, int escolha) 
{
    carro *atual = NULL;
    atual = copia_pointer (novo);

    if (raiz == NULL)
        return atual;

    if (raiz->left == NULL && raiz->right == NULL && raiz->pai == NULL && raiz->ano[0] == '\0')
        raiz->vazio = 1;

    if (raiz->vazio == 1)
    {
        raiz = atual;
        raiz->vazio = 0;
        return raiz;
    }

    int compResult = 0;

    switch (escolha)
    {
        case ANO:
            compResult = compare(atual->ano, raiz->ano);
            break;
        
        case MARCA:
            compResult = compare(atual->marca, raiz->marca);
            break;
        
        case PLACA:
            compResult = compare(atual->placa, raiz->placa);
            break;

        default:

            break;
    }
    
    if (compResult == 0)
    {
     
        int nova_esc = (escolha % 3) + 1;
        int second_comp = 0;

        switch (nova_esc)
        {
            case ANO:
                second_comp = compare (atual->ano, raiz->ano);
                break;
         
            case MARCA:
                second_comp = compare (atual->marca, raiz->marca);
                break;
         
            case PLACA:
                second_comp = compare (atual->placa, raiz->placa);
                break;
            
            default:
                break;
        }

        if (second_comp == 0) 
        {
            nova_esc = (nova_esc % 3) + 1;
            
            switch (nova_esc)
            {
                case ANO:
                    second_comp = compare (atual->ano, raiz->ano);
                    break;
            
                case MARCA:
                    second_comp = compare (atual->marca, raiz->marca);
                    break;
            
                case PLACA:
                    second_comp = compare (atual->placa, raiz->placa);
                    break;
                
                default:
                    break;
            }

            compResult = second_comp;
        } 
        
        else 
        {
            compResult = second_comp;
        }
    }
 
    if (compResult < 0) 
    {
        atual->pai = raiz;
        raiz->left = insertCarro (raiz->left, atual, escolha);
    } 

    else if (compResult > 0) 
    {
        atual->pai = raiz;
        raiz->right = insertCarro (raiz->right, atual, escolha);
    }

    free(atual);
    return raiz;
}

// Função para remover um carro da lista
carro *remove_lista (carro *LISTA, const char *placa) 
{
    carro *atual = LISTA;
    carro *anterior = NULL;

    while (atual != NULL && compare(placa, atual->placa) != 0) 
    {
        anterior = atual;
        atual = atual->right;
    }

    if (atual == NULL)
        return LISTA;

    if (anterior != NULL) 
        anterior->right = atual->right;
    
    else 
        LISTA = atual->right;
    
    free(atual);
    return LISTA;
}

// Função para editar um carro na lista
void editaCarro (carro *LISTA, const char *placa, const char *novaMarca, const char *novoAno) 
{
    carro *atual = LISTA;

    while (atual != NULL && compare(placa, atual->placa) != 0) 
    {
        atual = atual->right;
    }

    if (atual != NULL) 
    {
        strcpy(atual->marca, novaMarca);
        strcpy(atual->ano, novoAno);
    }
}

// Função para liberar a árvore
void liberaArvore(carro *raiz) 
{
    if (raiz == NULL) 
    {
        return;
    }

    liberaArvore(raiz->left);
    liberaArvore(raiz->right);

    free(raiz);
}

// Função para listar carros em ordem na árvore
void listarCarros (carro *raiz) 
{
    if (raiz != NULL) 
    {
        listarCarros(raiz->left);
        
        printf("\nPlaca: %s, Marca: %s, Ano: %s\n", raiz->placa, raiz->marca, raiz->ano);
        printf("\n            |\n");
    
        listarCarros(raiz->right);
    }

    printf("\n");
}

void listar_lista (carro *raiz) 
{
    carro *atual;
    atual = raiz;

    while (atual != NULL) 
    {
        printf("Placa: %s, Marca: %s, Ano: %s", atual->placa, atual->marca, atual->ano);
        printf("  --->  ");
        atual = atual->right;
    }
    
    printf("\n");
}

carro *inicia () 
{
    carro *novaRaiz = (carro *)malloc(sizeof(carro));
    
    if (novaRaiz != NULL) 
    {
        novaRaiz->ano[0] = '\0';  
        novaRaiz->marca[0] = '\0';  
        novaRaiz->placa[0] = '\0';  
        novaRaiz->left = NULL;
        novaRaiz->right = NULL;
        novaRaiz->pai = NULL;
        novaRaiz->vazio = 0;
    }
    
    return novaRaiz;
}
