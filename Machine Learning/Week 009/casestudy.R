# Data from last poll available previous to elections: Pennsylvania

# Susquehanna Polling & Research Inc.: 01/11-02/11
# https://www.realclearpolitics.com/docs/2020/SusquehannaPolling-PAStatewidePoll-Oct2020.pdf

Trump=round(499*0.49)
Biden =round(499*0.48)
n = Trump + Biden
p_hat = Trump/n # MLE
p_hat

# Frequentist Analysis

alpha = 0.05  # signficance level
q = round(qnorm(1-alpha/2), 2)  # quantile
se= sqrt(p_hat*(1-p_hat) /n) # standard error

# Confidence Interval

CIu = p_hat + 1.96 *se # upper bound of confidence interval
CIl = p_hat - 1.96 *se # lower bound of confidence interval

# Hypothesis test

t_obs = (p_hat - 0.5 )/se  # observed statistic value
p_value = pnorm(t_obs, lower.tail=F)

prop.test(Trump, n, p = 0.5, alternative = "greater")

#---------------------------------------------------------
# Bayesian analysis
# Using results of previous election as Prior
# Prior information available from previous poll: Swayable, 27/10-02/11
# https://www.swayable.com/polls/2020-11-02-large.html

# Prior parameters
#
alpha = round(1107*0.48)  # people supporting Trump in the poll
beta = round(1107*0.50) # people supporting Biden in the poll

p = seq(0.4,0.6,0.01)
prior = dbeta(p, alpha, beta)
like = dbeta(p, Trump + 1, Biden + 1 )
posterior = dbeta (p, Trump + alpha, Biden + beta)
plot(p, posterior, type="l", xlab="p", ylab="Density", lty=2, lwd=3, col='blue')
lines(p, like, lty=1, lwd=3, col='red')
lines(p, prior, lty=3, lwd=3)
legend(0.4, 28, c("Prior", "Likelihood", "Posterior"), lty=c(3,1,2), lwd=c(3,3,3), col=c("black", "red", "blue"))

pmean = (Trump + alpha) / (Trump + alpha + Biden + beta)
index = which.max(posterior)
pmode = p[index]
pmedian = qbeta(0.5, Trump + alpha, Biden + beta)

credIup = qbeta (0.975, Trump + alpha, Biden + beta)
credIlow = qbeta (0.025, Trump + alpha, Biden + beta)

# highest density interval

library(HDInterval)
postsample=rbeta( 1e5,Trump + alpha, Biden + beta)
hdi(postsample)


# the million dollars question: will Trump win?
probTrumpwinning = pbeta(0.50, Trump + alpha, Biden + beta, lower.tail=FALSE)


# In the 2020 elections Trump got 48.9% of the votes in Pennsylvania and Biden 50%. Could we have predicted this?

# Beta-binomial predictive distribution
# install.packages("rmutil")
library(rmutil)

# Results of 2020 elections
Tvoters = 3361744  # Trump voters
Voters = 3361744+3434769  # Voters from Trump and Biden

# Re-parametrization of Beta-binomial distribution as in this R package
s = Trump + alpha + Biden + beta
m = (Trump + alpha) / (Trump + alpha + Biden + beta)
pelections = dbetabinom(Tvoters, Voters, m, s)  # Predictive distribution of Trump voters

v = seq(3100000, 3600000, 10000)
predictions = dbetabinom(v, Voters, m, s)

plot(v, predictions, xlab="Trump voters", ylab="Predictive density", type="o")
abline(v = Tvoters, col="red")


