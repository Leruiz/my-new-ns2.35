#!/bin/bash

filtxt="sat-test/test-for-slotted-aloha/record.txt"
filawk="sat-test/throughput.awk"
filtcl="sat-test/test-for-slotted-aloha/sat-aloha.tcl"

echo "Slotted ALOHA" >> $filtxt
echo "num_node = 100  idle_time = 3" >> $filtxt
ns $filtcl poisson 100 3
awk -f $filawk out.tr >> $filtxt


echo "num_node = 100  idle_time = 2" >> $filtxt
ns $filtcl poisson  100 2
awk -f $filawk out.tr >> $filtxt

echo "num_node = 100  idle_time = 1" >> $filtxt
ns $filtcl poisson 100 1
awk -f $filawk out.tr >> $filtxt

echo "num_node = 100  idle_time = 0.5" >> $filtxt
ns $filtcl poisson 100 0.5
awk -f $filawk out.tr >> $filtxt

echo "num_node = 200  idle_time = 0.5" >> $filtxt
ns $filtcl poisson  200 0.5
awk -f $filawk out.tr >> $filtxt

echo "num_node = 300  idle_time = 0.5" >> $filtxt
ns $filtcl poisson 300 0.5
awk -f $filawk out.tr >> $filtxt

echo "num_node = 400  idle_time = 0.5" >> $filtxt
ns $filtcl poisson 400 0.5 
awk -f $filawk out.tr >> $filtxt

echo "num_node = 500  idle_time = 0.5" >> $filtxt
ns $filtcl poisson 500 0.5 
awk -f $filawk out.tr >> $filtxt

echo "num_node = 550  idle_time = 0.5" >> $filtxt
ns $filtcl poisson 550 0.5 
awk -f $filawk out.tr >> $filtxt

echo "num_node = 600  idle_time = 0.5" >> $filtxt
ns $filtcl poisson 600 0.5 
awk -f $filawk out.tr >> $filtxt

echo "num_node = 650  idle_time = 0.5" >> $filtxt
ns $filtcl poisson 650 0.5
awk -f $filawk out.tr >> $filtxt

