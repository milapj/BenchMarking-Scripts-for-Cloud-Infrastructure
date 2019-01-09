#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-RS-100000-1.out
./DISKFIN disk-RS-100000-1thread.dat
