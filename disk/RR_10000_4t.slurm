#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-RR-10000-4.out
./DISKFIN disk-RR-10000-4thread.dat
