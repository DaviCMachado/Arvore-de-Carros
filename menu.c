#include "CRUD.c"

void menu ()
{
    carro *LISTA = NULL;
    carro *arvorePlaca =  NULL;
    carro *arvoreMarca =  NULL;
    carro *arvoreAno =  NULL;

    LISTA = inicia ();
    arvorePlaca = inicia ();
    arvoreMarca = inicia ();
    arvoreAno = inicia ();

    while (1) 
    {
        printf("\nEscolha uma opção:\n");
        printf("1. Inserir carro\n");
        printf("2. Deletar carro\n");
        printf("3. Editar carro\n");
        printf("4. Listar carros por placa\n");
        printf("5. Listar carros por marca\n");
        printf("6. Listar carros por ano\n");
        printf("7. Exibir a Lista Principal\n");
        printf("8. Sair\n\n");

        int choice;
        if (scanf("%d", &choice) != 1) 
        {
            // Entrada inválida (não é um número inteiro)
            while (getchar() != '\n'); // Limpar o buffer de entrada
            continue;
        }

        if (choice == 8) 
            break;
        
        switch (choice) 
        {
            case 1: 
            {
                carro *novo = NULL; 
                carro *novo_lista = NULL;

                novo = inicia ();
                novo_lista = inicia ();

                if (novo == NULL) 
                {
                    printf("Erro: Falha na alocação de memória.\n");
                    exit(1); // Ou outra ação apropriada
                }

                printf("\nDigite a placa do carro: ");
                scanf (" %[^\n]", novo->placa);

                printf("\nDigite a marca do carro: ");
                scanf (" %[^\n]", novo->marca);

                printf("\nDigite o ano do carro: ");
                scanf (" %[^\n]", novo->ano);

                char textoAdicional[100];
                
                sprintf(textoAdicional, "%s", novo->placa);

                strcat(novo_lista->placa, textoAdicional);
     
                sprintf(textoAdicional, "%s", novo->marca);

                strcat(novo_lista->marca, textoAdicional);
     
                sprintf(textoAdicional, "%s", novo->ano);

                strcat(novo_lista->ano, textoAdicional);

                LISTA = insere_lista(LISTA, novo_lista);
                arvorePlaca = insertCarro(arvorePlaca, novo, PLACA); 
                arvoreMarca = insertCarro(arvoreMarca, novo, MARCA);   
                arvoreAno = insertCarro(arvoreAno, novo, ANO);

                break;
            }

            case 2: 
            {
                if (!LISTA)
                {
                    printf("\nA Lista de Carros Ja Esta Vazia!\n");
                    break;
                }

                char placa[50];
                printf("\nDigite a placa do carro a ser deletado: ");
                scanf(" %[^\n]", placa);

                LISTA = remove_lista(LISTA, placa);
                arvorePlaca = remove_arvore(arvorePlaca, placa);
                arvoreMarca = remove_arvore(arvoreMarca, placa);
                arvoreAno = remove_arvore(arvoreAno, placa);

                if(!LISTA)
                    LISTA = inicia();

                if (!arvoreAno)
                {
                    arvoreAno = inicia();
                    arvorePlaca = inicia();
                    arvoreMarca = inicia();
                }

                break;
            }

            case 3: 
            {
                char placa[50];
                printf("\nDigite a placa do carro a ser editado: ");
                scanf(" %[^\n]", placa);
                printf("\nDigite a nova marca: ");
                char novaMarca[50];
                scanf(" %[^\n]", novaMarca);
                printf("\nDigite o novo ano: ");
                char novoAno[10];
                scanf(" %[^\n]", novoAno);

                editaCarro(LISTA, placa, novaMarca, novoAno);
                editaCarro(arvorePlaca, placa, novaMarca, novoAno);
                editaCarro(arvoreMarca, placa, novaMarca, novoAno);
                editaCarro(arvoreAno, placa, novaMarca, novoAno);

                break;
            }

            case 4: 
            {
                printf("\nCarros ordenados por placa:\n");
                if (arvorePlaca->placa[0] == '\0')
                {
                    printf("\n<---Arvore Vazia!--->\n");
                    break;
                }

                listarCarros(arvorePlaca);
                break; 
            }

            case 5: 
            {
                printf("\nCarros ordenados por marca:\n");
                if (arvoreMarca->marca[0] == '\0')
                {
                    printf("\n<---Arvore Vazia!--->\n");
                    break;
                }
                
                listarCarros(arvoreMarca);
                break;
            }

            case 6: 
            {
                printf("\nCarros ordenados por ano:\n");
                if (arvoreAno->ano[0] == '\0')
                {
                    printf("\n<---Arvore Vazia!--->\n");
                    break;
                }
                
                listarCarros(arvoreAno);
                break;
            }
          
            case 7: 
            {
                printf("\n<----Lista de carros ordenados por placa---->\n\n");
                
                if (LISTA->ano[0] == '\0')
                {
                    printf("<---Lista Vazia!--->\n");
                    break;
                }
                
                listar_lista(LISTA);
                break;
            }
                            
            default: 
                break;
        }   
    }

    liberaArvore(arvorePlaca);
    liberaArvore(arvoreMarca);
    liberaArvore(arvoreAno);
    
    while (LISTA != NULL) 
    {
        carro *temp = LISTA;
        LISTA = LISTA->right;
        free(temp);
    } 
}



