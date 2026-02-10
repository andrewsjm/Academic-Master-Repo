//time ./Sort test0.input 0

real    0m0.494s
user    0m0.482s
sys     0m0.004s
//time./Sort test0.input 1

real    0m0.007s
user    0m0.005s
sys     0m0.000s
//time ./Sort test0.input 2

real    0m0.451s
user    0m0.441s
sys     0m0.005s
The quickest sorting method I found through testing was the quick sort method
I suppose that's what makes it a "qsort", the reason the quicksort is so much quicker than the insertion sort and the regular sort method is mainly due to the notation. 
quicksort O(n log n) divides up the list so that instead of comparing all the numbers at once, it does them in fragmented groups/pairs, which uses much less cpu than Insertion sort (O(n^2)) in which you have to go through iterations sorts/swaps two elements at a time until it is in the proper order 
