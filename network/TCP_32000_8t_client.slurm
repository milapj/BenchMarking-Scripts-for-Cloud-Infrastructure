#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/network-TCP-32000-8thread.dat.out
./TCPFIN network-TCP-32000-8thread.dat c
