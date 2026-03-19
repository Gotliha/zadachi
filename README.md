Задачі: Динамічний масив

Задача 1: Книга
#include <stdio.h>

struct Book {
    char title[100];
    char author[100];
    int year;
};

int main() {
    struct Book b;

    printf("Enter title: ");
    scanf("%s", b.title);
    printf("Enter author: ");
    scanf("%s", b.author);
    printf("Enter year: ");
    scanf("%d", &b.year);

    printf("\"%s\" by %s (%d)\n", b.title, b.author, b.year);

    return 0;
}


Задача 2: Товар
#include <stdio.h>

struct Product {
    char name[50];
    float price;
    int quantity;
};

int main() {
    struct Product p;

    printf("Enter name: ");
    scanf("%s", p.name);
    printf("Enter price: ");
    scanf("%f", &p.price);
    printf("Enter quantity: ");
    scanf("%d", &p.quantity);

    printf("Total: %.2f UAH\n", p.price * p.quantity);

    return 0;
}


Задача 3: Точка
#include <stdio.h>
#include <math.h>

struct Point {
    float x, y;
};

int main() {
    struct Point p;

    printf("Enter x: ");
    scanf("%f", &p.x);
    printf("Enter y: ");
    scanf("%f", &p.y);

    float d = sqrt(p.x * p.x + p.y * p.y);
    printf("Distance from origin: %.2f\n", d);

    return 0;
}


Задача 4: Час
#include <stdio.h>

struct Time {
    int h, m, s;
};

int main() {
    struct Time t;

    scanf("%d %d %d", &t.h, &t.m, &t.s);

    int total = t.h * 3600 + t.m * 60 + t.s;
    printf("Total seconds: %d\n", total);

    return 0;
}


Задача 5: Прямокутник
#include <stdio.h>

struct Rectangle {
    float w, h;
};

int main() {
    struct Rectangle r;

    scanf("%f %f", &r.w, &r.h);

    printf("Area: %.2f\n", r.w * r.h);
    printf("Perimeter: %.2f\n", 2 * (r.w + r.h));

    return 0;
}


Задача 6: Відстань між точками
#include <stdio.h>
#include <math.h>

struct Point {
    float x, y;
};

int main() {
    struct Point a, b;

    scanf("%f %f", &a.x, &a.y);
    scanf("%f %f", &b.x, &b.y);

    float d = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    printf("Distance: %.2f\n", d);

    return 0;
}


Задача 7: Різниця часу
#include <stdio.h>

struct Time {
    int h, m, s;
};

int toSec(struct Time t) {
    return t.h * 3600 + t.m * 60 + t.s;
}

int main() {
    struct Time t1, t2;

    scanf("%d %d %d", &t1.h, &t1.m, &t1.s);
    scanf("%d %d %d", &t2.h, &t2.m, &t2.s);

    int diff = toSec(t2) - toSec(t1);
    printf("Difference: %d seconds\n", diff);

    return 0;
}


Задача 8: Порівняння цін
#include <stdio.h>

struct Product {
    char name[50];
    float price;
};

int main() {
    struct Product a, b;

    scanf("%s %f", a.name, &a.price);
    scanf("%s %f", b.name, &b.price);

    if (a.price > b.price)
        printf("%s is more expensive\n", a.name);
    else
        printf("%s is more expensive\n", b.name);

    return 0;
}


Задача 9: Комплексні числа
#include <stdio.h>

struct Complex {
    int real, imag;
};

int main() {
    struct Complex a, b;

    scanf("%d %d", &a.real, &a.imag);
    scanf("%d %d", &b.real, &b.imag);

    printf("Sum: %d + %di\n", a.real + b.real, a.imag + b.imag);

    return 0;
}


Задача 10: Більший прямокутник
#include <stdio.h>

struct Rectangle {
    float w, h;
};

int main() {
    struct Rectangle r1, r2;

    scanf("%f %f", &r1.w, &r1.h);
    scanf("%f %f", &r2.w, &r2.h);

    float a1 = r1.w * r1.h;
    float a2 = r2.w * r2.h;

    if (a1 > a2)
        printf("Rectangle 1 is larger (area: %.2f)\n", a1);
    else
        printf("Rectangle 2 is larger (area: %.2f)\n", a2);

    return 0;
}


Задачі 11–15 (масиви)
#include <stdio.h>

