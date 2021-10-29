#Code for Lecture: Introduction to Bayesian Thinking

N = 5000 # sample size
sample = rbinom(N,1, 0.5) # simulation of coin tosses (1=Heads, 0=Tails)
index = 1:N
cum = cumsum(sample) 
cum_mean = cum/index # proportion of Heads
plot(index[1:50], cum_mean[1:50], type="l", xlab="Sample size", ylab="Proportion of Heads")
cum_mean[c(50, 100, 500, 1000, 5000)]

data = c(1,0,1,1,1,1,0,1,0,0,1,1,1,1)  # 1 represent heads
x = sum(data)
n = length(data)
p = seq(0,1,0.01)
like = dbinom(x,n,p)
plot(p, like, type="l", xlab="p")
abline(v = 0.714, col="red")

index = which.max(likelihood)
MLE = p[index]

alpha = 4
beta = 4
prior = dbeta(p, alpha, beta)
posterior = dbeta(p, (x + alpha), (n-x+beta))
like = dbeta(p, x+1, n-x+1)  # scaled likelihood
likelihood = dbinom(x,n,p)  # likelihood function
plot(p, posterior, type="l", xlab="p", ylab="Density", lty=2, lwd=3, col='blue')
lines(p, like, lty=1, lwd=3, col='red')
lines(p, prior, lty=3, lwd=3)
legend(0.0, 4, c("Prior", "Likelihood", "Posterior"), lty=c(3,1,2), lwd=c(3,3,3), col=c("black", "red", "blue"))


plot(p, dbeta(p, 10, 10), type="l", xlab="theta", ylab="Beta Density", lty=2, lwd=3, col='blue')
lines(p, dbeta(p, 4, 4), lty=1, lwd=3, col='red')
lines(p, dbeta(p, 2, 2), lty=3, lwd=3)
legend(0.0, 3.7, c("a=2, b=2", "a=4, b=4", "a=10, b=10"), lty=c(3,1,2), lwd=c(3,3,3), col=c("black", "red", "blue"), bty = "n")



#	P(A | B) = P(B | A) ⋅ P(A) / P(B)
a = 0.95
b = 1/90
c = 0.05
d= 89/90

p = (a*b)/((a*b)+(c*d))
p

