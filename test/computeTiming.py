#! /usr/bin/env python

import glob
from statistics import median 
from parse import parse

times = glob.glob("out/*.chrono")

for path in times:
    t = open(path).readlines()
    t = [int(x) for x in t]
    m = median(t)
    s = parse("out/{}.chrono", path)[0] + ":"

    if m < 1000:
        print(f"{s.ljust(10)}{str(m).rjust(7)} μs with {str(len(t)).rjust(4)} samples")
    else:
        print(f"{s.ljust(10)}{str(m/1000).rjust(7)} ms with {str(len(t)).rjust(4)} samples")

    
    
