cd ../build
rm quadtree
make -j6
clear
make
cd ../test
../build/quadtree
cat neighbours.txt
python3 plot_quatree.py
