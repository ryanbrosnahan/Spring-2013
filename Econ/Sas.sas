data work.dat20072; 
set work.dat2007;
lnGov=log(GovEffectiveness);
lnEFD=log(EFD);


proc reg data=work.dat20072;
model GovEffectiveness=lnEFD population PPP year /
selection=adjrsq sse aic adjrsq;
output out=out p=p r=r;
run;

proc reg data=work.dat20072;
model lnGov=EFD population PPP year /
selection=adjrsq sse aic adjrsq;
output out=out p=p r=r;
run;

proc reg;
model GovEffectiveness=lnEFD;
plot GovEffectiveness*lnEFD;
run;

proc corr;

proc freq;
