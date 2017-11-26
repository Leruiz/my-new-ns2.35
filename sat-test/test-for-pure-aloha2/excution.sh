#!/bin/bash

filtxt="sat-test/test-for-pure-aloha2/record.txt"
filawk="sat-test/throughput.awk"
filtcl="sat-test/test-for-pure-aloha2/sat-aloha.tcl"

echo "Pure ALOHA" >> $filtxt

echo "num_node = 100  idle_time = 6" >> $filtxt
ns $filtcl poisson 100 6 
awk -f $filawk out.tr >> $filtxt

echo "num_node = 50  idle_time = 2.5" >> $filtxt
ns $filtcl poisson  50 2
awk -f $filawk out.tr >> $filtxt

echo "num_node = 100  idle_time = 2.5" >> $filtxt
ns $filtcl poisson 100 2.5 
awk -f $filawk out.tr >> $filtxt

echo "num_node = 150  idle_time = 2.5" >> $filtxt
ns $filtcl poisson 150 2.5 
awk -f $filawk out.tr >> $filtxt

echo "num_node = 200  idle_time = 2.5" >> $filtxt
ns $filtcl poisson 200 2.5 
awk -f $filawk out.tr >> $filtxt

echo "num_node = 300  idle_time = 2.5" >> $filtxt
ns $filtcl poisson 300 2.5 
awk -f $filawk out.tr >> $filtxt

echo "num_node = 200  idle_time = 1.5" >> $filtxt
ns $filtcl poisson 200 1.5 
awk -f $filawk out.tr >> $filtxt

echo "num_node = 300  idle_time = 1.5" >> $filtxt
ns $filtcl poisson 300 1.5 
awk -f $filawk out.tr >> $filtxt

