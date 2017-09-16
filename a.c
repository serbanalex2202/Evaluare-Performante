#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 100

long long int N;
long long int mediana;    //mediana numerelor din fisierul creat
long long int abatere;    //abaterea de la stadard


/*
    O implementare recursiva -> foloseste mai mult stiva
*/
int hash(int i, char * sir){

    if (i == 0){
        return strlen(sir);
    }

    //ca sa nu fie out of bounds [i % strlen(sir)]
    return hash(i - 1, sir) * 31 + (int)sir[i % strlen(sir)];
}

//1. creaza fisier cu numere
void fisier_numere(){

    char * nume = "ser";
    char sir[SIZE];
    char str_i[SIZE];
    int numar = 0, i; 
    int * list = (int *)malloc(N * sizeof(int));
    FILE *fp;

    //cream fisier cu N numere
    for (i = 0; i < N; ++i) {

        //convertim index la char *
        sprintf(str_i, "%d", i);

        //concatenam numele
        strcat(sir, nume);

        //concatenam i
        strcat(sir, str_i);        

        //obtinerm numarul recursiv (varianta recursiva nu era optima)
        //numar = hash(i, sir) % N;

	//mai optim
	if(i == 0){
		numar = (int)(strlen(sir) % N) ;
	}else{
		numar = ( numar * 31 + (int)sir[i % strlen(sir)] ) % N;
	}

        //punem numarul in lista
        list[i] = numar;

        //reinitializam stringul de concatenare 
        sir[0] = '\0';    //sau memset(sir, 0, SIZE); dar nu e la fel de optim

    }

    fp = fopen("test.txt", "w");

    for (i = 0; i < N; ++i) {

	//scriem numarul in fisier si adaugam un spatiu
        fprintf(fp, "%d ", list[i]);

    }

    //inchidem fisierul
    fclose(fp);
    free(list);

}


//sursa https://discuss.codechef.com/questions/1489/find-median-in-an-unsorted-array-without-sorting-it
int partitions(int low, int high, int * list)
{
    int j, deviatie_i;
    int p = low, r = high , x = list[r], i = p - 1;

    for(j = p; j <= r - 1; j++){

        if (list[j] <= x)
        {
            i = i + 1;
            deviatie_i = list[j];
            list[j] = list[i];
            list[i] = deviatie_i;
            
        }
    }

    deviatie_i = list[j];
    list[j] = list[i];
    list[i] = deviatie_i;
            
    return i + 1;
}


int selection_algorithm(int left,int right,int kth, int * list)
{
    for(;;)
    {
        int pivotIndex = partitions(left,right, list);  //Select the Pivot Between Left and Right
        int len = pivotIndex - left + 1;

        if(kth == len) 
            return list[pivotIndex];

        else if(kth < len)
            right = pivotIndex - 1;

        else
        {
            kth = kth - len; 
            left = pivotIndex + 1;
        }
    }
}


//2. calculeaza mediana pentru numerele din acel fisier
void calcul_mediana(){

    //deschide fisier pentru citire
    FILE *fp = fopen("test.txt", "r");
    int i;
    int * list = (int *)malloc(N * sizeof(int));

    if(fp == NULL){
        printf("nu am putut citi fisierul cu numere");
        return ;
    }

    //citeste numerele din fisier in lista
    for (i = 0; i < N; ++i){
        fscanf(fp, "%d", &list[i]);
    }

    /*
        mediana reprezinta numarul din mijloc al unei liste sortate, mediana = list[N/2]
        in cazul in care lista are un numar par de elemnte in mijloc se vor afla 2 numere,
        in acest caz mediana = media lor
        dar se poate calcula mediana fara a sorta lista in complexitate O(n)
    */
    mediana = selection_algorithm(1, N, N/2, list);

    //inchidem fisierul
    fclose(fp);
    free(list);

}

//3. abaterea de la standard, conform wiki
void abatere_standard(){
    
    FILE *fp = fopen("test.txt", "r");
    int deviatie_i, deviatie_i_2, medie;
    int i;
    int dispersie;
    long long int suma_numere = 0, suma_deviatii = 0;
    int * list = (int *)malloc(N * sizeof(int));    

    if(fp == NULL){
        printf("nu am putut citi fisierul cu numere");
        return ;
    }


    //citeste numerele din fisier in lista
    for (i = 0; i < N; ++i){
        fscanf(fp, "%d", &list[i]);
    }

    //aduna numerele pentru a le face media
    for (i = 0; i < N; ++i){
        suma_numere += list[i];
    }


    medie = suma_numere / N;

    //adunam pentru a face media dispersiei, conform wiki
    for (i = 0; i < N; ++i){
        deviatie_i = list[i] - medie;   //deviations for each data point
        deviatie_i_2 = deviatie_i * deviatie_i;
        suma_deviatii = suma_deviatii + deviatie_i_2 ;
    }


    dispersie = suma_deviatii / N;   //variance
    abatere = sqrt(dispersie);

    fclose(fp);
    free(list);
}


int main(int argc, char ** argv)
{

    if(argc == 2){
        N = atoi(argv[1]);
    }else{
        printf("Eroare : INTRODUCETI N\n\n");
        return -1;
    }

    //1.creaza fisier cu numere
    fisier_numere();
    printf("Am creat fisierul cu numere \n");


    //2.calculeaza mediana
    calcul_mediana();
    printf("Am calculat mediana : %lli\n", mediana);    


    //3.calculeaza abaterea de la standard
    abatere_standard();
    printf("Am calculat abaterea de la standard : %lli\n", abatere); 


    return 0;
    
}
