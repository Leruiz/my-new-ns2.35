BEGIN {  
highest_packet_id = 0;  
}  
{  
    action = $1;  
    time = $2;  
    node_1 = $3;  
    node_2 = $4;  
    type = $5;  
    flow_id = $8;  
    node_1_address = $9;  
    node_2_address = $10;  
    seq_no = $11;  
    packet_id = $12;  
if ( packet_id > highest_packet_id )  
    highest_packet_id = packet_id;  
if ( start_time[packet_id] == 0 )  
    start_time[packet_id] = time;  
if ( flow_id == 2 && action != "d" ){  
    if ( action == "r" ) {  
        end_time[packet_id] = time;  
}  
} else {  
    end_time[packet_id] = -1;  
}  
}  
END {  
retrans_time = 0;
	for ( packet_id = 0; packet_id <= highest_packet_id; packet_id++ ) {  
		start = start_time[packet_id];  
		end = end_time[packet_id];  
		packet_duration = end - start;   
		
		if ( start < end )
			retrans_time = retrans_time + (end - start) / 0.27;
	}  
	printf("ave_retrans_times\n");
	printf("%f\n", retrans_time / highest_packet_id);

}  