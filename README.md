# 📋 Sistema de Controle de Captação de Clientes

> Trabalho Prático I — Estrutura de Dados I  
> Implementado em linguagem **C**

---

## 📌 Visão Geral

Sistema que gerencia três grupos distintos de clientes utilizando estruturas de dados adequadas para cada fluxo:

| Grupo | Estrutura | Comportamento |
|---|---|---|
| Potenciais clientes aguardando contato | Fila (FIFO) | Primeiro cadastrado é o primeiro atendido |
| Compradores efetivos | Fila (FIFO) | Primeiro comprador tem pedido processado primeiro |
| Clientes arquivados | Pilha (LIFO) | Último arquivado é o primeiro candidato a recontato |

---

## 🗂️ Estrutura de Arquivos

```
.
├── include/
│   ├── tipos.h               # Structs: Data, Endereco, nós e coleções
│   ├── utils.h               # Protótipos de funções utilitárias
│   ├── fila_espera.h         # Interface da fila de potenciais clientes
│   ├── fila_compradores.h    # Interface da fila de compradores
│   ├── pilha_arquivados.h    # Interface da pilha de arquivados
│   └── menu.h                # Interface dos menus e UI
├── src/
│   ├── utils.c               # Leitura segura de strings, datas, tela
│   ├── fila_espera.c         # Implementação da fila de espera (FIFO)
│   ├── fila_compradores.c    # Implementação da fila de compradores (FIFO)
│   ├── pilha_arquivados.c    # Implementação da pilha de arquivados (LIFO)
│   ├── menu.c                # Lógica de interface e fluxo de negócio
│   └── main.c                # Ponto de entrada — inicialização e loop principal
└── Makefile                  # Compilação com flags -Wall -Wextra -pedantic
```

---

## ⚙️ Compilação e Execução

### Comandos

```bash
# Compilar
make

# Executar
./captacao

# Limpar arquivos de compilação
make clean
```

> O Makefile usa `-Wall -Wextra -pedantic -std=c99`. A compilação atual produz **zero warnings**.

---

## 🏗️ Justificativa das Estruturas de Dados

### FilaEspera — Clientes Aguardando Contato

**Estrutura:** Fila FIFO com lista simplesmente encadeada (ponteiros de frente e de trás)

- O enunciado exige que *o cliente cadastrado há mais tempo seja exibido primeiro* — comportamento FIFO clássico.
- Ponteiro de frente (`dequeue O(1)`) e ponteiro de trás (`enqueue O(1)`) eliminam percurso completo a cada inserção.
- Busca por nome `O(n)` — aceitável para o tamanho típico da fila de atendimento.

### FilaCompradores — Clientes que Compraram

**Estrutura:** Fila FIFO com lista simplesmente encadeada (ponteiros de frente e de trás)

- O enunciado é explícito: *cliente que compra primeiro tem seu pedido processado para envio primeiro* — definição textual de fila FIFO.
- `enqueue` no final é `O(1)` graças ao ponteiro de trás, preservando a ordem cronológica sem overhead.

### PilhaArquivados — Clientes que Não Compraram

**Estrutura:** Pilha LIFO com lista simplesmente encadeada e ponteiro de topo

- O enunciado não define ordem de recontato — a pilha é a estrutura mais simples e eficiente para esse caso.
- O cliente arquivado mais recentemente é o candidato mais natural para recontato (interesse mais recente).
- `Push` e `Pop` são `O(1)` sem ponteiro de cauda — implementação mínima e sem risco de bug.

---

## 🔧 Funcionalidades

### Menu Principal

Quatro opções: **Cadastrar**, **Realizar Contato**, **Relatórios** e **Sair**.  
Entrada tratada com `atoi()`, com aviso ao usuário em caso de opção inválida.

### Cadastrar Cliente

Lê nome, telefone, email e data de captação (validada no formato `dd/mm/aaaa`). Insere o novo nó no final da fila via `enqueue O(1)`.

### Realizar Contato

Exibe o cliente mais antigo da fila e permite ao operador:

- **Avançar** para o próximo (`atual->prox`)
- **Voltar** para o anterior (percorre desde a frente até o nó anterior)
- **Buscar** por nome exato (busca linear, mantém cliente atual se não encontrar)
- **Finalizar** atendimento — desencadeia o fluxo de compra, arquivamento ou exclusão

### Finalizar Atendimento

```
Comprou?
├── Sim  → lê dados adicionais (nascimento, endereço, CPF)
│          enqueue na FilaCompradores
│          remove da FilaEspera + free()
└── Não  → Arquivar?
           ├── Sim  → push na PilhaArquivados
           │          remove da FilaEspera + free()
           └── Não  → remove da FilaEspera + free() completo
```

