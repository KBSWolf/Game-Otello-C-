#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
typedef struct registro{
    char nome[20];
    int idade;
    char sexo;//m ou f
    char cor;//p ou b
    int pontos;
}jogador;
void rank_registro(jogador *A){
    jogador r[5];
    int i;
    FILE *p;
    p=fopen("RANKJOGADORES.txt","r+");//Abertura do arquivo de Rank
    if(p==NULL){
        printf("Problema na abertura do arquivo");
        system("pause");
        exit(1);
    }
    char c;
    int linha=1;
    while((c=fgetc(p))!=EOF){//Contador de linhas
        linha++;
    }
    rewind(p);
    for(i=0;i<5;i++){
        fscanf(p,"%s %d %c %c %d",&r[i].nome,&r[i].idade,&r[i].sexo,&r[i].cor,&r[i].pontos);//Passagem das informaçoes para a struct r
    }
    rewind(p);
    printf("\nRank antigo:\n");//Mostrando rank antigo da struct
    for(i=0;i<5;i++){
        printf("%d Rank",i);
        printf("Nome:%s Idade:%d Sexo:%c([m]Masculino ou [f]Feminino) Cor da peca:%c ([p]preta ou [b]branca) Pontos:%d \n",r[i].nome,r[i].idade,r[i].sexo,r[i].cor,r[i].pontos);
    }
    bubble_sort(&*A,&r,5);//Faz a checagem do novo rank se houver e organiza a ordem
    printf("\nRank atual:\n");
    for(i=0;i<5;i++){
        printf("%d Rank",i);
        printf("Nome:%s Idade:%d Sexo:%c([m]Masculino ou [f]Feminino) Cor da peca:%c ([p]preta ou [b]branca) Pontos:%d \n",r[i].nome,r[i].idade,r[i].sexo,r[i].cor,r[i].pontos);
    }
    printf("O nome destacado no Rank atual e correspondente ao jogador que alterou o rank ");//Devido a um Bug encontrado no %s.
    printf("\n");
    for(i=0;i<5;i++){
       fprintf(p,"%s %d %c %c %d \n",r[i].nome,r[i].idade,r[i].sexo,r[i].cor,r[i].pontos);//Salva o novo rank no arquivo.
    }
    fclose(p);
}
void bubble_sort(jogador *A,jogador *r, int n){
    int i,j;
    jogador aux;
    for(i=0;i<n;i++){
        if(A->pontos>r[i].pontos){//Checa se o novo jogador bateu o rank de algum dos antigos jogadores
            r[i]=*A;
            break;
        }
    }
    for(i=1;i<n;i++){
        for(j=0;j<n-1;j++){
            if(r[j].pontos<r[j+1].pontos){//Ordena o rank com base do maior para o menor
                aux=r[j];
                r[j]=r[j+1];
                r[j+1]=aux;
            }
        }
    }
}
void imprimir_matriz(char matriz[][8]){
    int i,j;
    char t='A';
    printf("\n ");
    for(j=0;j<8;j++){
            printf(" %c ",t++);//Imprime as letras das colunas
    }
    printf("\n");
    for(i=0;i<8;i++){
            printf("%d",i);//imprime o numero das linhas
        for(j=0;j<8;j++){
            printf(" %c ",matriz[i][j]);//imprime o tabuleiro central
        }
        printf("\n");
    }
}
void placar(char matriz[][8],jogador *A,jogador *B){
    int pretas=0,brancas=0;
    int i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(matriz[i][j]=='p')//Separa as pretas e as brancas e as conta.
                pretas++;
            if(matriz[i][j]=='b')
                brancas++;
        }
    }
    printf("\nPretas:%d Brancas:%d\n",pretas,brancas);
    if(A->cor=='p'){//Checa quem e o primeiro a jogar e salva na struct correspondente
        A->pontos=pretas;
        B->pontos=brancas;
    }else if(B->cor=='p'){
        B->pontos=pretas;
        A->pontos=brancas;
    }
}
void vencedor(jogador *A,jogador *B){
    if(A->pontos>B->pontos){//Mostra quem dos dois jogadores ganhou a partida
        printf("Vitoria jogador A:%s, Vamos verificar o rank...",A->nome);
        rank_registro(&*A);
    }else if(B->pontos>A->pontos){
        printf("Vitoria jogador B:%s, Vamos verificar o rank...",B->nome);
        rank_registro(&*B);
    }
}
void imprimir_cadastro(jogador *A,jogador *B){//Imprime os dados do jogador.
    printf("\tA Nome:%s\tIdade:%d\n\tSexo:%c\n\tCor:%c\n\n\tB Nome:%s\tIdade:%d\n\tSexo:%c\n\tCor:%c\n",A->nome,A->idade,A->sexo,A->cor,B->nome,B->idade,B->sexo,B->cor);
}
void cadastro_jogador(jogador *A,jogador *B){//Coleta os dados do jogador.
    printf("Qual o nome do jogador A:");
    setbuf(stdin,NULL);
    fgets(A->nome,20,stdin);
    printf("Quantos anos jogador A:");
    scanf("%d",&A->idade);
    printf("(m)Masculino ou (f)Feminino?");
    scanf("%s",&A->sexo);
    printf("\n\nQual o nome do jogador B: ");
    setbuf(stdin,NULL);
    fgets(B->nome,20,stdin);
    printf("Quantos anos jogador B: ");
    scanf("%d",&B->idade);
    printf("(m)Masculino ou (f)Feminino?  ");
    scanf("%s",&B->sexo);
}
void movimento(jogador *A,jogador *B,char matriz[][8]){
    int vez=1,i,j;
    int turno=1;
    while(turno<=60){
        if(vez==1&&A->cor=='p'){
            for(i=0;i<8;i++){
                for(j=0;j<8;j++){//Cada if abaixo checa cada uma das direçoes da matriz a partir de um ponto, e ainda checa se cada cor oposta se encontra com um espaço em branco('0').
                    if(matriz[i][j]=='p'&&matriz[i+1][j]=='b'&&matriz[i+2][j]=='0'){
                        matriz[i+2][j]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i+1][j]=='b'&&matriz[i+2][j]=='b'){
                        int local=0;
                        for(int t=i;t<8;t++){
                            if(matriz[t+2][j]=='b'&&matriz[t+3][j]=='0'){//Else if checa a uma linha ou coluna ou vertical que seja em sequencia de cor oposta com espaço livre'0'
                                local=t+3;
                            }
                        }
                        if(local!=0)
                            matriz[local][j]='x';
                    }
                    if(matriz[i][j]=='p'&&matriz[i][j+1]=='b'&&matriz[i][j+2]=='0'){
                        matriz[i][j+2]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i][j+1]=='b'&&matriz[i][j+2]=='b'){//testar
                        int local=0;
                        for(int t=j;t<8;t++){
                            if(matriz[i][t+2]=='b'&&matriz[i][t+3]=='0'){
                                local=t+3;
                            }
                        }
                        if(local!=0)
                            matriz[i][local]='x';
                    }
                    if(matriz[i][j]=='p'&&matriz[i][j-1]=='b'&&matriz[i][j-2]=='0'){
                        matriz[i][j-2]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i][j-1]=='b'&&matriz[i][j-2]=='b'){//testar
                        int local=0;
                        for(int t=j;t<8;t++){
                            if(matriz[i][t-2]=='b'&&matriz[i][t-3]=='0'){
                                local=t-3;
                            }
                        }
                        if(local!=0)
                            matriz[i][local]='x';
                    }
                    if(matriz[i][j]=='p'&&matriz[i-1][j]=='b'&&matriz[i-2][j]=='0'){
                        matriz[i-2][j]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i-1][j]=='b'&&matriz[i-2][j]=='b'){//testar
                        int local=0;
                        for(int t=i;t<8;t++){
                            if(matriz[t-2][j]=='b'&&matriz[t-3][j]=='0'){
                                local=t-3;
                            }
                        }
                        if(local!=0)
                            matriz[i][local]='x';
                    }
                    if(matriz[i][j]=='p'&&matriz[i-1][j-1]=='b'&&matriz[i-2][j-2]=='0'){
                        matriz[i-2][j-2]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i-1][j-1]=='b'&&matriz[i-2][j-2]=='b'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t-2][r-2]=='b'&&matriz[t-3][r-3]=='0'){
                                    local=t-3;
                                    local2=r-3;
                                }
                            }
                        }
                        if(local!=0)
                        matriz[local][local2]='x';
                    }
                    if(matriz[i][j]=='p'&&matriz[i+1][j+1]=='b'&&matriz[i+2][j+2]=='0'){
                        matriz[i+2][j+2]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i+1][j+1]=='b'&&matriz[i+2][j+2]=='b'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t+2][r+2]=='b'&&matriz[t+3][r+3]=='0'){
                                    local=t+3;
                                    local2=r+3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                    if(matriz[i][j]=='p'&&matriz[i-1][j+1]=='b'&&matriz[i-2][j+2]=='0'){
                        matriz[i-2][j+2]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i-1][j+1]=='b'&&matriz[i-2][j+2]=='b'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t-2][r+2]=='b'&&matriz[t-3][r+3]=='0'){
                                    local=t-3;
                                    local2=r+3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                    if(matriz[i][j]=='p'&&matriz[i+1][j-1]=='b'&&matriz[i+2][j-2]=='0'){
                        matriz[i+2][j-2]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i+1][j-1]=='b'&&matriz[i+2][j-2]=='b'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t+2][r-2]=='b'&&matriz[t+3][r-3]=='0'){
                                    local=t+3;
                                    local2=r-3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                }
            }
            imprimir_matriz(&*matriz);
            vez=2;
            printf("Turno: %d",turno);
            turno++;
            jogada_A(&*A,&*B,&*matriz);
            placar(&*matriz,&*A,&*B);
            matriz_reset(&*matriz);
        }else if(vez==1&&B->cor=='p'){
            for(i=0;i<8;i++){
                for(j=0;j<8;j++){//Cada if abaixo checa cada uma das direçoes da matriz a partir de um ponto, e ainda checa se cada cor oposta se encontra com um espaço em branco('0').
                    if(matriz[i][j]=='p'&&matriz[i+1][j]=='b'&&matriz[i+2][j]=='0'){
                        matriz[i+2][j]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i+1][j]=='b'&&matriz[i+2][j]=='b'){//testar
                        int local=0;
                        for(int t=j;t<8;t++){
                            if(matriz[t+2][j]=='b'&&matriz[t+3][j]=='0'){//Else if checa a uma linha ou coluna ou vertical que seja em sequencia de cor oposta com espaço livre'0'
                                local=t+3;
                            }
                        }
                        if(local!=0)
                            matriz[local][j]='x';
                    }
                    if(matriz[i][j]=='p'&&matriz[i][j+1]=='b'&&matriz[i][j+2]=='0'){
                        matriz[i][j+2]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i][j+1]=='b'&&matriz[i][j+2]=='b'){//testar
                        int local=0;
                        for(int t=j;t<8;t++){
                            if(matriz[i][t+2]=='b'&&matriz[i][t+3]=='0'){
                                local=t+3;
                            }
                        }
                        if(local!=0)
                            matriz[i][local]='x';
                    }
                    if(matriz[i][j]=='p'&&matriz[i][j-1]=='b'&&matriz[i][j-2]=='0'){
                        matriz[i][j-2]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i][j-1]=='b'&&matriz[i][j-2]=='b'){//testar
                        int local=0;
                        for(int t=j;t<8;t++){
                            if(matriz[i][t-2]=='b'&&matriz[i][t-3]=='0'){
                                local=t-3;
                            }
                        }
                        if(local!=0)
                            matriz[i][local]='x';
                    }
                    if(matriz[i][j]=='p'&&matriz[i-1][j]=='b'&&matriz[i-2][j]=='0'){
                        matriz[i-2][j]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i-1][j]=='b'&&matriz[i-2][j]=='b'){//testar
                        int local=0;
                        for(int t=j;t<8;t++){
                            if(matriz[t-2][j]=='b'&&matriz[t-3][j]=='0'){
                                local=t-3;
                            }
                        }
                        if(local!=0)
                            matriz[local][j]='x';
                    }
                    if(matriz[i][j]=='p'&&matriz[i-1][j-1]=='b'&&matriz[i-2][j-2]=='0'){
                        matriz[i-2][j-2]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i-1][j-1]=='b'&&matriz[i-2][j-2]=='b'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t-2][r-2]=='b'&&matriz[t-3][r-3]=='0'){
                                    local=t-3;
                                    local2=r-3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                    if(matriz[i][j]=='p'&&matriz[i+1][j+1]=='b'&&matriz[i+2][j+2]=='0'){
                        matriz[i+2][j+2]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i+1][j+1]=='b'&&matriz[i+2][j+2]=='b'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t+2][r+2]=='b'&&matriz[t+3][r+3]=='0'){
                                    local=t+3;
                                    local2=r+3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                    if(matriz[i][j]=='p'&&matriz[i-1][j+1]=='b'&&matriz[i-2][j+2]=='0'){
                        matriz[i-2][j+2]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i-1][j+1]=='b'&&matriz[i-2][j+2]=='b'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t-2][r+2]=='b'&&matriz[t-3][r+3]=='0'){
                                    local=t-3;
                                    local2=r+3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                    if(matriz[i][j]=='p'&&matriz[i+1][j-1]=='b'&&matriz[i+2][j-2]=='0'){
                        matriz[i+2][j-2]='x';
                    }else if(matriz[i][j]=='p'&&matriz[i+1][j-1]=='b'&&matriz[i+2][j-2]=='b'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t+2][r+2]=='b'&&matriz[t+3][r-3]=='0'){
                                    local=t+3;
                                    local2=r-3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                }
            }
            imprimir_matriz(&*matriz);
            vez=2;
            printf("Turno: %d",turno);
            turno++;
            jogada_B(&*B,&*A,&*matriz);
            placar(&*matriz,&*A,&*B);
            matriz_reset(&*matriz);
        }else if(vez==2&&B->cor=='b'){
            for(i=0;i<8;i++){
                for(j=0;j<8;j++){//Cada if abaixo checa cada uma das direçoes da matriz a partir de um ponto, e ainda checa se cada cor oposta se encontra com um espaço em branco('0').
                    if(matriz[i][j]=='b'&&matriz[i+1][j]=='p'&&matriz[i+2][j]=='0'){
                        matriz[i+2][j]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i+1][j]=='p'&&matriz[i+2][j]=='p'){//testar
                        int local=0;
                        for(int t=j;t<8;t++){
                            if(matriz[t+2][j]=='p'&&matriz[t+3][j]=='0'){//Else if checa a uma linha ou coluna ou vertical que seja em sequencia de cor oposta com espaço livre'0'
                                local=t+3;
                            }
                        }
                        if(local!=0)
                            matriz[local][j]='x';
                    }
                    if(matriz[i][j]=='b'&&matriz[i][j+1]=='p'&&matriz[i][j+2]=='0'){
                        matriz[i][j+2]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i][j+1]=='p'&&matriz[i][j+2]=='p'){//testar
                        int local=0;
                        for(int t=j;t<8;t++){
                            if(matriz[i][t+2]=='p'&&matriz[i][t+3]=='0'){
                                local=t+3;
                            }
                        }
                        if(local!=0)
                            matriz[i][local]='x';
                    }
                    if(matriz[i][j]=='b'&&matriz[i][j-1]=='p'&&matriz[i][j-2]=='0'){
                        matriz[i][j-2]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i][j-1]=='p'&&matriz[i][j-3]=='p'){//testar
                        int local=0;
                        for(int t=j;t<8;t++){
                            if(matriz[i][t-2]=='p'&&matriz[i][t-3]=='0'){
                                local=t-3;
                            }
                        }
                        if(local!=0)
                            matriz[i][local]='x';
                    }
                    if(matriz[i][j]=='b'&&matriz[i-1][j]=='p'&&matriz[i-2][j]=='0'){
                        matriz[i-2][j]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i-1][j]=='p'&&matriz[i-2][j]=='p'){//testar
                        int local=0;
                        for(int t=j;t<8;t++){
                            if(matriz[t-2][j]=='p'&&matriz[t-3][j]=='0'){
                                local=t-3;
                            }
                        }
                        if(local!=0)
                            matriz[local][j]='x';
                    }
                    if(matriz[i][j]=='b'&&matriz[i-1][j-1]=='p'&&matriz[i-2][j-2]=='0'){
                        matriz[i-2][j-2]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i-1][j-1]=='p'&&matriz[i-2][j-2]=='p'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t-2][r-2]=='b'&&matriz[t-3][r-3]=='0'){
                                    local=t-3;
                                    local2=r-3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                    if(matriz[i][j]=='b'&&matriz[i+1][j+1]=='p'&&matriz[i+2][j+2]=='0'){
                        matriz[i+2][j+2]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i+1][j+1]=='p'&&matriz[i+2][j+2]=='p'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t+2][r+2]=='p'&&matriz[t+3][r+3]=='0'){
                                    local=t+3;
                                    local2=r+3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                    if(matriz[i][j]=='b'&&matriz[i-1][j+1]=='p'&&matriz[i-2][j+2]=='0'){
                        matriz[i-2][j+2]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i-1][j+1]=='p'&&matriz[i-2][j+2]=='p'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t-2][r+2]=='p'&&matriz[t-3][r+3]=='0'){
                                    local=t-3;
                                    local2=r+3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                    if(matriz[i][j]=='b'&&matriz[i+1][j-1]=='p'&&matriz[i+2][j-2]=='0'){
                        matriz[i+2][j-2]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i+1][j-1]=='p'&&matriz[i+2][j-2]=='p'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t+2][r-2]=='p'&&matriz[t+3][r-3]=='0'){
                                    local=t+3;
                                    local2=r-3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                }
            }
            imprimir_matriz(&*matriz);
            vez=1;
            printf("Turno: %d",turno);
            turno++;
            jogada_B(&*B,&*A,&*matriz);
            placar(&*matriz,&*A,&*B);
            matriz_reset(&*matriz);
        }else if(vez==2&&A->cor=='b'){
            for(i=0;i<8;i++){
                for(j=0;j<8;j++){//Cada if abaixo checa cada uma das direçoes da matriz a partir de um ponto, e ainda checa se cada cor oposta se encontra com um espaço em branco('0').
                    if(matriz[i][j]=='b'&&matriz[i+1][j]=='p'&&matriz[i+2][j]=='0'){
                        matriz[i+2][j]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i+1][j]=='p'&&matriz[i+2][j]=='p'){//testar
                        int local=0;
                        for(int t=j;t<8;t++){
                            if(matriz[t+2][j]=='p'&&matriz[t+3][j]=='0'){//Else if checa a uma linha ou coluna ou vertical que seja em sequencia de cor oposta com espaço livre'0'
                                local=t+3;
                            }
                        }
                        if(local!=0)
                            matriz[local][j]='x';
                    }
                    if(matriz[i][j]=='b'&&matriz[i][j+1]=='p'&&matriz[i][j+2]=='0'){
                        matriz[i][j+2]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i][j+1]=='p'&&matriz[i][j+2]=='p'){//testar
                        int local=0;
                        for(int t=j;t<8;t++){
                            if(matriz[i][t+2]=='p'&&matriz[i][t+3]=='0'){
                                local=t+3;
                            }
                        }
                        if(local!=0)
                            matriz[i][local]='x';
                    }
                    if(matriz[i][j]=='b'&&matriz[i][j-1]=='p'&&matriz[i][j-2]=='0'){
                        matriz[i][j-2]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i][j-1]=='p'&&matriz[i][j-2]=='p'){//testar
                        int local=0;
                        for(int t=j;t<8;t++){
                            if(matriz[i][t-2]=='p'&&matriz[i][t-3]=='0'){
                                local=t-3;
                            }
                        }
                        if(local!=0)
                            matriz[i][local]='x';
                    }
                    if(matriz[i][j]=='b'&&matriz[i-1][j]=='p'&&matriz[i-2][j]=='0'){
                        matriz[i-2][j]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i-1][j]=='p'&&matriz[i-2][j]=='p'){//testar
                        int local=0;
                        for(int t=j;t<8;t++){
                            if(matriz[t-2][j]=='p'&&matriz[t-3][j]=='0'){
                                local=t-3;
                            }
                        }
                        if(local!=0)
                            matriz[local][j]='x';
                    }
                    if(matriz[i][j]=='b'&&matriz[i-1][j-1]=='p'&&matriz[i-2][j-2]=='0'){
                        matriz[i-2][j-2]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i-1][j-1]=='p'&&matriz[i-2][j-2]=='p'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t-2][r-2]=='p'&&matriz[t-3][r-3]=='0'){
                                    local=t-3;
                                    local2=r-3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                    if(matriz[i][j]=='b'&&matriz[i+1][j+1]=='p'&&matriz[i+2][j+2]=='0'){
                        matriz[i+2][j+2]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i+1][j+1]=='p'&&matriz[i+2][j+2]=='p'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t+2][r+2]=='p'&&matriz[t+3][r+3]=='0'){
                                    local=t+3;
                                    local2=r+3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                    if(matriz[i][j]=='b'&&matriz[i-1][j+1]=='p'&&matriz[i-2][j+2]=='0'){
                        matriz[i-2][j+2]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i-1][j+1]=='p'&&matriz[i-2][j+2]=='p'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t-2][r+2]=='p'&&matriz[t-3][r+3]=='0'){
                                    local=t-3;
                                    local2=r+3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                    if(matriz[i][j]=='b'&&matriz[i+1][j-1]=='p'&&matriz[i+2][j-2]=='0'){
                        matriz[i+2][j-2]='x';
                    }else if(matriz[i][j]=='b'&&matriz[i+1][j-1]=='p'&&matriz[i+2][j-2]=='p'){//testar
                        int local=0,local2=0;
                        for(int t=i;t<8;t++){
                            for(int r=j;r<8;r++){
                                if(matriz[t+2][r-2]=='p'&&matriz[t+3][r-3]=='0'){
                                    local=t+3;
                                    local2=r-3;
                                }
                            }
                        }
                        if(local!=0)
                            matriz[local][local2]='x';
                    }
                }
            }
            imprimir_matriz(&*matriz);
            vez=1;
            printf("Turno: %d",turno);
            turno++;
            jogada_A(&*A,&*B,&*matriz);
            placar(&*matriz,&*A,&*B);
            matriz_reset(&*matriz);
        }
    }

}
void jogada_A(jogador *A,jogador *B,char matriz[][8]){
    char posicion[3];
    int i,j,v;
    char t='A';
    v=0;
    printf(" Jogador:A %s Cor:%c",A->nome,A->cor);
    while(v==0){
        printf("\nPosicao valida: ");
        for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                if(matriz[i][j]=='x'){
                    t='A';
                    printf(" %d%c ",i,t+j);//Mostra a posição valida para jogar
                }
            }
        }
        printf("\nEscolha a posicao: ");
        setbuf(stdin,NULL);
        gets(posicion);
        for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                if(matriz[i][j]=='x'){
                    t='A';
                    if(posicion[0]-48==i&&posicion[1]==t+j){//Faz a comparação convertendo char em int atrazes da inverção da tabela ascii
                        matriz[i][j]=A->cor;//Coloca a cor do jogador na posiçao escolhida
                        if(matriz[i][j]==A->cor&&matriz[i-1][j]==B->cor&&matriz[i-2][j]==A->cor){//checa se a posiçao anterior a escolhida e da cor do oponente
                            matriz[i-1][j]=A->cor;
                        }else if(matriz[i][j]==A->cor&&matriz[i-1][j]==B->cor&&matriz[i-2][j]==B->cor){//Procura se a linha escolhida e uma sequencia de cor oponente
                            int z=1;
                            while(matriz[i][j]==A->cor&&matriz[i-z][j]==B->cor){
                                z++;
                            }
                            if(matriz[i-z+1][j]==B->cor&&matriz[i-z][j]==A->cor){//pinta toda a linha ou coluna ou vertical da cor do oponente quando tem uma cor do jogador no final
                                for(int x=1;x<=z;x++){
                                    matriz[i-x][j]=A->cor;
                                }
                            }
                        }
                        if(matriz[i+1][j]==B->cor&&matriz[i+2][j]==A->cor){
                            matriz[i+1][j]=A->cor;
                        }else if(matriz[i][j]==A->cor&&matriz[i+1][j]==B->cor&&matriz[i+2][j]==B->cor){
                            int z=1;
                            while(matriz[i][j]==A->cor&&matriz[i+z][j]==B->cor){
                                z++;
                            }
                            if(matriz[i+z-1][j]==B->cor&&matriz[i+z][j]==A->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i+x][j]=A->cor;
                                }
                            }
                        }
                        if(matriz[i][j-1]==B->cor&&matriz[i][j-2]==A->cor){
                            matriz[i][j-1]=A->cor;
                        }else if(matriz[i][j]==A->cor&&matriz[i][j-1]==B->cor&&matriz[i][j-2]==B->cor){
                            int z=1;
                            while(matriz[i][j]==A->cor&&matriz[i][j-z]==B->cor){
                                z++;
                            }
                            if(matriz[i][j-z+1]==B->cor&&matriz[i][j-z]==A->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i][j-x]=A->cor;
                                }
                            }
                        }
                        if(matriz[i][j+1]==B->cor&&matriz[i][j+2]==A->cor){
                            matriz[i][j+1]=A->cor;
                        }else if(matriz[i][j]==A->cor&&matriz[i][j+1]==B->cor&&matriz[i][j+2]==B->cor){
                            int z=1;
                            while(matriz[i][j]==A->cor&&matriz[i][j+z]==B->cor){
                                z++;
                            }
                            if(matriz[i][j+z-1]==B->cor&&matriz[i][j+z]==A->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i][j+x]=A->cor;
                                }
                            }
                        }
                        if(matriz[i+1][j+1]==B->cor&&matriz[i+2][j+2]==A->cor){
                            matriz[i+1][j+1]=A->cor;
                        }else if(matriz[i][j]==A->cor&&matriz[i+1][j+1]==B->cor&&matriz[i+2][j+2]==B->cor){
                            int z=1;
                            while(matriz[i][j]==A->cor&&matriz[i+z][j+z]==B->cor){
                                z++;
                            }
                            if(matriz[i+z-1][j+z-1]==B->cor&&matriz[i+z][j+z]==A->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i+x][j+x]=A->cor;
                                }
                            }
                        }
                        if(matriz[i+1][j-1]==B->cor&&matriz[i+2][j-2]==A->cor){
                            matriz[i+1][j-1]=A->cor;
                        }else if(matriz[i][j]==A->cor&&matriz[i+1][j-1]==B->cor&&matriz[i+2][j-2]==B->cor){
                            int z=1;
                            while(matriz[i][j]==A->cor&&matriz[i+z][j-z]==B->cor){
                                z++;
                            }
                            if(matriz[i+z-1][j-z+1]==B->cor&&matriz[i+z][j-z]==A->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i+x][j-x]=A->cor;
                                }
                            }
                        }
                        if(matriz[i-1][j+1]==B->cor&&matriz[i-2][j+2]==A->cor){
                            matriz[i-1][j+1]=A->cor;
                        }else if(matriz[i][j]==A->cor&&matriz[i-1][j+1]==B->cor&&matriz[i-2][j+2]==B->cor){
                            int z=1;
                            while(matriz[i][j]==A->cor&&matriz[i-z][j+z]==B->cor){
                                z++;
                            }
                            if(matriz[i-z+1][j+z-1]==B->cor&&matriz[i-z][j+z]==A->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i-x][j+x]=A->cor;
                                }
                            }
                        }
                        if(matriz[i-1][j-1]==B->cor&&matriz[i-2][j-2]==A->cor){
                            matriz[i-1][j-1]=A->cor;
                        }else if(matriz[i][j]==A->cor&&matriz[i-1][j-1]==B->cor&&matriz[i-2][j-2]==B->cor){
                            int z=1;
                            while(matriz[i][j]==A->cor&&matriz[i-z][j-z]==B->cor){
                                z++;
                            }
                            if(matriz[i-z+1][j-z+1]==B->cor&&matriz[i-z][j-z]==A->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i-x][j-x]=A->cor;
                                }
                            }
                        }
                        v=1;
                    }
                }
            }
        }
        if(v==0){
            printf("Posicao invalida");
        }
    }

}
void jogada_B(jogador *B,jogador *A,char matriz[][8]){
    char posicion[3];
    int i,j,v;
    char t='A';
    v=0;
    printf(" Jogador:B %s Cor:%c",B->nome,B->cor);
    while(v==0){
        printf("\nPosicao valida: ");
        for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                if(matriz[i][j]=='x'){
                    t='A';
                    printf(" %d%c ",i,t+j);//Mostra a posição valida para jogar
                }
            }
        }
        printf("\nEscolha a posicao: ");
        setbuf(stdin,NULL);
        gets(posicion);
        for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                if(matriz[i][j]=='x'){
                    t='A';
                    if(posicion[0]-48==i&&posicion[1]==t+j){//Faz a comparação convertendo char em int atrazes da inverção da tabela ascii
                        matriz[i][j]=B->cor;//Coloca a cor do jogador na posiçao escolhida
                        if(matriz[i-1][j]==A->cor&&matriz[i-2][j]==B->cor){//checa se a posiçao anterior a escolhida e da cor do oponente
                            matriz[i-1][j]=B->cor;
                        }else if(matriz[i][j]==B->cor&&matriz[i-1][j]==A->cor&&matriz[i-2][j]==A->cor){//Procura se a linha escolhida e uma sequencia de cor oponente
                            int z=1;
                            while(matriz[i][j]==B->cor&&matriz[i-z][j]==A->cor){//pinta toda a linha ou coluna ou vertical da cor do oponente quando tem uma cor do jogador no final
                                z++;
                            }
                            if(matriz[i-z+1][j]==A->cor&&matriz[i-z][j]==B->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i-x][j]=B->cor;
                                }
                            }
                        }
                        if(matriz[i+1][j]==A->cor&&matriz[i+2][j]==B->cor){
                            matriz[i+1][j]=B->cor;
                        }else if(matriz[i][j]==B->cor&&matriz[i+1][j]==A->cor&&matriz[i+2][j]==A->cor){
                            int z=1;
                            while(matriz[i][j]==B->cor&&matriz[i+z][j]==A->cor){
                                z++;
                            }
                            if(matriz[i+z-1][j]==A->cor&&matriz[i+z][j]==B->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i+x][j]=B->cor;
                                }
                            }
                        }
                        if(matriz[i][j-1]==A->cor&&matriz[i][j-2]==B->cor){
                            matriz[i][j-1]=B->cor;
                        }else if(matriz[i][j]==B->cor&&matriz[i][j-1]==A->cor&&matriz[i][j-2]==A->cor){
                            int z=1;
                            while(matriz[i][j]==B->cor&&matriz[i][j-z]==A->cor){
                                z++;
                            }
                            if(matriz[i][j-z+1]==A->cor&&matriz[i][j-z]==B->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i][j-z]=B->cor;
                                }
                            }
                        }
                        if(matriz[i][j+1]==A->cor&&matriz[i][j+2]==B->cor){
                            matriz[i][j+1]=B->cor;
                        }else if(matriz[i][j]==B->cor&&matriz[i][j+1]==A->cor&&matriz[i][j+2]==A->cor){
                            int z=1;
                            while(matriz[i][j]==B->cor&&matriz[i][j+z]==A->cor){
                                z++;
                            }
                            if(matriz[i][j+z-1]==A->cor&&matriz[i][j+z]==B->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i][j+x]=B->cor;
                                }
                            }
                        }
                        if(matriz[i+1][j+1]==A->cor&&matriz[i+2][j+2]==B->cor){
                            matriz[i+1][j+1]=B->cor;
                        }else if(matriz[i][j]==B->cor&&matriz[i+1][j+1]==A->cor&&matriz[i+2][j+2]==A->cor){
                            int z=1;
                            while(matriz[i][j]==B->cor&&matriz[i+z][j+z]==A->cor){
                                z++;
                            }
                            if(matriz[i+z-1][j+z-1]==A->cor&&matriz[i+z][j+z]==B->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i+x][j+x]=B->cor;
                                }
                            }
                        }
                        if(matriz[i-1][j+1]==A->cor&&matriz[i-2][j+2]==B->cor){
                            matriz[i-1][j+1]=B->cor;
                        }else if(matriz[i][j]==B->cor&&matriz[i-1][j+1]==A->cor&&matriz[i-2][j+2]==A->cor){
                            int z=1;
                            while(matriz[i][j]==B->cor&&matriz[i-z][j+z]==A->cor){
                                z++;
                            }
                            if(matriz[i-z+1][j+z-1]==A->cor&&matriz[i-z][j+z]==B->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i-x][j+x]=B->cor;
                                }
                            }
                        }
                        if(matriz[i+1][j-1]==A->cor&&matriz[i+2][j-2]==B->cor){
                            matriz[i+1][j-1]=B->cor;
                        }else if(matriz[i][j]==B->cor&&matriz[i+1][j-1]==A->cor&&matriz[i+2][j-2]==A->cor){
                            int z=1;
                            while(matriz[i][j]==B->cor&&matriz[i+z][j-z]==A->cor){
                                z++;
                            }
                            if(matriz[i+z-1][j-z+1]==A->cor&&matriz[i+z][j-z]==B->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i+x][j-x]=B->cor;
                                }
                            }
                        }
                        if(matriz[i-1][j-1]==A->cor&&matriz[i-2][j-2]==B->cor){
                            matriz[i-1][j-1]=B->cor;
                        }else if(matriz[i][j]==B->cor&&matriz[i-1][j-1]==A->cor&&matriz[i-2][j-2]==A->cor){
                            int z=1;
                            while(matriz[i][j]==B->cor&&matriz[i-z][j-z]==A->cor){
                                z++;
                            }
                            if(matriz[i-z+1][j-z+1]==A->cor&&matriz[i-z][j-z]==B->cor){
                                for(int x=1;x<=z;x++){
                                    matriz[i-x][j-x]=B->cor;
                                }
                            }
                        }
                        v=1;
                    }
                }
            }

        }
        if(v==0){
            printf("Posicao invalida");
        }
    }

}

