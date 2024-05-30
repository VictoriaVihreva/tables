#include <gtest.h>
#include "Polinom.h"

TEST(Polinom, can_create_polinom) 
{
    ASSERT_NO_THROW(Polinom("12xyz+12x^2y^2z^2-4z-7"));
}

TEST(Polinom, can_create_empty_polinom) 
{
    ASSERT_NO_THROW(Polinom());
}

TEST(Polinom, can_compare_polinoms)
{
    Polinom pol1("12x^2yz+12+11x");
    Polinom pol2("12x^2yz+12+11x");
    ASSERT_EQ(pol1, pol2);
}

TEST(Polinom, can_add_pol) 
{
    Polinom pol1("12x^2yz+12+11x");
    Polinom pol2("6x+25x^2y^2z^2+5");
    Polinom pol3 = pol1 + pol2;
    Polinom pol4("25x^2y^2z^2+12x^2yz+17x+17");
    ASSERT_EQ(pol3, pol4);
}

TEST(Polinom, can_sub_pol) 
{
    Polinom pol1("12x^2yz+12+11x");
    Polinom pol2("11x+25x^2y^2z^2+5");
    Polinom pol3 = pol1 - pol2;
    Polinom pol4("-25x^2y^2z^2+12x^2yz+7");
    ASSERT_EQ(pol3, pol4);
}

TEST(Polinom, can_mul_pol_pol) 
{
    Polinom pol1("12x^2yz+12+11x");
    Polinom pol2("x^5");
    Polinom pol3 = pol1 * pol2;
    Polinom pol4("12x^7yz+12x^5+11x^6");
    ASSERT_EQ(pol3, pol4);
}

TEST(Polinom, can_mul_pol_const) 
{
    Polinom pol1("12x^2yz+12+11x");
    Polinom pol2 = pol1 * 2;
    Polinom pol3("24x^2yz+24+22x");
    ASSERT_EQ(pol2, pol3);
}

TEST(Polinom, can_dif_arithm) 
{
    Polinom pol1("5x^2");
    Polinom pol2("xyz");
    Polinom pol3 = pol1 + pol2 * (-2);
    Polinom pol4("5x^2-2xyz");
    ASSERT_EQ(pol3, pol4);
}

TEST(Polinom, can_mul_zero_and_polinom)
{
    Polinom p1("x^2+y^2");
    Polinom p2 = p1 * 0;
    Polinom p3("0");
    ASSERT_EQ(p2, p3);
}

TEST(Polinom, can_mul_polinom_and_polinom)
{
    Polinom p1("yz");
    Polinom p2("x^5");
    Polinom p3 = p1 * p2;
    Polinom p4("x^5yz");
    ASSERT_EQ(p3, p4);
}

TEST(Polinom, can_right_count_example)
{
    Polinom p1("x^2+y^2");
    Polinom p2("x");
    Polinom p3 = p1 + p2;

    Polinom p4("yz");
    Polinom p5("x^5");
    Polinom p6 = p3 + p5 * p4;

    Polinom p7("x^5yz+x^2+x+y^2");
    ASSERT_EQ(p6, p7);
}

TEST(Polinom, can_right_count_double_value)
{
    Polinom p1("x^5yz+x^2+x+y^2");
    double a = p1.value_pol(1, 2, 2);
    ASSERT_EQ(a, 10);
}

TEST(Polinom, can_right_count_example_and_double_value)
{
    Polinom p1("3x^2yz^2+10xy^2-7yz+x-12");
    Polinom p2("x+2");

    Polinom p3("-5xyz+7yz+18");
    Polinom p4("-x^4yz^3-8xy^2z+3z");

    Polinom p5 = p4 + p3 * (-4);
    Polinom p6 = p1 * p2 - p5;

    Polinom p7("x^4yz^3+3x^3yz^2+10x^2y^2+6x^2yz^2+x^2+8xy^2z+20xy^2-27xyz-10x+14yz-3z+48");
    ASSERT_EQ(p6, p7);

    double a = p6.value_pol(1, 1, 1);
    ASSERT_EQ(a, 71);
}