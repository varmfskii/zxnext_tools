rw = 0.30
gw = 0.59
bw = 0.11

for i in range(16):
    v = i*7.0/15.0
    dist = float("Inf")
    for r in range(8):
        for g in range(8):
            for b in range(8):
                tv = r*rw+g*gw+b*bw
                tdist = abs(v-tv)
                if tdist<dist:
                    color = (r, g, b)
                    dist = tdist
    print(color, dist)
