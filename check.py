# Import SageMath modules
from sage.all import *

# Given prime
p = 0xe92e40ad6f281c8a082afdc49e1372659455bec8ceea043a614c835b7fe9eff5

# Elliptic curve parameters (can adjust a, b as needed)
a = 0
b = 7

# Define the elliptic curve over the finite field F_p
E = EllipticCurve(GF(p), [a, b])

# Compute the number of points on the curve
num_points = E.cardinality()

# Find a large prime divisor of num_points
n = factor(num_points).canonical_coefficient()

# Compute the cofactor
h = num_points // n

# Print results
print("Prime (p):", hex(p))
print("Elliptic Curve: y^2 = x^3 + {}x + {}".format(a, b))
print("Number of points (#E):", num_points)
print("Largest prime order (n):", n)
print("Cofactor (h):", h)
