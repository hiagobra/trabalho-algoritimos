// ============================================================
// trabalho de algoritmos 1
// aluno: hiago brambatti
// curso: bacharelado em sistemas de informacao
// professor: alessandro joao brassanini
// disciplina: algoritmos 1
// data:24 de abril de 2026
//
// descricao:
// esse programa resolve equacoes do 1 grau, do 2 grau e
// tambem sistemas lineares 2x2 usando a regra de cramer.
// tudo com o passo a passo, meio que nem o professor faz no
// quadro, pra ficar facil de acompanhar as contas.
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

// prototipos das funcoes (coloquei aqui em cima pq fica mais
// organizado e da pra declarar main() antes das outras)
void exibirMenu(void);
void resolverPrimeiroGrau(void);
void resolverSegundoGrau(void);
void resolverSistemaCramer(void);
void sobrePrograma(void);
void pausar(void);
void limparTela(void);
void limparBuffer(void);

// ============================================================
// funcao principal
// ============================================================
int main(void)
{
    int opcao;

    // tentei usar o setlocale pra sair os acentos direitinho
    // no terminal do windows, as vezes funciona as vezes nao
    setlocale(LC_ALL, "Portuguese");

    // loop do menu. so sai quando o usuario digitar 0
    do {
        limparTela();
        exibirMenu();
        printf("digite a opcao desejada: ");

        // se o scanf nao ler um numero a gente limpa e volta
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("\nopcao invalida, tente de novo.\n");
            pausar();
            opcao = -1; // forca o loop a continuar
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                resolverPrimeiroGrau();
                break;
            case 2:
                resolverSegundoGrau();
                break;
            case 3:
                resolverSistemaCramer();
                break;
            case 4:
                sobrePrograma();
                break;
            case 0:
                printf("\nate mais! valeu por usar o programa.\n");
                break;
            default:
                printf("\nessa opcao nao existe no menu, escolhe outra.\n");
                pausar();
        }
    } while (opcao != 0);

    return 0;
}

// ============================================================
// exibe o menu principal na tela
// ============================================================
void exibirMenu(void)
{
    printf("============================================\n");
    printf("     calculadora de equacoes - algoritmos   \n");
    printf("============================================\n");
    printf(" [1] equacao do 1 grau  (ax + b = 0)        \n");
    printf(" [2] equacao do 2 grau  (ax^2 + bx + c = 0) \n");
    printf(" [3] sistema linear 2x2 (regra de cramer)   \n");
    printf(" [4] sobre o programa                       \n");
    printf(" [0] sair                                   \n");
    printf("============================================\n");
}

// ============================================================
// resolve equacao do 1 grau no formato: ax + b = 0
// ============================================================
void resolverPrimeiroGrau(void)
{
    // usei float pra ficar mais leve, daria pra usar double

    float a, b, x;

    limparTela();
    printf("========== equacao do 1 grau ==========\n");
    printf("formato geral: a*x + b = 0\n\n");

    printf("digite o valor de a: ");
    scanf("%f", &a);
    printf("digite o valor de b: ");
    scanf("%f", &b);
    limparBuffer();

    printf("\n---- resolvendo passo a passo ----\n");
    printf("equacao: (%.2f)*x + (%.2f) = 0\n\n", a, b);

    // primeiro a gente precisa ver se o a e zero,
    // pq se for nao tem como dividir por ele
    if (a == 0) {
        if (b == 0) {
            // 0 = 0 sempre e verdade, entao qualquer x serve
            printf("como a = 0 e b = 0, ficou:\n");
            printf("   0 = 0\n");
            printf("isso e verdade pra qualquer valor de x.\n");
            printf("-> equacao com infinitas solucoes (indeterminada).\n");
        } else {
            // 0 = numero, isso nunca e verdade
            printf("como a = 0 e b != 0, ficou:\n");
            printf("   %.2f = 0\n", b);
            printf("isso nunca e verdade.\n");
            printf("-> equacao sem solucao (impossivel).\n");
        }
        pausar();
        return;
    }

    // agora sim, passo a passo como se fosse no caderno
    printf("passo 1 - passar o b pro outro lado (troca de sinal):\n");
    printf("   %.2f*x = -(%.2f)\n", a, b);
    printf("   %.2f*x = %.2f\n\n", a, -b);

    printf("passo 2 - dividir os dois lados por a (%.2f):\n", a);
    printf("   x = (%.2f) / (%.2f)\n", -b, a);

    x = -b / a;
    printf("   x = %.4f\n\n", x);

    // pra fechar bonito, faz a prova real substituindo o x
    // de volta na equacao original (isso aqui e mo legal)
    printf("passo 3 - prova real (substitui x na equacao):\n");
    printf("   (%.2f)*(%.4f) + (%.2f) = %.4f\n",
           a, x, b, a * x + b);
    printf("   como o resultado deu (aproximadamente) 0, confere!\n");

    printf("\n==> resposta final: x = %.4f\n", x);

    pausar();
}

