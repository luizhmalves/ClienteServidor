//Biblioteca da aplicação

void cliente();
void servidor();
int convAlocCpu(char *arg1);
int convAlocMem(char *arg1);
int convAlocTempo(char *arg1);
void respostaConsulta(char *arg1, int arg2, int arg3);
int randomizaTempo();
int randomizaCpu();
int randomizaMemoria();
void MsgAlocacao(char *arg1);
void* servidorThread(void* arg);
void* atualizaServidor(void* arg);
extern int cpu;
extern int mem;
extern int reqCpu;
extern int reqMem;
