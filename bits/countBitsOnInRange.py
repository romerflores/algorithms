def f(n):
    return (n+1)*n.bit_count()+(sum((m:=1<<j)*((k:=n>>j)-(r if n<<1>=m*(r:=k<<1|1) else 0)) for j in range(1, n.bit_length()+1))>>1)
print(f(int(input())))