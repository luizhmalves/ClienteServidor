int atualizaCpu(int cpCpu, int cpReq, int op){
	int novaCpu;
	if(op == 1){
		novaCpu = cpCpu + cpReq;
	}else if(op == 2){
		novaCpu = cpCpu - cpReq;
	}
	return novaCpu;
}
