#Notes

##Descrimination:
Oaxaca Decomposition

Sample selection - Heckman

##Corruption:

Endogineity - i.e. corruption and enforcement of laws against corruption
Reverse causality (2 stage least squares)

Goel & Nelson

income of corruption, legitimate income, strength of political institution, moral and political values of society, probability of getting caught and punished)

##Trade:
cross-section vs Panel

Unobserved hetergeneity (AKA omitted variable bias)

##Paper Layout:

- Intro - Define a problem, state research question. Literature review and find your niche.

- Theory - Specify a hypothesis, use the papers he gave us as a guide. 

- Empirical - Data, Econometrics, Results.

- Conclusion - Review what you did, limitations, future work.

In summary:

 1. Intro
 2. Lit Review
 3. Model
 4. Data
 5. Methodology
 6. Results
 7. Conclusions

##Presentation:

Title
Motivation
Literature Review

##Proposal:

Intro - Longer, more expanded concept paper
Literature Review - Avoid being an annotaed bibliography
			 - Research hypothesis
			 - model
			 - question
			 - conclusion
			 - results

Theoretical Model - Likely similar to the model presented in class. At least a long paragraph on the model, if not more.

Data - Table incuding the name of the variable and the description of the variable as described by the source (copy it) and the source.

log wage equation: There is sample selection biad because the people who chose not to work because the offer is below theur reserve wage are not incuded in the data.

Log(W0) > Log(Wr)
x1B1 + u1 > x2B2 + u2
x1B1 - x2B2 > u2 - u1
(u is error)

Assumptions:
 1. Y and X are always observable
 2. u and e (e = u2 - u1) are independent of x. I.e. no omitted variable bias
 3. e is normally distributed
 4. E(u1|e) = h where h represents the correlation measure between u1 and e

E(Log(W0)|Y=1) = x1B1 + h p
p (gamma) is the inverse Mills ration used in hazard functions
h p captures the selection bias.


Hackit Procedure:
 1. Run a probit on the whole set to see probability that a worker, works
 2. SAS can compute an inverse Mill's ratio (h above, aka lambda)
 3. Run OLS on Log(W0) = x1B1 + h p + u1
	1. Fix any heteroskedasticity
	2. t test on p (gamma) will tell you is sample selection bias is significant

## Panel Data

Ommited variable Bias - Unobserved Heterogineity

When x and y are endogenous, there is *reverse causality*. Maybe there is some hidden variable z that influences x and y each, without endogineity, but you cannot observe z directly. Z is the fixed effect.

Assume that the unobserved heterogineity (z) is time-constant.

Do a regression where you take the average year for all data, efefctively turning the panel to a cross-section. Then you look at the difference between the model made with the averages and the model made without. Because you assumed z is time-constant, its average is itself and thus can be removed. 

Create a set of dummy variables for the intercept for each entity (e.g. each country).

Alternatively, PROC PANEL.

## Fixed Effects

F-test is used to determine if the intercepts are really different from each other. H0 = Coeficcients of dummy variables are all equal.

F-test = { RSS(restricted) - RSS(full) } (n - k) (q) / RSS(full)

 - RSS restricted is for the Pooled model
 - RSS full is for the fixed effect model
 - q is the number of restrictions. If you hae 15 countries, q = 14.
 - n - k is the degrees of freedom in the fixed effect

** Two-way Fixed Effect **

Add a time-trend variable in addition to the normal One-way model above. This let's each time period have a different, non-constant, effect on the model from period to period. One-way forces each time period to have the same effect for each year.