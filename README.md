# Trabalho-de-C
#  Sistema de Gerenciamento de Fila de Atendimento - Blua

Este repositório contém o código-fonte de um sistema interativo em **Linguagem C** projetado para gerenciar o fluxo de teleconsultas da plataforma de saúde **Blua**. A aplicação simula a triagem de pacientes em filas com níveis de prioridade e rastreia o histórico de atendimentos realizados para fins de auditoria.

---

##  Restrições Técnicas e Arquitetura

Em conformidade com as diretrizes do desafio pedagógico, **o projeto foi construído inteiramente do zero, sem a utilização de bibliotecas prontas de estruturas de dados**. 

* **Gerenciamento Dinâmico de Memória:** Todas as estruturas utilizam alocação dinâmica (`malloc` e `free`) via ponteiros. Essa abordagem evita o desperdício de memória associado a arrays estáticos subutilizados, otimizando o *memory footprint* e poupando ciclos de CPU.
* **Princípios de Green IT:** A eficiência algorítmica aplicada reduz o consumo de recursos computacionais do servidor host, alinhando-se às práticas de desenvolvimento de software sustentável.

---

##  Estruturas de Dados Implementadas

O sistema baseia-se na manipulação de **Listas Encadeadas** para estruturar dois comportamentos clássicos:

### 1. Fila Dinâmica (Queue) — Comportamento FIFO (*First-In, First-Out*)
Utilizada tanto para a **Fila Regular** quanto para a **Fila de Emergência**. 
* **Operações:** `initQueue`, `isQueueEmpty`, `enqueue` (inserção no fim/`tail`) e `dequeue` (remoção no início/`head`).
* **Complexidade Temporal:** $O(1)$ para inserção e remoção, graças à manutenção dos ponteiros de início e fim.

### 2. Pilha Dinâmica (Stack) — Comportamento LIFO (*Last-In, First-Out*)
Utilizada para o **Histórico de Auditoria**.
* **Operações:** `initStack`, `isStackEmpty`, `push` (inserção no topo/`top`) e `pop` (remoção do topo).
* **Complexidade Temporal:** $O(1)$ para adição de novos registros de consultas finalizadas.

---

##  Regras de Negócio e Fluxo do Menu

O programa roda em um menu interativo no terminal com as seguintes opções:

1. **Inserir Paciente na Fila (Enqueue):** Permite cadastrar o nome do paciente e definir o tipo de atendimento. Se for **Emergência (2)**, o nó é inserido na fila prioritária; se for **Regular (1)**, vai para a fila comum.
2. **Chamar Próximo Paciente (Dequeue):** O sistema realiza a chamada priorizando **sempre** a fila de emergência. A fila regular só começa a ser escoada quando não houver nenhuma emergência pendente. Cada paciente chamado é empilhado imediatamente no histórico.
3. **Consultar Histórico de Auditoria (Pilha):** Permite ao usuário escolher visualizar as últimas $N$ consultas finalizadas. O sistema desempilha e exibe os dados (mostrando o atendimento mais recente primeiro), utilizando uma pilha auxiliar para restaurar os dados originais logo em seguida, preservando a integridade do histórico.
4. **Sair do Sistema:** Encerra a aplicação.