void matriz_reset(char matriz[][8]){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(matriz[i][j]=='x'){
                matriz[i][j]='0';//So reseta tudo para '0' novamente.
            }
        }
    }
}

int main(){
    jogador A,B;
    char c;
    do{
    printf("Bem vindo ao game OTHELLO\n");
    cadastro_jogador(&A,&B);
    char matriz[8][8];//Cria a matriz de char
    int i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            matriz[i][j]='0';//Preenche ela com '0'.
        }
    }
    srand(time(NULL));//De acordo com o tempo para dar a posiçao Aleatoria a toda inicializaçao
    do{
        i=rand()%2;//Aleatorio a posiçao
    }while(i==0);
    if(i==1){
        A.cor='p';
        B.cor='b';
    }else if(i==2){
        B.cor='p';
        A.cor='b';
    }
    matriz[3][3]='b';
    matriz[3][4]='p';
    matriz[4][3]='p';
    matriz[4][4]='b';
    imprimir_cadastro(&A,&B);
    imprimir_matriz(&matriz);
    movimento(&A,&B,&matriz);
    imprimir_matriz(&matriz);
    vencedor(&A,&B);
    fflush(stdin);
    printf("Deseja jogar novamente?(s)Sim ou (n)Nao");
    }while(getchar()=='s');//Função para pedir uma letra do teclado para checar se deve executar novamente.
    return 0;
}
