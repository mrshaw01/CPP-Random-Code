// Note: vtbl - virtual function table
#include <iostream>
#include <list>

class Vector
{
private:
    double *elem;
    int sz;

public:
    Vector(int s) : elem(new double[s]), sz(s)
    {
        for (int i = 0; i < s; ++i)
            elem[i] = 0;
    }
    Vector(std::initializer_list<double> lst) : elem(new double[lst.size()]), sz((int)lst.size())
    {
        std::copy(lst.begin(), lst.end(), elem);
    }

    ~Vector()
    {
        delete[] elem;
    }

    double &operator[](int i)
    {
        if (i < 0 || i >= sz)
            throw std::out_of_range("Vector");
        return elem[i];
    }
    int size() const
    {
        return sz;
    }
};

class Container
{
public:
    virtual double &operator[](int) = 0;
    virtual int size() const = 0;
    virtual ~Container() {}
};

void use(Container &c)
{
    const int sz = c.size();
    for (int i = 0; i != sz; ++i)
        std::cout << i << "\t" << c[i] << "\n";
}

class Vector_container : public Container
{
    Vector v;

public:
    Vector_container(std::initializer_list<double> lst) : v(lst) {}
    Vector_container(int s) : v(s) {}
    ~Vector_container() {}

    double &operator[](int i) { return v[i]; }
    int size() const { return v.size(); }
};

void f()
{
    Vector v({10, 9, 4, 20, 100, 300, 1000});
    for (int i = 0; i < v.size(); ++i)
        std::cout << i << "\t" << v[i] << "\n";
}
void g()
{
    Vector_container vc({10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
    use(vc);
}

class List_container : public Container
{
    std::list<double> ld;

public:
    List_container() {}
    List_container(std::initializer_list<double> il) : ld(il) {}
    ~List_container() {}

    double &operator[](int i)
    {
        for (auto &x : ld)
        {
            if (i == 0)
                return x;
            --i;
        }
        throw std::out_of_range("List container");
    }
    int size() const { return ld.size(); }
};

void h()
{
    List_container lc({1, 2, 3, 4, 5, 6, 7, 8, 9});
    use(lc);
}

int main()
{
    h();
    return 0;
}