#! /usr/bin/env python

import glob
from statistics import median 
from parse import parse

times = glob.glob("../out/*.chrono")

for path in times:
    t = open(path).readlines()
    t = [int(x) for x in t]
    m = median(t)
    s = parse("../out/{}.chrono", path)[0]
    print(f"{path}: {m} microseconds")
    
    
