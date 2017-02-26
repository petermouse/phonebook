reset
set ylabel 'time(sec)'
set style fill solid
# set key outside
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][:0.06]'output.txt' using 2:xtic(1) with histogram title 'original', \
'' using 3:xtic(1) with histogram title 'reduced size', \
'' using 4:xtic(1) with histogram title 'redeced size + BST', \
'' using 5:xtic(1) with histogram title 'reduced size + hash(djb2)', \
'' using ($0-0.2):($2+0.001):2 with labels title ' ', \
'' using ($0-0.0):($3+0.001):3 with labels title ' ', \
'' using ($0+0.15):($4+0.001):4 with labels title ' ', \
'' using ($0+0.35):($5+0.0025):5 with labels title ' '
