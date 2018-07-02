#include "funcoes.h"

void Solucao(string nome, int m, int n, char tipo)
{
    ifstream ler(nome.c_str(),ifstream::app);    
    if( !ler.is_open())
    {
        cout << "O arquivo não pode ser aberto!";
    }
    
    float **mat_A;
    float **mat_Ab;
    float *vet_B;
    float *vet_C; 
    float *vet_C_Aux; 
    float *vet_Res;
    float *vet_D;
    float z;

    mat_A = Carregar_Matriz(m,n);
    mat_Ab = Carregar_Matriz(m,n+1);
    vet_B = new float[m];
    vet_C = new float[n];
    vet_C_Aux = new float[n];
    vet_D = new float[m];
    vet_Res = new float[n];
        
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            ler >> mat_A[i][j];
        }
    }
    
    for(int i = 0; i<m; i++)
        ler >> vet_B[i];

    for(int i=0; i<n; i++)
            ler >> vet_C[i];
    
    if(tipo == '0')
        for(int i=0; i<n; i++)
            vet_C[i] *= -1;
        

    for(int i = 0; i<m; i++)
            ler >> vet_D[i];
    
    ler.close();
    
    bool otima = false; 
    
    Preenche_Mat_Ab(mat_A,vet_B,mat_Ab,m,n);
    
    int iteracoes = 0;

    while(otima==false)
    {
        z = Calcular_Z(vet_B,vet_C,vet_D,m);
        Calcular_Custo(vet_C_Aux,vet_C,mat_Ab,vet_D,n,m);
        otima = Verifica_Otimizacao(vet_C_Aux,n);
        if(otima)
            break;        
        int entra = Quem_Entra(vet_C_Aux,n);
        int sai = Quem_Sai(mat_Ab,vet_D,entra,n,m); 
        Pivoteamento(mat_Ab,vet_B,m,n,sai,entra);        
        iteracoes ++;
    }
    Resultados(vet_Res,vet_D,vet_B,z,iteracoes,m,n);
}

void Det_Dimensoes(string nome, int &linhas, int &colunas)
{
    FILE *arquivo = fopen(nome.c_str(), "r");
    
    char caractere;
    
    while((caractere = fgetc(arquivo)) != EOF)
    {
        if(linhas == 0)
        {
            if(caractere != '\n')
            {
                if(caractere == ' ')
                    colunas++;
            }
        }
        
        if(caractere == '\n')
            linhas++;            
    }
    
    linhas -= 6;
    colunas += 1;

}

float **Carregar_Matriz(int m, int n)
{
    float **mat;
    int i;
    
    if(m<1 || n<1)
    {
        cout << "Erro: Parametro invalido!" << endl;
        return 0;
    }
    
    mat = new float*[m];
    
    if(mat == 0)
    {        
        cout << "Erro: Memoria Insuficiente!" << endl;
        return 0;
    }

    for(i=0; i<m; i++)
    {
        mat[i] = new float[n];

        if(mat[i] == 0)
        {
            cout << "Erro: Memoria Insuficiente!" << endl;
            return 0;
        }
    }
    return mat;
}

void Preenche_Mat_Ab(float **mat_A, float *vet_B, float **&mat_Ab, int lin_A, int col_A)
{
    for(int i=0; i<lin_A; i++)
    {
        for(int j=0; j<col_A; j++)
        {
            mat_Ab[i][j] = mat_A[i][j];
        }
    }
    
    for(int i=0; i<lin_A; i++)
        {
        mat_Ab[i][col_A] = vet_B[i];
        }    
}

void Calcular_Custo(float *&vet_C_Aux, float *vet_C, float **mat_A, float *vet_D, int tam_C, int tam_D)
{
   for(int i=0; i<tam_C; i++)
    {       
        float yb = 0;
        
        for(int j=0; j<tam_D; j++)
        {
           int indice = vet_D[j]-1;
           
          yb += (vet_C[indice] * mat_A[j][i]);
        }
        vet_C_Aux[i] = vet_C[i] - yb;
   }
}

bool Verifica_Otimizacao(float *vet_C_Aux, int tam_C)
{    
    for(int i=0 ; i<tam_C; i++)
    {
        if(vet_C_Aux[i] > 0)
            return false;
    }    
    return true;
}

int Quem_Entra(float *vet_C_Aux, int tam_C)
{
    float x = 0;
    int maior = 0;
    
    for(int i=0 ; i<tam_C; i++)
    {
        if(vet_C_Aux[i] > x)
        {
            x = vet_C_Aux[i];
            maior = i;
        }
    }    
    return maior;    
}

