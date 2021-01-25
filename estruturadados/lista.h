struct processo{
    float tempo;
    int id;
} typedef Processo;

typedef struct elemento* Lista;

Lista* criar_lista();
void destruir_lista(Lista* lista);

int insere_fim(Lista* lista, Processo p);
int remove_inicio(Lista* lista);

int tamanho_lista(Lista* lista);
Processo obter_processo(Lista* lista, int pos);
