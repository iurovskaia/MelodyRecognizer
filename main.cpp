#include <iostream>
#include <Eigen/Dense>

int main() {
    Eigen::VectorXd v(3);

    v << 1, 2, 3;

    std::cout << "Vector:\n" << v << std::endl;

    return 0;
}