#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// estrutura para representar uma tafera 
typedef struct Tarefa {
    int id;
    char descricao[100];
    struct Tarefa* next;
} Tarefa;

// fun��o para criar uma nova tarefa 
Tarefa* criarTarefa(int id, const char* descricao) {
    Tarefa* novaTarefa = (Tarefa*)malloc(sizeof(Tarefa));
    novaTarefa->id = id;
    strcpy(novaTarefa->descricao, descricao);
    novaTarefa->next = NULL;
    return novaTarefa;
}

// Fun��o para inserir uma nova tarefa no final da lista 
void inserirTarefa(Tarefa** head, int id, const char* descricao) {
    Tarefa* novaTarefa = criarTarefa(id, descricao);
    if (*head == NULL){
        *head = novaTarefa;
    } else {
        Tarefa* prev = *head;
        while (prev->next != NULL){
           prev = prev-> next;
        }
        prev->next = novaTarefa;
    }
}

//Função para exibir todas as tarefas
void exibirTarefas(Tarefa* head){
    Tarefa* prev = head;
    if (prev == NULL){
        printf("Nenhuma tarefa pendente.\n");
        return;
    }
    printf("Tarefas pendentes: \n");
    while (prev != NULL){
        printf("ID: %d, Descri��o: %s\n", prev->id, prev->descricao);
        prev = prev->next;
    }
}

//Função para remover uma tafera 
void removerTarefa(Tarefa** head, int id ) {
    Tarefa* prev = *head;
    Tarefa* anterior = NULL;

    while (prev != NULL && prev->id != id){
        anterior = prev;
        prev = prev->next;
    }

    if(prev == NULL){
        printf("Tarefa com ID %d n�o encontrada.\n", id);
        return;
    }

    if (anterior == NULL) {
        *head = prev->next; //remove a primeira tarefa 
    } else {
        anterior->next = prev->next; //remove a ultima tarefa 
    }

    free(prev);
    printf("Tarefa com ID %d removida.\n", id);
}

//fun��o principal 
int main(){
    setlocale(LC_ALL, "Portuguese"); //Corre��o de Acentos
    Tarefa* listaTarefas = NULL;
    int opcao, id;
    char descricao[100];

     do {
        printf("\nGerenciador de Tarefas\n");
        printf("1. Inserir Tarefa\n");
        printf("2. Exibir Tarefas\n");
        printf("3. Remover Tarefa\n");
        printf("4. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do stdin

        switch (opcao) {
            case 1:
                printf("Digite o ID da tarefa: ");
                scanf("%d", &id);
                getchar(); // Limpar o buffer
                printf("Digite a descri��o da tarefa: ");
                fgets(descricao, sizeof(descricao), stdin);
                descricao[strcspn(descricao, "\n")] = 0; // Remove a nova linha
                inserirTarefa(&listaTarefas, id, descricao);
                break;
            case 2:
                exibirTarefas(listaTarefas);
                break;
            case 3:
                printf("Digite o ID da tarefa a ser removida: ");
                scanf("%d", &id);
                removerTarefa(&listaTarefas, id);
                break;
            case 4:
                printf("Saindo do gerenciador de tarefas.\n");
                break;
            default:
                printf("Op��o inv�lida! Tente novamente.\n");
        }
    } while (opcao != 4);

    // Libera a memoria usada pela lista
    while (listaTarefas != NULL) {
        removerTarefa(&listaTarefas, listaTarefas->id);
    }

    return 0;
}