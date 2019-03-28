#include "Movie.h"
#include "Rental.h"
#include "Customer.h"
#include<string.h>
#include <iostream>

using std::cout;

int main() {
     Movie m1("The Shining", 2);
     cout << m1.getTitle() << "\n";

}
