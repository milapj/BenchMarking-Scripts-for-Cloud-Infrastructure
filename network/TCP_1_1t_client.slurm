#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/network-TCP-1-1thread.dat.out
./TCPFIN network-TCP-1-1thread.dat c
