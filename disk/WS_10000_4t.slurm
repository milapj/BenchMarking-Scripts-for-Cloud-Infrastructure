#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-WS-10000-4.out
./DISKFIN disk-WS-10000-4thread.dat
