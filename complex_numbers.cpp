#include <iostream>

class complex
{
    double re, im;

public:
    complex(double r, double i) : re(r), im(i) {}
    complex(double r) : re(r), im(0) {}
    complex() : re(0), im(0) {}

    double real() const { return re; }
    void real(double d) { re = d; }
    double imag() const { return im; }
    void imag(double d) { im = d; }
    complex &operator+=(complex z)
    {
        re += z.re;
        im += z.im;
        return *this;
    }

    complex &operator-=(complex z)
    {
        re -= z.re;
        im -= z.im;
        return *this;
    }

    complex &operator*=(complex z)
    {
        double temp_re = re * z.re - im * z.im;
        double temp_im = re * z.im + im * z.re;
        re = temp_re;
        im = temp_im;
        return *this;
    }

    complex &operator/=(complex z)
    {
        double temp_re = (re * z.re + im * z.im) / (z.re * z.re + z.im * z.im);
        double temp_im = (im * z.re - re * z.im) / (z.re * z.re + z.im * z.im);
        re = temp_re;
        im = temp_im;
        return *this;
    }
};

complex operator+(complex a, complex b)
{
    return a += b;
}

complex operator-(complex a, complex b)
{
    return a -= b;
}

complex operator-(complex a)
{
    return {-a.real(), -a.imag()};
}

complex operator*(complex a, complex b)
{
    return a *= b;
}

complex operator/(complex a, complex b)
{
    return a /= b;
}

bool operator==(complex a, complex b)
{
    return a.real() == b.real() && a.imag() == b.imag();
}

int main()
{
    // Create complex numbers
    complex a(1.0, 2.0);
    complex b(2.0, 2.0);
    complex c(2.0);

    // Test accessor functions
    std::cout << "Real part of a: " << a.real() << std::endl;
    std::cout << "Imaginary part of a: " << a.imag() << std::endl;

    // Test arithmetic operators
    complex sum = a + b;
    complex difference = a - b;
    complex product = a * b;
    complex quotient = a / b;

    // Test unary operator
    complex negation = -a;

    // Test equality operator
    bool isEqual = (a == b);

    // Output results
    std::cout << "Sum (a + b): " << sum.real() << " + " << sum.imag() << "i" << std::endl;
    std::cout << "Difference (a - b): " << difference.real() << " + " << difference.imag() << "i" << std::endl;
    std::cout << "Product (a * b): " << product.real() << " + " << product.imag() << "i" << std::endl;
    std::cout << "Quotient (a / b): " << quotient.real() << " + " << quotient.imag() << "i" << std::endl;
    std::cout << "Negation (-a): " << negation.real() << " + " << negation.imag() << "i" << std::endl;
    std::cout << "Is a equal to b? " << (isEqual ? "Yes" : "No") << std::endl;

    return 0;
}