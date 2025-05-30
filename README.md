# 🎟️ Sistema de Venda de Ingressos em C

Este projeto é um sistema simples de controle de venda e cancelamento de ingressos para uma sala de cinema. Ele simula a reserva de poltronas, armazenando o estado da plateia em arquivo e permitindo operações como venda, cancelamento e visualização de ocupação.

## 📌 Funcionalidades

- 📋 Menu interativo via terminal
- 🎫 Venda de ingressos (meia ou inteira)
- ❌ Cancelamento de ingressos vendidos
- 🪑 Visualização da plateia com numeração de assentos disponíveis
- 📊 Visualização da ocupação com contagem de ingressos vendidos
- 💾 Persistência da plateia em arquivo (`plateia.txt`)

## 🧠 Estrutura da Plateia

A sala é composta por 10 linhas e 12 colunas, totalizando 120 poltronas numeradas de 1 a 120.

- `-` → Poltrona livre  
- `M` → Poltrona vendida (meia)  
- `I` → Poltrona vendida (inteira)

## 🗂️ Arquivos

- `main.c` → Código-fonte principal
- `plateia.txt` → Armazena o estado atual das poltronas

## ⚙️ Como Compilar

Use `gcc` para compilar o programa:

```bash
gcc main.c -o cinema
```

## ▶️ Como Executar

```bash
./cinema
```

## 💡 Exemplo de Execução

```text
-------------------------------
        MENU
-------------------------------
0 - Sair do programa
1 - Mostrar plateia
2 - Mostrar ocupação
3 - Vender ingresso
4 - Cancelar ingresso (devolução)
-------------------------------
Digite a opção desejada:
```

## 📚 Requisitos Técnicos

- Linguagem: C
- Plataforma: Terminal
- Compatibilidade: Linux / Windows (com Dev-C++ ou equivalente)

---

### 🧑‍💻 Autor

**Pedro Antonio Couto Terres**  
Estudante de Engenharia da Computação  
[GitHub](https://github.com/Terres06)