int Quem_Sai(float **mat_Ab, float *&vet_D, int entra, int tam_C, int tam_D)
{
    int sai;
    int indice;
    float menor = -1;
    
    for(int i=0; i<tam_D; i++)
    {
        if(mat_Ab[i][tam_C]/mat_Ab[i][entra] >= 0)
        {
            sai = vet_D[i]-1;
            indice = i;
            menor = mat_Ab[i][tam_C]/mat_Ab[i][entra];
        }
        if(menor != -1)
            break;
        
    }
    for(int i=0; i<tam_D; i++)
    {
        if((mat_Ab[i][tam_C]/mat_Ab[i][entra] < menor) && mat_Ab[i][tam_C]/mat_Ab[i][entra] >= 0)
        {
            sai = vet_D[i]-1;
            indice = i;
            menor = mat_Ab[i][tam_C]/mat_Ab[i][entra]; 
        }
    }
    
    vet_D[indice] = entra+1;
    
    return sai;
}

 void Pivoteamento(float **&mat_Ab, float *&vet_B, int tam_B, int tam_C, int sai, int entra)
{
    int linha;
    float valor;
    
    for(int i=0; i<tam_B; i++)
    {
        if(mat_Ab[i][sai] == 1)
        {
            linha = i;
            break;
        }
    }
    
    valor = mat_Ab[linha][entra];
    
    for(int i =0; i<= tam_C; i++)
    {
        mat_Ab[linha][i] = mat_Ab[linha][i]/valor; 
    }
    
    for(int i=0; i<tam_B; i++)
    {
        float x;
        x = mat_Ab[i][entra];
        
        for(int j=0; j <= tam_C; j++)
        {
            if(i != linha)
            {
            mat_Ab[i][j] -= x*mat_Ab[linha][j];
            }
        }
    }

   for(int i=0; i< tam_B; i++)
    {
       vet_B[i] = mat_Ab[i][tam_C];
    } 
}
 
float Calcular_Z(float *vet_B, float *vet_C, float *vet_D, int tam_B)
{
    float z = 0;
    
    for(int j=0; j<tam_B; j++)
        {
           int indice = vet_D[j]-1;
           z += (vet_C[indice] * vet_B[j]);
        }    
    return z;
}

void Resultados(float *vet_Res, float *vet_D, float *vet_B, float z, int it, int tam_B, int tam_C)
{
    system("clear");
    
    for(int i=0; i<tam_C; i++)
    {
        vet_Res[i] = 0;
    }
    
    for(int i=0; i<tam_B; i++)
    {
        int indice = vet_D[i];
        vet_Res[indice-1] = vet_B[i];
    }

    cout << "RESULTADOS" << endl << endl;
    cout << "Iteracoes: " << it << endl;      
    cout << "Z: " << z << endl; 
    
    for(int i=0; i<tam_C; i++)
    {
        cout << "X" << i+1 << "=" << vet_Res[i] << "  ";
    }
    cout << "\n\n" ;
}

bool Simplex()
{
    bool sair = false;
    string nome_arquivo;
    char tipo = 's';    
    char continuar = '0';

    cout << "--------------------------------------------SIMPLEX------------------------------------------------------" << endl;
    cout << "OBS: o arquivo contendo o problema deve ser colocado no diretorio do programa e seguir o seguinte modelo:" << endl << endl
         << "a1 a2 a3 1 0 0" << endl
         << "a4 a5 a6 0 1 0" << endl
         << "a7 a8 a9 0 0 1" << endl << endl
         << "b1 b2 b3" << endl << endl
         << "c1 c2 c3 c4 c5 c6" << endl << endl
         << "4 5 6" << endl
         << "----------------------------------------------------------------------------------------------------------" << endl << endl;
    
     cout << "Continuar(s/n)?";
     cin >> continuar;
     
     if(continuar != 's' && continuar != 'S')
     {
         system("clear");
         cout << "Programa finalizado!" << endl;
         return 0;
     }
     
     system("clear");
     
     while(sair == false)
     {
         int m = 0;
         int n = 0;                  
         
         cout << "Escolha uma das opções: " << endl << endl <<
                 "(1) - Z = Max" << endl <<
                 "(0) - Z = Min" << endl <<
                 "(Qualqer outra tecla) - Sair do programa" << endl << endl <<
                 "Opcao:";
         
         cin >> tipo;
        
        if(tipo != '1' && tipo != '0')
        {
            sair = true;
            break;
        }
         
         cout << "Nome do arquivo:";
         cin >> nome_arquivo;    
         
         Det_Dimensoes(nome_arquivo,m,n);
    
         Solucao(nome_arquivo, m, n, tipo);
        
         cout << "Continuar(s/n)?";
         cin >> continuar;
         
         if(continuar != 's' && continuar != 'S')
         {
             system("clear");
             cout << "Programa finalizado!" << endl;
             return 0;
         }   
         
         system("clear");       
     }

     system("clear"); 
     cout << "Programa finalizado!" << endl;
}