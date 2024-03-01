#!/bin/bash
cd $SLURM_SUBMIT_DIR
# Run our program using OpenMPI.
mpirun a.out
