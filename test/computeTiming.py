#! /usr/bin/env python

import glob
from statistics import median
from parse import parse

times = glob.glob("out/*.*")
d = dict()
ks = []

res = {}

for path in times:
    if ".res" in path:
        k = parse("out/{:d}.res", path)[0]
        t = open(path).readlines()
        t = [x.strip() for x in t]
        res[k] = (t[1], t[2], t[3], t[4], t[5], t[6])

    else:
        t = open(path).readlines()
        t = [int(x) for x in t]
        m = median(t)
        s, k = parse("out/{}_{}.chrono", path)
        if k not in ks:
            ks.append(k)

        if s not in d.keys():
            d[s] = {k: m}
        else:
            d[s][k] = m

n=22
print("Results accuracy")
print("".center(n), end="")
for s in ["mated success", "non-mated success", "mated failure", "non-mated failure", "mated error", "non-mated error"]:
    print(s.center(n), end="")
print()
print("-"*n*7)
for k in sorted(list(res.keys())):
    print(f" {str(k).center(8)}" + "|".center(n-9), end="")
    for m in res[k]:
        perc = round(eval(m)*100, 2)
        print((str(m).center(9) + " - " + f"{perc}%".center(6)).center(n), end="")
    print()

n=11
print("Results time")
ks.sort(key=lambda x: int(x))
print("".center(n), end="")
for k in ks:
    print(k.center(n), end="")
print()
print("-"*n*(len(ks)+1))

for s, rs in d.items():
    print(" " + s.ljust(8) + "|".center(n-8), end="")
    for k in ks:
        if s == "full":
            print(f"{rs[k]}ms".center(n), end="")
        elif rs[k] < 1000:
            print(f"{round(rs[k], 2)}μs".center(n), end="")
        else:
            print(f"{round(rs[k]/1000, 2)}ms".center(n), end="")

    print()