// ============================================================
// resolve equacao do 2 grau no formato: ax^2 + bx + c = 0
// usa bhaskara com o delta (discriminante)
// ============================================================
void resolverSegundoGrau(void)
{
    float a, b, c;
    float delta, raizDelta;
    float x1, x2;

    limparTela();
    printf("========== equacao do 2 grau ==========\n");
    printf("formato geral: a*x^2 + b*x + c = 0\n\n");

    printf("digite o valor de a: ");
    scanf("%f", &a);
    printf("digite o valor de b: ");
    scanf("%f", &b);
    printf("digite o valor de c: ");
    scanf("%f", &c);
    limparBuffer();

    // se o a for zero entao na verdade nem e do 2 grau, e
    // do 1 grau disfarcado. avisa o usuario
    if (a == 0) {
        printf("\nopa, como a = 0 essa equacao nao e do 2 grau.\n");
        printf("ela virou do 1 grau (b*x + c = 0).\n");
        printf("volta no menu e escolhe a opcao [1] pra resolver.\n");
        pausar();
        return;
    }

    printf("\n---- resolvendo passo a passo ----\n");
    printf("equacao: (%.2f)*x^2 + (%.2f)*x + (%.2f) = 0\n\n", a, b, c);

    // passo 1 - calcular o delta (b^2 - 4ac)
    printf("passo 1 - calcular o delta (discriminante):\n");
    printf("   delta = b^2 - 4*a*c\n");
    printf("   delta = (%.2f)^2 - 4*(%.2f)*(%.2f)\n", b, a, c);
    printf("   delta = %.2f - (%.2f)\n", b * b, 4 * a * c);

    delta = (b * b) - (4 * a * c);
    printf("   delta = %.2f\n\n", delta);

    // passo 2 - analisar o delta (tem 3 casos possiveis)
    printf("passo 2 - analisar o sinal do delta:\n");

    if (delta < 0) {
        // delta negativo -> nao tem raiz real
        // (teria raiz complexa, mas a gente so ve isso la na
        // frente no curso, entao deixei de fora)
        printf("   delta < 0, entao a equacao NAO tem raizes reais.\n");
        printf("   (nesse caso as raizes seriam complexas)\n");
        printf("\n==> a equacao nao possui solucao nos reais.\n");
        pausar();
        return;
    }

    if (delta == 0) {
        // delta zero -> uma raiz so (ou duas iguais)
        printf("   delta = 0, entao a equacao tem 1 raiz real\n");
        printf("   (ou duas raizes iguais, depende do jeito que explica)\n\n");

        printf("passo 3 - aplicar bhaskara:\n");
        printf("   x = -b / (2*a)\n");
        printf("   x = -(%.2f) / (2*%.2f)\n", b, a);
        printf("   x = %.2f / %.2f\n", -b, 2 * a);

        x1 = -b / (2 * a);
        printf("   x = %.4f\n", x1);

        printf("\n==> resposta final: x1 = x2 = %.4f\n", x1);
    } else {
        // delta positivo -> duas raizes reais diferentes
        printf("   delta > 0, entao a equacao tem 2 raizes reais diferentes.\n\n");

        raizDelta = (float) sqrt((double) delta);

        printf("passo 3 - calcular a raiz quadrada do delta:\n");
        printf("   raiz(delta) = raiz(%.2f) = %.4f\n\n", delta, raizDelta);

        printf("passo 4 - aplicar bhaskara:\n");
        printf("   x = (-b +- raiz(delta)) / (2*a)\n");
        printf("   x = (-(%.2f) +- %.4f) / (2*%.2f)\n", b, raizDelta, a);
        printf("   x = (%.2f +- %.4f) / %.2f\n\n", -b, raizDelta, 2 * a);

        x1 = (-b + raizDelta) / (2 * a);
        x2 = (-b - raizDelta) / (2 * a);

        printf("   x1 = (%.2f + %.4f) / %.2f = %.4f\n",
               -b, raizDelta, 2 * a, x1);
        printf("   x2 = (%.2f - %.4f) / %.2f = %.4f\n",
               -b, raizDelta, 2 * a, x2);

        printf("\n==> resposta final: x1 = %.4f  e  x2 = %.4f\n", x1, x2);

        // bonus - relacoes de girard
        // isso aqui eu aprendi em algebra linear, a soma e o
        // produto das raizes da pra tirar direto dos coefici-
        // entes, sem precisar achar as raizes primeiro.
        // e uma forma boa de conferir se as contas batem.
        printf("\n---- bonus: relacoes de girard ----\n");
        printf("pelas formulas:\n");
        printf("   soma    = x1 + x2 = -b/a = %.4f\n", -b / a);
        printf("   produto = x1 * x2 =  c/a = %.4f\n", c / a);
        printf("conferindo com as raizes que calculamos:\n");
        printf("   soma    = %.4f + %.4f = %.4f\n", x1, x2, x1 + x2);
        printf("   produto = %.4f * %.4f = %.4f\n", x1, x2, x1 * x2);
        printf("bateu! entao as contas estao certas.\n");
    }

    pausar();
}

