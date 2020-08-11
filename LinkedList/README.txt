Jessalyn Wang (jwang456)

Stopwatch count:
     Selection sort time: 49.981 ms
     Insertion sort time: 25.789 ms
Analysis of stopwatch times:
     Given the stopwatch times, it can be seen that SelectionSort() is slower than InsertionSort(). In a static array
     SelectionSort() would be faster because doing insertions in InsertionSort() would require the indexes of all of the
     following values to be shifted, and on a big list that would cost a lot. However, since we are using linked lists, 
     I expected InsertionSort() to be faster because now insertion does not require all indexes to be shifted. In 
     addition, now that the inefficiencies with insertion do not need to be considered, SelectionSort() iterates way 
     more than InsertionSort() does because it checks every single value with all of its successors while 
     InsertionSort() simply puts a value in its correct place on the list, building the sorted list behind the first 
     unsorted value as it goes.

The lab was an introduction to memory allocation and deallocation, as well as the concept of sorting algorithms and 
linked lists. I think the most important takeaways are the ideas of linked lists and the difference in efficiencies in
the sorting algorithms. Learning how to allocate and deallocate memory was also important. Also, we learned a cool
feature of MPLABX that allows us to check the time it takes our code to run (stopwatch).

My approach to the lab was pretty stereotypical. I wrote the code out for LinkedList.c as well as LinkedListTest.c then
I waited until after the next autograder run to confirm that LinkedList passed the automated tests before writing sort.c
I wrote sort.c using the pseudocode given, took the stopwatch times, and was finished. Nothing went wrong with the lab,
the concept of the doubly linked list was easy enough to understand and the wasn't challenging when converting from
concept to code. The same goes for the sorting methods. I would approach the lab the same if I did it again.

I ended up spending about three hours doing this lab, and I think it went well. I liked learning about linked lists and
learning how to implement them. I think it was definitely a worthwile lab although I do wish there was a little bit more
to the sorting algorithms. I think it would have made the lab more challening/interesting if pseudocode for the sorting
algorithms was not given and we had to figure it out ourselves. Also, it would have been cool if we experimented with
more sortng algorithms, such as Bubble sort or Quicksort. I think discussion was not necessary for this lab, as the 
instructions were very clear, though it has helped me with clarifications in the past!
