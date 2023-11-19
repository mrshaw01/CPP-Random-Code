#include <iostream>
#include <vector>

class Point
{
private:
    double x;
    double y;

public:
    // Constructor
    Point(double x_val = 0.0, double y_val = 0.0) : x(x_val), y(y_val) {}

    // Getter methods for x and y coordinates
    double getX() const { return x; }
    double getY() const { return y; }

    // Setter methods for x and y coordinates
    void setX(double x_val) { x = x_val; }
    void setY(double y_val) { y = y_val; }
};

class Shape
{
public:
    // Pure virtual function for getting the center of the shape
    virtual Point center() const = 0;

    // Pure virtual functions for moving, drawing, rotating the shape
    virtual void move(Point to) = 0;
    virtual void draw() const = 0;
    virtual void rotate(int angle) = 0;

    // Virtual destructor
    virtual ~Shape() {}
};

class Circle : public Shape
{
private:
    Point c;
    int r;

public:
    Circle(Point p, int r) : c(p), r(r) {} // Constructor

    Point center() const { return c; }
    void move(Point to) { c = to; };
    void draw() const;
    void rotate(int){};
};

class Smiley : public Circle
{
private:
    std::vector<Shape *> eyes;
    Shape *mouth;

public:
    Smiley(Point p, int r) : Circle(p, r), mouth(nullptr) {}

    ~Smiley()
    {
        delete mouth;
        for (auto p : eyes)
            delete p;
    }

    void move(Point to);
    void draw() const;
    void rotate(int);

    void add_eye(Shape *s)
    {
        eyes.push_back(s);
    }

    void set_mouth(Shape *s);
    virtual void wink(int i);
};

void rotate_all(std::vector<Shape *> &v, int angle)
{
    for (auto p : v)
        p->rotate(angle);
}

void Smiley::move(Point to)
{
    Circle::move(to);
    for (auto eye : eyes)
        eye->move(to);
    if (mouth != nullptr)
        mouth->move(to);
}

void Smiley::draw() const
{
    Circle::draw();
    for (auto eye : eyes)
        eye->draw();
    mouth->draw();
}

void Smiley::rotate(int angle)
{
    Circle::rotate(angle);
    rotate_all(eyes, angle);
    if (mouth != nullptr)
        mouth->rotate(angle);
}

void Smiley::set_mouth(Shape *s)
{
    mouth = s;
}

void Smiley::wink(int i)
{
    if (i >= 0 && i < eyes.size())
        delete eyes[i];
}

void Circle::draw() const
{
    std::cout << "Drawing Circle at center (" << c.getX() << ", " << c.getY() << ") with radius " << r << std::endl;
}

int main()
{
    std::cout << 100 << std::endl;
}
