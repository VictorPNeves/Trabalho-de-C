#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do Nó da Lista Encadeada
typedef struct Node {
    char data[100];
    struct Node* next;
} Node;

// Fila (FIFO) construída com ponteiros para o início (head) e fim (tail)
typedef struct {
    Node* head;
    Node* tail;
} Queue;

// Pilha (LIFO) construída com ponteiro para o topo (top)
typedef struct {
    Node* top;
} Stack;

// ================= FUNÇÕES DA FILA (QUEUE) =================
void initQueue(Queue* q) {
    q->head = NULL;
    q->tail = NULL;
}

int isQueueEmpty(Queue* q) {
    return q->head == NULL;
}

void enqueue(Queue* q, const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->next = NULL;
    
    if (q->tail == NULL) {
        q->head = q->tail = newNode;
        return;
    }
    q->tail->next = newNode;
    q->tail = newNode;
}

void dequeue(Queue* q, char* outData) {
    if (isQueueEmpty(q)) {
        outData[0] = '\0';
        return;
    }
    Node* temp = q->head;
    strcpy(outData, temp->data);
    q->head = q->head->next;
    
    if (q->head == NULL) {
        q->tail = NULL;
    }
    free(temp); // Liberação de memória dinâmica
}

// ================= FUNÇÕES DA PILHA (STACK) =================
void initStack(Stack* s) {
    s->top = NULL;
}

int isStackEmpty(Stack* s) {
    return s->top == NULL;
}

void push(Stack* s, const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->next = s->top;
    s->top = newNode;
}

void pop(Stack* s, char* outData) {
    if (isStackEmpty(s)) {
        outData[0] = '\0';
        return;
    }
    Node* temp = s->top;
    strcpy(outData, temp->data);
    s->top = s->top->next;
    free(temp); // Liberação de memória dinâmica
}

// ================= SISTEMA PRINCIPAL E REQUISITOS =================
Queue filaRegular;
Queue filaEmergencia;
Stack historico;

void enfileirar_paciente() {
    char nome[100];
    int tipo;
    
    printf("\nNome do paciente: ");
    scanf(" %[^\n]s", nome);
    
    printf("Tipo (1 - Regular, 2 - Emergência): ");
    scanf("%d", &tipo);
    
    if (tipo == 2) {
        enqueue(&filaEmergencia, nome);
        printf("🚨 [EMERGÊNCIA] Paciente \"%s\" entrou na fila prioritária.\n", nome);
    } else {
        enqueue(&filaRegular, nome);
        printf("✅ [REGULAR] Paciente \"%s\" entrou na fila normal.\n", nome);
    }
}

void processar_atendimento() {
    char paciente[100];
    char registro[120];
    
    // Regra de Negócio: Priorizar sempre a fila de emergência
    if (!isQueueEmpty(&filaEmergencia)) {
        dequeue(&filaEmergencia, paciente);
        printf("\n👨‍⚕️ [ATENDIMENTO] Médico chamou: %s (Emergência)\n", paciente);
        sprintf(registro, "%s (Emergência)", paciente);
        push(&historico, registro); // Guarda no histórico LIFO
    } 
    else if (!isQueueEmpty(&filaRegular)) {
        dequeue(&filaRegular, paciente);
        printf("\n👨‍⚕️ [ATENDIMENTO] Médico chamou: %s (Regular)\n", paciente);
        sprintf(registro, "%s (Regular)", paciente);
        push(&historico, registro); // Guarda no histórico LIFO
    } 
    else {
        printf("\n📭 Nenhum paciente aguardando atendimento no momento.\n");
    }
}

void auditar_historico() {
    int n, count = 0;
    char paciente[120];
    Stack tempStack; // Pilha auxiliar para não destruir os dados originais
    initStack(&tempStack);
    
    printf("\nQuantas consultas finalizadas deseja auditar? ");
    scanf("%d", &n);
    
    printf("\n--- 📋 AUDITORIA: Últimas %d consultas (Ordem LIFO) ---\n", n);
    if (isStackEmpty(&historico)) {
        printf("Nenhum histórico disponível.\n");
        return;
    }
    
    // Desempilha os elementos para leitura exibindo os mais recentes primeiro
    while (!isStackEmpty(&historico) && count < n) {
        pop(&historico, paciente);
        printf("%dº mais recente: %s\n", count + 1, paciente);
        push(&tempStack, paciente);
        count++;
    }
    
    // Restaura a pilha de histórico original preservando a integridade dos dados
    while (!isStackEmpty(&tempStack)) {
        pop(&tempStack, paciente);
        push(&historico, paciente);
    }
    printf("-----------------------------------------------------\n");
}

int main() {
    // Inicialização das estruturas vazias
    initQueue(&filaRegular);
    initQueue(&filaEmergencia);
    initStack(&historico);
    
    int opcao;
    
    do {
        printf("\n======= SISTEMA DE ATENDIMENTO BLUA =======");
        printf("\n1. Inserir Paciente na Fila (Enqueue)");
        printf("\n2. Chamar Próximo Paciente (Dequeue)");
        printf("\n3. Consultar Histórico de Auditoria (Pilha)");
        printf("\n4. Sair do Sistema");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: enfileirar_paciente(); break;
            case 2: processar_atendimento(); break;
            case 3: auditar_historico(); break;
            case 4: printf("\nEncerrando o sistema Blua...\n"); break;
            default: printf("\nOpção inválida! Tente novamente.\n");
        }
    } while(opcao != 4);
    
    return 0;
}
