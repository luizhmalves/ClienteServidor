int calculaCapacidadeMemoria(int cpServidor, int cpRequisicao){
	int novaCpServidor;
	novaCpServidor = cpServidor - cpRequisicao;
	return novaCpServidor;
}
