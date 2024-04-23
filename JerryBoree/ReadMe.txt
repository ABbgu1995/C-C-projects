The program using 4 data structures:
1. MultivalueHashTable which contains physical characteristic as key 
and a linkedlists of jerries (as keypairvalue which the value of each key contains a linkedlist of jerries
2. HashTable which conatins jerry id(name) as keys and a linkedlists of jerries (as keypairvalue)
** both hashtable uses chaining in order to handle collision
3. linkedlist of planet information received from the configuration files
4. "Main" linkedlist of jerries information.

Both hashTables doing flatcopy of the keys for its keyValuePair elements exist in nodes.
The keys are basically allocated by the user.
The values for each key are using also flat functions for free and copy.
So for example if the program allocated a jerry in the heap, both table and linkedlist are 
point to it, but the real free of memory done by the free functions provided to the linkedlist 
of jerries, and that is why the linkedlist is jerry consider as "main" data strructure.

After each dynamic allocation (using malloc in the main menu or create structs functions), the program
verify the allocation worked. if not, its free the temp main allocation (aka input helpers) and 
call the memoryCleaner the clean the infromation from the data strcuture.

The HashTable data structures of the program is based on pointer to linkedlist in order to build 
a table model and each node data is based on KeyValuePair struct.
In order to support that configuration of I set 4 functions (copy, free, equal, print) 
that each linked list uses to manage its nodes KeyValuePair information.

