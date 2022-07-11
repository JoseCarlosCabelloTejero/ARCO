#include <CL/sycl.hpp>


// This allow us to remove cl::sycl:: from all invokations
using namespace cl::sycl;

int main() {
    cpu_selector selector;

    queue q(selector);

    std::cout << "Device: " << q.get_device().get_info<info::device::name>()<< std::endl;

    return 0;
}

