int atualizaMem(int cpMem, int cpReq, int op){
	int novaMem;
	if(op == 1){
		novaMem = cpMem + cpReq;
	}else if(op == 2){
		novaMem = cpMem - cpReq;
	}
	return novaMem;
}
