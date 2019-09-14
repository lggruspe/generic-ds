import itertools

data_structures = [
    "bst",
    "deque",
    "heap",
    "list",
    "rb",
    "vector",
    "slist",
    "chash",
]

def type_registration(data_structure, namespace, *args):
    va_args = "" if not args else ", " + ", ".join(str(a) for a in args)
    return f"{data_structure}_register({namespace}, const char *{va_args})"

def headers():
    for ds in data_structures:
        print(f"#include \"{ds}.h\"")
    print()

def single_test():
    for ds in data_structures:
        if ds == "chash":
            print(type_registration(ds, ds, 1))
        else:
            print(type_registration(ds, ds))
    print()

incompatibility_classes = [
    ("bst", "rb"),
    ("heap", "vector"),
    ("list", "chash"),
    ("deque",),
    ("slist",),
]

def multiple_tests(i, S):
    for s in S:
        if s == "chash":
            print(type_registration(s, f"ns{i}", 1))
        else:
            print(type_registration(s, f"ns{i}"))

def mixed_test():
    S = set(itertools.product(*incompatibility_classes))
    for i, s in enumerate(S):
        multiple_tests(i, s)
        print()

def main_function():
    print("int main() {}")

def main():
    headers()
    single_test()
    mixed_test()
    main_function()

if __name__ == "__main__":
    main()