struct Student {
    char name[50];
    int grade;
};

int main() {
    struct Student s[3];

    for(int i=0;i<3;i++)
        scanf("%s %d", s[i].name, &s[i].grade);

    for(int i=0;i<3;i++)
        printf("%d. %s - %d\n", i+1, s[i].name, s[i].grade);

    return 0;
}


12
#include <stdio.h>

struct Student {
    char name[50];
    int grade;
};

int main() {
    struct Student s[3];
    int best = 0;

    for(int i=0;i<3;i++)
        scanf("%s %d", s[i].name, &s[i].grade);

    for(int i=1;i<3;i++)
        if(s[i].grade > s[best].grade) best = i;

    printf("Best student: %s (%d)\n", s[best].name, s[best].grade);

    return 0;
}


13
#include <stdio.h>

struct Student {
    int grade;
};

int main() {
    struct Student s[3];
    int sum = 0;

    for(int i=0;i<3;i++) {
        scanf("%d", &s[i].grade);
        sum += s[i].grade;
    }

    printf("Average grade: %.2f\n", sum / 3.0);

    return 0;
}


14
#include <stdio.h>

struct Product {
    float price;
    int quantity;
};

int main() {
    struct Product p[3];
    float sum = 0;

    for(int i=0;i<3;i++) {
        scanf("%f %d", &p[i].price, &p[i].quantity);
        sum += p[i].price * p[i].quantity;
    }

    printf("Total warehouse value: %.2f UAH\n", sum);

    return 0;
}


15
#include <stdio.h>

struct Product {
    char name[50];
    float price;
};

int main() {
    struct Product p[3];
    int min = 0;

    for(int i=0;i<3;i++)
        scanf("%s %f", p[i].name, &p[i].price);

    for(int i=1;i<3;i++)
        if(p[i].price < p[min].price) min = i;

    printf("Cheapest: %s (%.2f UAH)\n", p[min].name, p[min].price);

    return 0;
}


Задачі 16–20 (вкладені)
#include <stdio.h>

struct Date {
    int d,m,y;
};

struct Student {
    char name[50];
    struct Date birth;
};

int main() {
    struct Student s;

    scanf("%s", s.name);
    scanf("%d %d %d", &s.birth.d, &s.birth.m, &s.birth.y);

    printf("%s was born on %02d.%02d.%d\n",
           s.name, s.birth.d, s.birth.m, s.birth.y);

    return 0;
}


17
#include <stdio.h>
#include <math.h>

struct Point {
    float x,y;
};

struct Segment {
    struct Point a,b;
};

int main() {
    struct Segment s;

    scanf("%f %f", &s.a.x, &s.a.y);
    scanf("%f %f", &s.b.x, &s.b.y);

    float d = sqrt(pow(s.b.x - s.a.x,2)+pow(s.b.y - s.a.y,2));
    printf("Segment length: %.2f\n", d);

    return 0;
}


18
#include <stdio.h>

struct Product {
    float price;
};

struct Order {
    struct Product p;
    int qty;
};

int main() {
    struct Order o;

    scanf("%f", &o.p.price);
    scanf("%d", &o.qty);

    printf("Order total: %.2f UAH\n", o.p.price * o.qty);

    return 0;
}


19
#include <stdio.h>

struct Point {
    float x,y;
};

struct Rectangle {
    struct Point bl, tr;
};

int main() {
    struct Rectangle r;

    scanf("%f %f", &r.bl.x, &r.bl.y);
    scanf("%f %f", &r.tr.x, &r.tr.y);

    float area = (r.tr.x - r.bl.x)*(r.tr.y - r.bl.y);
    printf("Area: %.2f\n", area);

    return 0;
}


20
#include <stdio.h>

struct Date { int d,m,y; };
struct Time { int h,m; };

struct Event {
    char name[50];
    struct Date date;
    struct Time time;
};

int main() {
    struct Event e;

    scanf("%s", e.name);
    scanf("%d %d %d", &e.date.d, &e.date.m, &e.date.y);
    scanf("%d %d", &e.time.h, &e.time.m);

    printf("Event: %s\n", e.name);
    printf("When: %02d.%02d.%d at %02d:%02d\n",
           e.date.d, e.date.m, e.date.y,
           e.time.h, e.time.m);

    return 0;
}
