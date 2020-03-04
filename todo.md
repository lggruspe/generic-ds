separate iterator generator
use void* array so there's only one vector type
write separate declaration and definition macros?
add variadic args to registration macro to set default values in .create
python-style negative indexing in vector.get
don't resize vector types if growth_factor = 0?
allow static vectors to be created using .static()?
push, peek, pop operations in list.h?

```c
Iterator it = create_iterator();
for (int a = list_iterate(&it, &l); !it.done; a = list_iterate(&it, &l));
```

- status code new/bst.h insert

<!--
TODO

- redesign .get api so that it returns a pointer to the data directly, which
- can be dereferenced by the user to access or modify it

ohash.h

- use anything other than linear probing
-->
