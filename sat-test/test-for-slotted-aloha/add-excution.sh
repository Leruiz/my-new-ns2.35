#!/bin/bash

filtxt="sat-test/test-for-pure-aloha2/record.txt"
filawk="sat-test/throughput.awk"
filtcl="sat-test/test-for-pure-aloha2/sat-aloha.tcl"

echo " add low load tests" >> $filtxt

echo "num_node = 100  idle_time = 1" >> $filtxt
ns $filtcl poisson 100 1
awk -f $filawk out.tr >> $filtxt

echo "num_node = 100  idle_time = 2" >> $filtxt
ns $filtcl poisson  100 2
awk -f $filawk out.tr >> $filtxt

echo "num_node = 100  idle_time = 3" >> $filtxt
ns $filtcl poisson 100 3
awk -f $filawk out.tr >> $filtxt


