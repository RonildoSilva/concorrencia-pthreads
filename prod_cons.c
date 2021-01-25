#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>   
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

#include "estruturadados/lista.h"

#define MAXIMO_OPERACOES 10
#define MAX_COUNT 15
#define NUM_THREAD 4

pthread_mutex_t iniciado = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ocupado  = PTHREAD_COND_INITIALIZER;

sem_t mutex; 

int prod_cont = 0, cons_cont = 0;

static Lista* lista = NULL;

float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX;
    return min + scale * ( max - min );
}

void * consumidor(int *tempo)
{
  // Configura o mutex
  pthread_mutex_lock(&iniciado);

  while(cons_cont < MAXIMO_OPERACOES){
      // Espera a proxima chamada do consumo
      pthread_cond_wait(&ocupado, &iniciado);

      Processo p = obter_processo(lista, 1);
      int id_processo  = remove_inicio(lista);

      printf("Processo [%03d] morto : \t\n", p.id);
    
      // Incrementa operacao
      cons_cont ++;
    
      // Thread dorme
      sem_wait(&mutex); 
      sleep(p.tempo);
  }
  
  pthread_mutex_unlock(&iniciado);
}

void * produtor(int *id)
{

  while (prod_cont < MAXIMO_OPERACOES)
    {
      // Configura o mutex
      pthread_mutex_lock(&iniciado);
      
      // Cria um processo com tempo e id aleatorio
      Processo p = {float_rand(1.0, 6.0), rand()%100};
      
      printf("Processo [%03d] criado: \t %f (s) \n", p.id, p.tempo);
      
      // Insere processo na lista
      insere_fim(lista, p);

      // Incrementa operacao
      prod_cont ++;
      
      // Envio de sinal
      pthread_cond_signal(&ocupado);

      // Destrava a exclusao mutua
      pthread_mutex_unlock(&iniciado);

      // Thread dorme
      sem_post(&mutex); 
	    sleep(p.tempo);

    }
}

int main()
{
  int i = 0;

  // Definição da semente:
  srand((unsigned)time(0));

  // Criação da lista
  lista = criar_lista();

  // Definicao thread
  pthread_t thread[NUM_THREAD];

  for(i=0; i< NUM_THREAD ; i++){
    if(rand()%10 % 2 == 0){
      pthread_create(&thread[i], NULL, (void *)consumidor, &i);
    }else{
      pthread_create(&thread[i], NULL, (void *)produtor, &i);
    }
  }

  for(i=0; i< NUM_THREAD ; i++)
    {
      pthread_join(thread[i], NULL);
    }
}

