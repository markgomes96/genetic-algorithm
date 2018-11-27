reset

set term postscript eps enhanced
set output 'ffenergy.eps'

set size 1,1

set title 'Force Field Energies'
set ylabel 'Energies'
set xlabel 'Bond Distance'

stats 'GAFF.dat' using 2 nooutput name 'Y_'
stats 'GAFF.dat' using 1 every ::Y_index_min::Y_index_min nooutput
X_min = STATS_min

set label 1 sprintf("%.2f", Y_min) center at first X_min,Y_min point pt 7 ps 1 offset 0,-1.5
plot [:] [:500] 'GAFF.dat' title 'GAFF'

print GPVAL_DATA_Y_MIN
min_y = GPVAL_DATA_Y_MIN
set label 1 gprintf("Minimum = %g", min_y) at 2, min_y-50

plot [:] [:500] 'GHEMICAL.dat' title 'GHEMICAL'
print GPVAL_DATA_Y_MIN

plot [:] [:500] 'MMFF94.dat' title 'MMFF94'
print GPVAL_DATA_Y_MIN

plot [:] [:500] 'MMFF94s.dat' title 'MMFF94s'
print GPVAL_DATA_Y_MIN

plot [:] [:500] 'UFF.dat' title 'UFF'
print GPVAL_DATA_Y_MIN
