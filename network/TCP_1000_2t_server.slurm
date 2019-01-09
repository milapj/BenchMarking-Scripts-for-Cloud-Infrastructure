#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/network-TCP-1000-2thread.dat.out
./TCPFIN network-TCP-1000-2thread.dat s
