while true; do
	./gen;./tree;./bf
	if diff tree.out bf.out; then
		echo AC
	else
		echo WA
		exit 0
	fi
done