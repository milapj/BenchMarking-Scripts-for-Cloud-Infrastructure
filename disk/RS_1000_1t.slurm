#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-RS-1000-1.out
./DISKFIN disk-RS-1000-1thread.dat
