# Generate the modified database for imporved timing and accuracy tests
# TODO Change the path to database with an arg
# WARNING The full copy of the dataset can take time

import os
from parse import parse

os.system("""
rm -r /mnt/dasec/dataset/mcyt/mcyt330dp/bake
cp -r /mnt/dasec/dataset/mcyt/mcyt330dp/pgm /mnt/dasec/dataset/mcyt/mcyt330dp/bake
ls /mnt/dasec/dataset/mcyt/mcyt330dp/bake > /tmp/a
""")

f = open('/tmp/a').readlines()
ps = [x.strip() for x in f]

al = []
i=0
for p in ps:
    a,b,c = parse("dp_{}_{:d}_{:d}.pgm", p)
    if b == 0 and (c == 7 or c == 8 or c == 9):
        if a not in al:
            al.append(a)
    else:
        os.system(f"rm /mnt/dasec/dataset/mcyt/mcyt330dp/bake/{p}")
    i+=1
    print(i)

al.sort()
k = 0
for a in al:
    astr = str(a).rjust(3,"0")
    kstr = str(k).rjust(3,"0")
    for c in range(3):
        os.system(f"mv /mnt/dasec/dataset/mcyt/mcyt330dp/bake/dp_{astr}_0_{c+7}.pgm /mnt/dasec/dataset/mcyt/mcyt330dp/bake/{kstr}_{c}.pgm")
    k+=1
