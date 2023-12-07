plot 'u_n_0.dat' title 'Initial condition' with lines, \
    'u_ref_20.dat' title 'Exact solution' with lines, \
    'u_np1_20.dat' title 'First order Upwind solution' with lines, \
    'u_np1_2nd_order_20.dat' title 'Second order Lax-Wendroff solution' with lines
pause -1