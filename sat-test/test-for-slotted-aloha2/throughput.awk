BEGIN {
	success_pkts=0;
	sent_pkts=0;
}
{

 	action = $1;
    	time = $2;
    	src_node = $3;
    	dst_node = $4;
    	pkt_type = $5;
    	pktsize = $6;
    	flow_id = $8;
    	src_node_port = $9;
    	dst_node_port = $10;
    	seq_no = $11;
    	pkt_id = $12;

	if(action=="-"  ){

			a[pkt_id] = 1;
			sent_pkts ++;

	}

    	if(action=="r" ){
    		success_pkts ++;
    	}
	st = time - 1;
}
END{
	printf("%.4f\t",st);
	printf("%d\t",sent_pkts);
	printf("%d\t",success_pkts);	
	printf("\n");
}