// ============================================================
// resolve sistema linear 2x2 usando a regra de cramer
//
//   a1*x + b1*y = c1
//   a2*x + b2*y = c2
//
// essa parte foi pra usar mais coisa de algebra linear
//   D  -> matriz dos coeficientes
//   Dx -> troca a coluna do x pelos termos independentes
//   Dy -> troca a coluna do y pelos termos independentes
// e no final x = Dx/D  e  y = Dy/D
// ============================================================
void resolverSistemaCramer(void)
{
    float a1, b1, c1;
    float a2, b2, c2;
    float D, Dx, Dy;
    float x, y;

    limparTela();
    printf("========== sistema linear 2x2 (cramer) ==========\n");
    printf("formato geral:\n");
    printf("   a1*x + b1*y = c1\n");
    printf("   a2*x + b2*y = c2\n\n");

    printf("-- primeira equacao --\n");
    printf("digite a1: "); scanf("%f", &a1);
    printf("digite b1: "); scanf("%f", &b1);
    printf("digite c1: "); scanf("%f", &c1);

    printf("\n-- segunda equacao --\n");
    printf("digite a2: "); scanf("%f", &a2);
    printf("digite b2: "); scanf("%f", &b2);
    printf("digite c2: "); scanf("%f", &c2);
    limparBuffer();

    printf("\n---- resolvendo passo a passo ----\n");
    printf("o sistema ficou assim:\n");
    printf("   (%.2f)*x + (%.2f)*y = %.2f\n", a1, b1, c1);
    printf("   (%.2f)*x + (%.2f)*y = %.2f\n\n", a2, b2, c2);

    // mostra a matriz dos coeficientes de um jeito visual
    printf("montando as matrizes:\n");
    printf("   matriz dos coeficientes:\n");
    printf("      | %6.2f  %6.2f |\n", a1, b1);
    printf("      | %6.2f  %6.2f |\n\n", a2, b2);

    // passo 1 - calcular D (determinante principal)
    // lembrando que pra matriz 2x2 o determinante e:
    //   det = (a*d) - (b*c)
    printf("passo 1 - calcular o determinante D (principal):\n");
    printf("   D = (a1 * b2) - (a2 * b1)\n");
    printf("   D = (%.2f * %.2f) - (%.2f * %.2f)\n", a1, b2, a2, b1);
    printf("   D = %.2f - %.2f\n", a1 * b2, a2 * b1);

    D = (a1 * b2) - (a2 * b1);
    printf("   D = %.2f\n\n", D);

    // se o D for zero, o sistema nao tem solucao unica
    if (D == 0) {
        printf("como D = 0, o sistema NAO tem solucao unica.\n");
        printf("pode ser:\n");
        printf("  - sistema possivel indeterminado (infinitas solucoes)\n");
        printf("  - sistema impossivel (nao tem solucao nenhuma)\n");
        printf("pra saber qual dos dois teria que analisar mais,\n");
        printf("mas pra regra de cramer ja parou aqui.\n");
        pausar();
        return;
    }

    // passo 2 - calcular Dx (troca a coluna do x)
    printf("passo 2 - calcular Dx (troca a coluna do x por c1,c2):\n");
    printf("      | %6.2f  %6.2f |\n", c1, b1);
    printf("      | %6.2f  %6.2f |\n", c2, b2);
    printf("   Dx = (c1 * b2) - (c2 * b1)\n");
    printf("   Dx = (%.2f * %.2f) - (%.2f * %.2f)\n", c1, b2, c2, b1);
    printf("   Dx = %.2f - %.2f\n", c1 * b2, c2 * b1);

    Dx = (c1 * b2) - (c2 * b1);
    printf("   Dx = %.2f\n\n", Dx);

    // passo 3 - calcular Dy (troca a coluna do y)
    printf("passo 3 - calcular Dy (troca a coluna do y por c1,c2):\n");
    printf("      | %6.2f  %6.2f |\n", a1, c1);
    printf("      | %6.2f  %6.2f |\n", a2, c2);
    printf("   Dy = (a1 * c2) - (a2 * c1)\n");
    printf("   Dy = (%.2f * %.2f) - (%.2f * %.2f)\n", a1, c2, a2, c1);
    printf("   Dy = %.2f - %.2f\n", a1 * c2, a2 * c1);

    Dy = (a1 * c2) - (a2 * c1);
    printf("   Dy = %.2f\n\n", Dy);

    // passo 4 - dividir pra achar x e y
    printf("passo 4 - dividir pra achar x e y:\n");
    printf("   x = Dx / D = %.2f / %.2f\n", Dx, D);
    printf("   y = Dy / D = %.2f / %.2f\n\n", Dy, D);

    x = Dx / D;
    y = Dy / D;

    printf("   x = %.4f\n", x);
    printf("   y = %.4f\n\n", y);

    // prova real substituindo nas duas equacoes
    printf("passo 5 - prova real (substitui x e y nas equacoes):\n");
    printf("   eq1: (%.2f)*(%.4f) + (%.2f)*(%.4f) = %.4f  (esperado %.2f)\n",
           a1, x, b1, y, a1 * x + b1 * y, c1);
    printf("   eq2: (%.2f)*(%.4f) + (%.2f)*(%.4f) = %.4f  (esperado %.2f)\n",
           a2, x, b2, y, a2 * x + b2 * y, c2);
    printf("se os resultados baterem (a menos de pequenas casas\n");
    printf("decimais), quer dizer que a resposta esta correta.\n");

    printf("\n==> resposta final: x = %.4f  e  y = %.4f\n", x, y);

    pausar();
}

