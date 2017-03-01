reset
set ylabel 'time(sec)'
set style fill solid
#set key outside
set key left top Left reverse
set title 'perfomance comparison (1000 random last names)'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][0:3]'output.txt' using 2:xtic(1) with histogram title 'original', \
'' using 3:xtic(1) with histogram title 'reduced size', \
'' using 4:xtic(1) with histogram title 'redeced size + BST', \
'' using 5:xtic(1) with histogram title 'reduced size + hash(djb2)', \
'' using ($0-0.18):($2+0.05):2 with labels title ' ', \
'' using ($0+0.02):($3+0.16):3 with labels title ' ', \
'' using ($0+0.15):($4+0.06):4 with labels title ' ', \
'' using ($0+0.35):($5+0.15):5 with labels title ' '
