#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-RS-10000-1.out
./DISKFIN disk-RS-10000-1thread.dat
