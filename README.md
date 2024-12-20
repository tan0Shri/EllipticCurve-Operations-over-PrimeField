# Elliptic Curve Operations Over a Prime Field

This project aims to implement elliptic curve operations over a prime order field. It includes field arithmetic, elliptic curve definitions, and optimized scalar multiplication techniques.

## Key Objectives

1. **Field Definition and Operations**  
   - Define a finite field with a prime order, a core requirement for elliptic curves.  
   - Implement efficient arithmetic operations: 
     - Addition (`FieldAddition`)
     - Subtraction (`FieldSubtraction`)
     - Multiplication (`FieldMult`)
     - Modular reduction (`Barrett_Red`).  

2. **Elliptic Curve Definition**  
   - Choose an elliptic curve equation:  
     \( y^2 = x^3 + ax + b \) over the defined finite field with characteristic \(\neq 2,3\).  
   - Implement key operations:
     - **Point Addition** (`add`): Combines two points on the curve (P1 + P2).  
     - **Point Doubling** (`dbl`): Computes 2P for a given point P.  

3. **Scalar Multiplication**  
   - Implement scalar multiplication \( kP \), where \( k \) is a scalar and \( P \) is a point on the curve.  
   - Optimize this critical operation using:  
     - **Left-to-right double-and-add** method (`ScalarMult_left2right`).  
     - **Right-to-left double-and-add** method (`ScalarMult_right2left`).  

## File Descriptions
- **Documentation of the project**
  - `EC_documentation.pdf`: This file contains detailed pseudocodes for all implemented functions in the project, along with their explanations.

- **Prime Related Inputs**
  - `prime_mu.txt`: contains the 256-bits prime, needed to define the field and the precomputed T needed for Barratt Reduction in hex format.

- **Field Operations**
  - `main_FieldArithmetic.c`: implements the core functionality by utilizing the functions declared in
utilities.h and defined in FieldArithmetics.c.
  - `utilities.h`: Header file defining function prototypes and data structures for I/O handling, base
conversions, arithmetic, and modular operations in a prime field using base 29 representation.
  - `FieldArithmetic.c`: Source file implementing functions for I/O handling, base conversions, arithmetic
operations, and modular computations in a prime field using base 29 representation.
  - `Exponentiation.c`: Source file implementing function for exponentiation of primitive element of prime
field using base 29 representation
  - `input.txt`: Contains sample inputs and test vectors for `main_FieldArithmetic.c`.
  - `output_Field.txt`: Stores the output generated by  `main_FieldArithmetic.c`.

- **Elliptic Curve Operations**
  - `ec_utilities.h`: Header file containing function prototypes for different elliptic curve operations
  - `ec_operations.c`: Contains functions for defining the elliptic curve and performing point addition and
doubling, scalar multiplication.
  - `main_ec.c`: Serves as the entry point, coordinating the other components and demonstrating the EC
operations.
  - `inputs1.txt`: Contains sample inputs and test vectors for `main_ec.c` where curve is  \( y^2 = x^3 + x + 113 mod p\).
  - `inputs.txt`: Contains sample inputs and test vectors for `main_ec.c` where curve is  \( y^2 = x^3 + 3x  mod p\).
  - `ec_outputs.txt`: Stores the output generated by `main_ec.c`.
    

### Prerequisites
- **C Compiler**: GCC or any C compiler installed on your device.  
- **Development Environment:** Linux or Windows (with MinGW).

  
### Building the Project
# Compile and run the Field Arithmetic test
```bash
gcc -o main_field main_FieldArithmetic.c FieldArithmetic.c Exponentiation.c
./main_field
```
# Compile and run the Elliptic Curve Operations test
```bash
gcc -o main_ec main_ec.c FieldArithmetic.c Exponentiation.c ec_operations.c
./main_ec
```



