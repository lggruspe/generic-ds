import sys

def heap_summary(log, start=0):
    start = log.find("in use at exit", start)
    end = log.find("\n", start)
    return start, end

def error_summary(log, start=0):
    start = log.find("ERROR SUMMARY", start)
    end = log.find("\n", start)
    return start, end

def shh(log):
    '''
    Only show valgrind summary
    '''
    hs, he = heap_summary(log)
    es, ee = error_summary(log, he)
    print(log[hs:he])
    print(log[es:ee])

def main():
    try:
        filename = sys.argv[1]
    except IndexError:
        return print("Missing operand: filename")

    try:
        with open(filename, "r") as f:
            log = f.readlines()
    except FileNotFoundError:
        return print("No such file or directory:", filename)

    log = "".join(log)
    print(filename)
    shh(log)
    print()

if __name__ == "__main__":
    main()
