#!bin/bash

echo " # Tranfert de u_n_0.dat, u_np1_20.dat, u_ref_20.dat u_np1_2nd_order_20.dat dans Resultats"
mv u_n_0.dat u_np1_20.dat u_ref_20.dat u_np1_2nd_order_20.dat ../Resultats

rm -rf *.dat