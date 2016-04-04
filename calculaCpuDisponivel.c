int calculaCapacidadeCPU(int cpServidor,int cpRequisicao){
	int novaCpServidor = cpServidor - cpRequisicao;
	return novaCpServidor;
}