// Função para remover o maior nó à direita
carro *MaiorDireita(carro **no) 
{
    if ((*no)->right != NULL) 
    {
        return MaiorDireita(&(*no)->right);
    } 
    
    else 
    {
        carro *aux = *no;
        if ((*no)->left != NULL) 
        {
            *no = (*no)->left;
        } 
        
        else 
        {
            *no = NULL;
        }
        
        return aux;
    }
}

// Função para remover o menor nó à esquerda
carro *MenorEsquerda(carro **no) 
{
    if ((*no)->left != NULL) 
    {
        return MenorEsquerda(&(*no)->left);
    } 
    
    else 
    {
        carro *aux = *no;
        if ((*no)->right != NULL) 
        {
            *no = (*no)->right;
        } 
        
        else 
        {
            *no = NULL;
        }
        return aux;
    }
}

carro *remove_arvore(carro *raiz, const char *placa) 
{
    if (raiz == NULL) 
    {
        return raiz;
    }

    int compResult = compare(placa, raiz->placa);

    if (compResult < 0) 
    {
        raiz->left = remove_arvore(raiz->left, placa);
    } 
    
    else if (compResult > 0) 
    {
        raiz->right = remove_arvore(raiz->right, placa);
    } 
    
    else 
    {
        if (raiz->left == NULL) 
        {
            carro *temp = raiz->right;
            free(raiz);
            return temp;
        } 
        
        else if (raiz->right == NULL) 
        {
            carro *temp = raiz->left;
            free(raiz);
            return temp;
        }
        
        carro *sucessor = MenorEsquerda(&raiz->right);
        strcpy(raiz->placa, sucessor->placa);
        strcpy(raiz->marca, sucessor->marca);
        strcpy(raiz->ano, sucessor->ano);
        raiz->right = remove_arvore(raiz->right, sucessor->placa);
    }

    return raiz;
}



carro *remove_carro(carro *raiz, const char *placa) 
{
    if (raiz == NULL) 
        return raiz;

    int compResult = compare(placa, raiz->placa);

    if (compResult < 0) 
    {
        raiz->left = remove_carro(raiz->left, placa);
    } 
    
    else if (compResult > 0) 
    {
        raiz->right = remove_carro(raiz->right, placa);
    } 
    
    else 
    {
        if (raiz->left == NULL) 
        {
            carro *temp = raiz->right;
            free(raiz);
            return temp;
        } 
        
        else if (raiz->right == NULL) 
        {
            carro *temp = raiz->left;
            free(raiz);
            return temp;
        }
        
        carro *sucessor = encontrarMenorNo(raiz->right);
        strcpy(raiz->placa, sucessor->placa);
        raiz->right = remove_carro(raiz->right, sucessor->placa);
    }

    return raiz;
}


carro *encontrarMenorNo(carro *raiz) 
{
    if (raiz == NULL) 
        return NULL;
    
    while (raiz->left != NULL) 
        raiz = raiz->left;

    return raiz;
}