// ============================================================
// tela "sobre o programa" - fala quem fez e pra que serve
// ============================================================
void sobrePrograma(void)
{
    limparTela();
    printf("============================================\n");
    printf("            sobre o programa                \n");
    printf("============================================\n");
    printf(" trabalho da disciplina de algoritmos i     \n");
    printf(" curso: bacharelado em sistemas de informacao\n");
    printf(" professor: alessandro joao brassanini      \n");
    printf(" ano: 2026                                  \n");
    printf("--------------------------------------------\n");
    printf(" aluno:                                     \n");
    printf("   - hiago brambatti                        \n");
    printf("--------------------------------------------\n");
    printf(" objetivo: juntar o que aprendi em          \n");
    printf(" algoritmos com o que vi em algebra linear, \n");
    printf(" resolvendo equacoes do 1 grau, 2 grau e    \n");
    printf(" sistemas 2x2 pela regra de cramer, tudo    \n");
    printf(" com o passo a passo dos calculos.          \n");
    printf("============================================\n");

    pausar();
}

// ============================================================
// funcoes utilitarias (coisinhas pequenas pra ajudar)
// ============================================================

// pausa a execucao ate o usuario apertar enter, pra dar tempo
// de ler o resultado antes de voltar pro menu
void pausar(void)
{
    printf("\npressione ENTER para continuar...");
    getchar();
}

// limpa a tela do terminal. usei o system("cls") pq o programa
// foi feito pra rodar no windows. se fosse linux seria "clear"
void limparTela(void)
{
    system("cls");
}

// limpa o buffer do teclado, pq as vezes sobra um \n do scanf
// e isso atrapalha o proximo getchar/scanf
void limparBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // so vai descartando os caracteres ate achar o enter
    }
}
