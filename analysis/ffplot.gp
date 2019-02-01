reset

set term postscript eps enhanced
set output 'ffenergy.eps'

set size 1,1

set title 'Force Field Energies'
set ylabel 'Energies'
set xlabel 'Bond Distance'

plot [:] [:500] 'GAFF.dat' title 'GAFF'
print GPVAL_DATA_Y_MIN

plot [:] [:500] 'GHEMICAL.dat' title 'GHEMICAL'
print GPVAL_DATA_Y_MIN

plot [:] [:500] 'MMFF94.dat' title 'MMFF94'
print GPVAL_DATA_Y_MIN

plot [:] [:500] 'MMFF94s.dat' title 'MMFF94s'
print GPVAL_DATA_Y_MIN

plot [:] [:500] 'UFF.dat' title 'UFF'
print GPVAL_DATA_Y_MIN
