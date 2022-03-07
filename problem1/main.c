#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef DOLOG
#define LOG(...) fprintf(log, __VA_ARGS__);
#else
#define LOG(...)
#endif

struct array
{
    int *pdata;
    int size;
};

void initArray(struct array *);
void getArray(struct array *);
void arrayCommon(struct array *, struct array *, struct array *);
void printArray(struct array *);
void freeMemory(struct array *, struct array *, struct array *);

void initArray(struct array *arr){
    arr->pdata = NULL;
    arr->size = -1;
}

void printArray(struct array *parr)
{
    for (int i = 0; i < parr->size; i++)
    {
        printf("%d ", parr->pdata[i]);
    }
    printf("\n");
}

void getArray(struct array *parr)
{
    parr->pdata = malloc(50);  //Se asigna la posicion a la memoria en el heap
    char size[10]; //Se asigna el valor maximo de lo que ocupara el arreglo
    char *endptr; //Se define donde se guardaran los valores no utilizados de la cantidad total de caracteres
    long sizeNum; //En esta variable se guarda el numero convertido de los caracteres ingresados del size
    char arrValue[10]; //En este arreglo se guardan los numeros/valores del arreglo
    if (fgets(size, 10, stdin) != NULL) //Se guarda en el arreglo size, el input que ingresa el usuario
    {
        sizeNum = strtol(size, &endptr, 10); //Se convierte el input de caracteres a numeros, en este caso en un long
        parr->size = sizeNum; //Se asigna a la variable size del struct, en la posicion de memoria, lo que ingreso el usuario
        for(int i = 0; i < sizeNum; i++) //Se crea un ciclo para ingresar cada valor del arreglo principal
        {
            fgets(arrValue, 10, stdin); //Se lee el input y se guarda en arrValue
            *(parr->pdata + i) = strtol(arrValue, &endptr, 10); //Se convierte el input en caracteres a numeros, y se asigna en la posicion de memoria
        }
    }
    
}

void arrayCommon(struct array *arrIn1, struct array *arrIn2, struct array *arrOut)
{
    arrOut->pdata = malloc(50); //Se asigna la posicion a la memoria en el heap, del arreglo donde se guardara la interseccion
    int pos = 0, a = 0; //Se inicializa la posicion del size en 0, y a como variable temporal para despues asignar los valores de arrOut
    for (int i = 0; i < arrIn1->size; i++) //Se crea un ciclo para leer los valores de arrIn1
    {
        for (int j = 0; j < arrIn2->size; j++) //Se crea un ciclo para leer los valores de arrIn2
        {
            if (*(arrIn1->pdata + i) == *(arrIn2->pdata + j)) //Se comparan los valores de arrIn2 para cada valor de arrIn1, para saber si son iguales o no
            {
                for (int k = 0; k < pos; k++){ if (*(arrOut->pdata + k) == *(arrIn1->pdata + i)){ a = 1; } } //En caso de ser iguales se revisa en los valores guardados en arrOut si el valor ya esta para no repetir
                if (a != 1) { *(arrOut->pdata + pos) = *(arrIn1->pdata + i); pos++;} //Si no esta ya guardado el valor en arrOut, se guarda y se aumenta en uno la variable pos, que luego sera el size
                a = 0; //Se reinicia la variable a, que define si estuvo repetido el numero o no
            }
            
        }        
    }
    arrOut->size = pos; //Se asigna a la variable size del struct, en la posicion de memoria, el valor que hay en pos, que contiene la cantidad de datos en arrOut
    
}

void freeMemory(struct array *arr1, struct array *arr2, struct array *arr3)
{
    free(arr1->pdata);
    free(arr1);

    free(arr2->pdata);
    free(arr2);

    free(arr3->pdata);
    free(arr3);
}

int main(void)
{

#ifdef DOLOG
    FILE *log = fopen("log", "w");
    if (log == NULL)
    {
        perror("log file creation fails: ");
        return EXIT_FAILURE;
    }
#endif

    char commandBuf[64];

    LOG("creating an object for each array\n");

    struct array *arr1 = malloc(sizeof(struct array) * 1);
    initArray(arr1);
    struct array *arr2 = malloc(sizeof(struct array) * 1);
    initArray(arr2);    
    struct array *arr3 = malloc(sizeof(struct array) * 1);
    initArray(arr3);


    LOG("Init command loop\n");

    while (fgets(commandBuf, sizeof(commandBuf), stdin) != NULL)
    {
        commandBuf[strlen(commandBuf) - 1] = 0;

        if (strncmp(commandBuf, "arr1", strlen("arr1")) == 0)
        {
            LOG("getting array1\n");
            getArray(arr1);
        }
        else if (strncmp(commandBuf, "arr2", strlen("arr2")) == 0)
        {
            LOG("getting array2\n");
            getArray(arr2);
        }
        else if (strncmp(commandBuf, "printArr1", strlen("printArr1")) == 0)
        {
            LOG("printing arr1\n");
            printArray(arr1);
        }
        else if (strncmp(commandBuf, "printArr2", strlen("printArr2")) == 0)
        {
            LOG("printing arr2\n");
            printArray(arr2);
        }
        else if (strncmp(commandBuf, "compare", strlen("compare")) == 0)
        {
            LOG("Compare arrays\n");
            arrayCommon(arr1, arr2, arr3);
        }
        else if (strncmp(commandBuf, "printResult", strlen("printResult")) == 0)
        {
            LOG("printing compare result\n");
            printf("%d\n", arr3->size);
            if (arr3->size != 0)
            {
                printArray(arr3);
            }
        }
        else if (strncmp(commandBuf, "exit", strlen("exit")) == 0)
        {
            LOG("running exit command\n");
            freeMemory(arr1,arr2,arr3);
            break;
        }
    }

    return EXIT_SUCCESS;
}
