### Introduction

These files are my course homework for advanced data structure in C++.  Below is a summary of each homework description. 

### HW 1: Reversible Stack

Write an integer stack class in C++ that uses a singly linked list internally. It must have the following
public methods: 

* void Push(int item) : Pushes an item onto the top of the stack

* int Pop() : Pops an item off the top of the stack and returns it

* isempty() : Displays either “true” or “false” on a line based on whether the stack is empty or not.

* void Reverse() : Reverses the order of items on the stack by reversing the singly linked list

* void Display(std::ostream& writer) const : Displays the contents of the stack from top to
bottom on one line.

### HW 2&3: String Class Implementation

Write functions for operation of string, including: 

* set(string_value) : Sets the current string

* substr(startindex,length) : Displays a substring from the current string

* indexof(substr,startindex) : Displays an integer that is the starting index of the substring within
the current string.

* bad_char_table : Builds and displays the bad character rule table for the current string

* split(char_separator) : Splits the string based on the specified separating character and
displays each “piece” (substring) on the same line with a comma after each one, including the
last one on the line.

* anagrams(str1,str2,str3,…) : This function must support any number of parameters >= 1.
Compares all strings against the current string and displays only the ones that are anagrams

* suffix_of_length(length) : Displays a suffix of the specified length from the current string

* starts_with(str) : Displays either “true” or “false” (without quotes) based on whether or not the
current string starts with the specified string parameter. This does NOT change the current
string.

* reverse : Reverses the current string AND then displays it on one line.

* is_integer : Displays either “true” or “false”, without quotes, based on whether or not the current
string is an integer value.

### HW 4: Sorting Algorithms – Insertion and Shell

Write functions for sorting, including insertion sort and shell sort:

* set(num1Value,num1Index;num2Value,num2Index;...numXValue,numXIndex) : Sets the
current array

* insertion : Sorts the current array using insertion sort and displays the results ON ONE LINE.

* shell(gap1,gap2,gap3,...) : Sorts the current array using shell sort and displays the results ON
ONE LINE.


### HW 5: Sorting Algorithms Part 2 – Merge, Quick

Write functions for sorting, including merge sort and quick sort:

* merge_sort : Sorts the current array using merge sort (either the classic or natural variant) and
displays the results ON ONE LINE.

* partition(pivotIndex) : Runs a single partitioning step on the array contents and displays the
results ON ONE LINE.

* quick_sort : Sorts the current array using quick sort and displays the results ON ONE LINE.


### HW 6&7: 2-3-4 Tree Class Implementation

Write functions to implement a 2-3-4 tree, including:

* add(student name,student_id) : Adds a student structure to the tree.

* countLevels() : Displays an integer value indicating the number of levels in the tree.

* displayInOrder() : Displays the contents of the entire tree, in order by student ID numbers.

* getName(student_id) : Does a search within the tree for a student with the specified ID number and displays their name if found.

* getLevel(student_id) : Finds a node within the tree that contains a student with the specified ID number, then displays the level of the tree that this node is on.

* countValuesInNode(student_id) : Finds a node within the tree that contains a student with the specified ID number, then displays an integer value for the number of values that reside within that node.

* remove(student_id) : Removes the student structure with the specified ID from the
tree


### HW 8: Heap Class Implementation


Write functions to implement a k-ary max heap template class, including:

* reset(k) : Re-initializes the max heap with the specified k value

* add(value) : Adds an integer value to the heap.

* remove() : Removes the max value from the heap AND displays it on its own line
without a comma or anything else after it.

* displayArray() : Displays the contents of the array that is being used to store the heap.


### HW 9: Weighted Graph Class Implementation

Write functions to implement a Graph class for a directed, weighted
graph, including:

* set(node1,node2,node3,...|n1,n2,w1;n3,n4,w2) : Sets the current graph data,
completely clearing any prior graph data.

* degree(node_name) : Displays the degree for the specified node as an integer.

* shortest_path_length(start_node,end_node) : Computes the length of the shortest
path from the start node to the end node.

* shortest_path(start_node,end_node) : Displays the sequence of nodes for the
shortest path from the start to end node on one line.


### HW 10: Hash Table “Database” Implementation

For this assignment we will implement a simple database app that can store (in
memory), lookup, and remove clients, including:

* add_client(client_name,client_address) : Adds a new client to the database, provided
that the client doesn't already exist.

* client_makes_purchase(client_name) : Increases the purchase count for a client that
is already in the database/hash table.

* remove_client(client_name) : Removes the client with the specified name from the
database/hash table.

* get_client_address(client_name) : Gets and displays the address of the specified
client.


















