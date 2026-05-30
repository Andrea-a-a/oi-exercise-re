import random
import sys
def gen_data(n):
    m = random.randint(0, n)
    print(f"{n} {m}")
    for _ in range(n):
        t = random.randint(0, 1)
        a = random.randint(1, 100) * 10 # 保证是10的倍数[span_7](end_span)
        print(f"{t} {a}")
        
sys.stdout=open('input.txt','w')

gen_data(1000)