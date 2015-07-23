FOR /L %%G IN (1,1,13) DO (copy template.cpp %%G.cpp && echo. 2>%%G.in)
