#!/bin/bash
#SBATCH --nodes=1
#SBATCH --output=output/MyDiskBench-RS-100000-4.out
./DISKFIN disk-RS-100000-4thread.dat
