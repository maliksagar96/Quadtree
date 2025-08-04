cd ../build
rm quadtree
make -j6
clear
make
cd ../test
../build/quadtree
python3 plot_quatree.py