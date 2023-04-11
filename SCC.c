#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 50
#define HEIGHT 70

void ControleJanela(){
    HANDLE Window;
    DWORD dwWidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD dwHeight = GetSystemMetrics(SM_CYSCREEN);
    SMALL_RECT windowSize = {0, 0, dwWidth, dwHeight };
    COORD bufferSize = { WIDTH , HEIGHT };
    Window = GetStdHandle(STD_OUTPUT_HANDLE);


    SetConsoleTitle("SCC: Sistema de controle de covid");
    SetConsoleWindowInfo(Window, 1, &windowSize);
    SetConsoleScreenBufferSize(Window, bufferSize);

}

int LoginUsuario(char *a, char *b){
    if ((strcmp(a, "Unip")==0) && (strcmp(b, "Epsilon")==0))
        {return 1;}
    else
        {return 0;}
};

int DadosPacienteGeral (const char *text, char *D, int Key){
	if (Key == 0)    	
	{
	FILE *PacienteGeral;
    	PacienteGeral = fopen("Paciente Geral.txt", "a+");
    	fputs(text, PacienteGeral);
    	fputs(D, PacienteGeral);
    	fclose(PacienteGeral);
	}
    	else if(Key == 1)
        {
        FILE *GrupoRisco;
        GrupoRisco = fopen("Grupo de risco.txt", "a+");
        fputs(text, GrupoRisco);
        fputs(D, GrupoRisco);
        fclose(GrupoRisco);
        };

};

int CalcularIdade(){
    int a;
    scanf("%d",&a);
    struct tm *data;
    time_t segundos;
    time(&segundos);
    data = localtime(&segundos);
    return data->tm_year+1900 - a;
};

#define MAX_NAME_SZ 256

void main()
    {
    ControleJanela();
    int ControleMenu1 = 0, ControleMenu2 = 0;
    char User[21],Senha[21];

    printf("\n-------------------\n[Bem vindo ao SCC]\n-------------------\n");

    while (ControleMenu1 == 0)
        {
        printf("Login de acesso\nUsuario: ");
        scanf(" %s", &User);
        printf("Senha: ");
        scanf(" %s", &Senha);
        if (LoginUsuario(User,Senha) == 1)
            {
            ControleMenu1 = 1;
            ControleMenu2 = 1;
            }
        else
            {
            printf("\nSenha incorreta, digite [0] para tentar novamente.\nEncerrar o programa digite qualquer numero: ");
            scanf("%d",&ControleMenu1);
            system("cls");
            }
        }

    char DadosGeral[8][120];
    int IdadeInt, Contr;
    char Idade[3];

    while (ControleMenu2==1){
        system("cls");
        printf("\n----------------------\n[Cadastrar o paciente]\n----------------------\nNome: ");
        scanf(" %120[^\n]s", &DadosGeral[0]);
        DadosPacienteGeral("\n-", "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n",0);
        DadosPacienteGeral("\nNome: ", DadosGeral[0], 0);

        printf("CPF: ");
        scanf(" %120[^\n]s", &DadosGeral[1]);
        DadosPacienteGeral("\nCPF: ", DadosGeral[1], 0);

        printf("Telefone: ");
        scanf(" %120[^\n]s", &DadosGeral[2]);
        DadosPacienteGeral("\nTelefone: ", DadosGeral[2], 0);

        printf("Endereco  (numero, rua, bairro, cidade - estado): ");
        scanf(" %120[^\n]s", &DadosGeral[3]); 
        DadosPacienteGeral("\nEndereco: ", DadosGeral[3], 0);

        printf("CEP: ");
        scanf(" %120[^\n]s", &DadosGeral[4]);
        DadosPacienteGeral("\nCEP: ", DadosGeral[4], 0);

        printf("Data Nascimento (DD/MM/AAAA): ");
        scanf(" %120[^\n]s", &DadosGeral[5]);
        printf("Ano de nasciemnto: ");
        IdadeInt = CalcularIdade();
        DadosPacienteGeral("\nData Nascimento: ", DadosGeral[5], 0);
        itoa(IdadeInt, Idade, 10);

        printf("E-mail: ");
        scanf(" %120[^\n]s", &DadosGeral[6]);
        DadosPacienteGeral("\nE-mail: ", DadosGeral[6], 0);

        printf("Data de diagnostico(DD/MM/AAAA): ");
        scanf(" %120[^\n]s", &DadosGeral[7]);
        DadosPacienteGeral("\nData de diagnostico: ", DadosGeral[7], 0);

        printf("O paciente possui comorbidade ? sim[1] nao[0]");
        scanf(" %d", &Contr);

        if (Contr == 1)
           {
            DadosPacienteGeral("\nPaciente: ", DadosGeral[0], 1);
            DadosPacienteGeral("\nIdade: ", Idade, 1);
            DadosPacienteGeral("\nCEP: ", DadosGeral[4], 1);
            printf("Comorbidade: ");
            scanf(" %120[^\n]s", DadosGeral[8]);
            DadosPacienteGeral("\nComorbidade: ", DadosGeral[8], 0);
            DadosPacienteGeral("\n-", "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n",1);
            }
        else if ((IdadeInt>=65))
            {
            DadosPacienteGeral("\nPaciente: ", DadosGeral[0], 1);
            DadosPacienteGeral("\nIdade: ", Idade, 1);
            DadosPacienteGeral("\nCEP: ", DadosGeral[4], 1);
            DadosPacienteGeral("\nComorbidade: ", "Nenhuma declarada\n", 0);
            DadosPacienteGeral("\n-", "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n",1);
            }
        else
            {
            DadosPacienteGeral("\nComorbidade: ", "Nenhuma declarada\n", 0);
            DadosPacienteGeral("-", "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n",0);
            };
        system("cls");
	printf("\nMenu\n\nAdicionar novo paciente [1]\nEncerrar programa digite qualquer numero: ");
        scanf("%d", &ControleMenu2);
        system("cls");
        };
};
