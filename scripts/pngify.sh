
for i in $( ls $1/*.tif ); do convert $i "${i%.*}.png"; done