### Relatórios

| Relatório | Descrição |
|---|---|
| 1 | Número de clientes aguardando (`fila_espera_tamanho()`) |
| 2 | Lista todos com nome, data de captação e dias de espera |

---

## 🧠 Resumo das Operações por Estrutura

| Estrutura | Inserção / Remoção | Uso no Sistema |
|---|---|---|
| FilaEspera (FIFO) | `enqueue` (trás) / `dequeue` (frente) | Cadastrar / Atender o mais antigo |
| FilaCompradores (FIFO) | `enqueue` (trás) / `dequeue` (frente) | Registrar compra / Logística processa pedido |
| PilhaArquivados (LIFO) | `push` (topo) / `pop` (topo) | Arquivar / Recuperar para recontato |

---

## 🛡️ Gerenciamento de Memória

- Todo `malloc()` é verificado (`if (novo == NULL)`) antes de usar o ponteiro. Erros são reportados em `stderr` sem crash.
- `dequeue()` e `remover_no()` retornam o ponteiro ao chamador, que é responsável pelo `free()`.
- `enqueue()` e `push()` alocam um **novo nó** copiando os dados; o nó original da fila de espera é liberado em seguida pelo `menu.c`.
- As funções `*_destruir()` percorrem toda a coleção liberando cada nó e são chamadas no `main()` antes de encerrar.

> ✅ Nenhum vazamento de memória em nenhum fluxo do sistema.

---

## ❓ Perguntas e Respostas Técnicas

<details>
<summary><strong>Por que fila para clientes aguardando contato?</strong></summary>

O enunciado exige que o cliente cadastrado há mais tempo seja atendido primeiro — comportamento FIFO clássico. Mantemos ponteiros para frente (`dequeue`) e trás (`enqueue`) para que ambas as operações sejam `O(1)`.
</details>

<details>
<summary><strong>Por que também fila para os compradores?</strong></summary>

O enunciado diz explicitamente: *"cliente que compra primeiro tem seu pedido processado para envio primeiro"*. Isso é a definição de fila. A logística processa pedidos via `dequeue` na frente da fila.
</details>

<details>
<summary><strong>Por que pilha para os arquivados?</strong></summary>

O enunciado não define ordem para recontatar arquivados. A pilha é a estrutura mais simples (`push`/`pop` `O(1)`) quando não há necessidade de ordem. Além disso, o cliente arquivado mais recentemente tem interesse mais recente, tornando-se candidato natural para recontato imediato.
</details>

<details>
<summary><strong>Como funciona enqueue e dequeue?</strong></summary>

**Enqueue:** cria nó com `malloc`, preenche dados, faz `f->tras->prox` apontar para o novo nó e atualiza `f->tras`. `O(1)`.

**Dequeue:** salva `f->frente`, avança `f->frente` para o próximo, retorna o nó. O chamador faz `free()`. `O(1)`.
</details>

<details>
<summary><strong>Como evitar vazamento de memória?</strong></summary>

Cada `malloc` tem um `free` correspondente. `dequeue` e `remover_no` retornam o ponteiro ao chamador, que chama `free()` após usar o nó. As funções `*_destruir()` liberam toda a coleção e são chamadas no `main()` antes de encerrar.
</details>

<details>
<summary><strong>Como funciona a busca por nome?</strong></summary>

Busca linear `O(n)`: percorre do primeiro ao último nó comparando com `strcmp()`. Se encontrar, retorna o ponteiro; se não, retorna `NULL` e o sistema mantém o cliente atual exibido.
</details>

<details>
<summary><strong>Como calcular os dias desde a captação?</strong></summary>

Convertemos cada data para dias julianos usando a fórmula de Fliegel-Van Flandern (implementada em `data_para_dias()`), depois subtraímos. A data de hoje é obtida com `time()` + `localtime()` de `<time.h>`.
</details>

<details>
<summary><strong>O que é ler_string e por que foi criada?</strong></summary>

Wrapper em torno de `fgets()` que: imprime o prompt; lê até `tamanho-1` caracteres evitando buffer overflow; remove o `\n` final; descarta o restante da linha no `stdin` se a string foi maior que o buffer. Isso evita que leituras anteriores deixem lixo no `stdin`.
</details>

<details>
<summary><strong>O que acontece se malloc retornar NULL?</strong></summary>

As funções verificam o retorno. Se for `NULL`, imprimem mensagem de erro em `stderr` e retornam sem modificar a estrutura. O programa continua executando sem crash nem segfault.
</details>


