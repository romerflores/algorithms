//suma de subsets,donde A[i]tiene la suma de esa mascara
for(int i = 0; i<(1<<N); ++i)ans[i] = A[i];
for(int i = 0;i < N; ++i){
    for(int mask = 0; mask < (1<<N); ++mask){
        if(mask & (1<<i))ans[mask] += ans[mask^(1<<i)];
    }
}