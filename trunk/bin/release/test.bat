FOR /L %%G IN (1,1,20) DO mpstart ping localhost -n %%G -w 1000
mpwait