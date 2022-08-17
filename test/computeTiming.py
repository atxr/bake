#! /usr/bin/env python

import glob
from statistics import median
from parse import parse

times = glob.glob("out/*.chrono")
d = dict()
ks = []

for path in times:
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

ks.sort(key=lambda x: int(x))
print("".center(14), end="")
for k in ks:
    print(k.center(14), end="")
print()
print("-"*14*(len(ks)+1))

for s, rs in d.items():
    print(" " + s.ljust(10) + "|".center(4), end="")
    for k in ks:
        if s == "full":
            print(f"{rs[k]} ms".center(14), end="")
        elif rs[k] < 1000:
            print(f"{rs[k]} μs".center(14), end="")
        else:
            print(f"{rs[k]/1000} ms".center(14), end="")

    print()
