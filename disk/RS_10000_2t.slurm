#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-RS-10000-2.out
./DISKFIN disk-RS-10000-2thread.dat
