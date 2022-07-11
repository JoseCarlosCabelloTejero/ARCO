#include <CL/sycl.hpp>


// This allow us to remove cl::sycl:: from all invokations
using namespace cl::sycl;

int main() {
    gpu_selector selector;

    queue q(selector);

    std::cout << "Device name: " << q.get_device().get_info<info::device::name>()<< std::endl;
    std::cout << "Vendor: " << q.get_device().get_info<info::device::vendor>()<< std::endl;
    std::cout << "Version: " << q.get_device().get_info<info::device::version>()<< std::endl;
    std::cout << "Driver version: " << q.get_device().get_info<info::device::driver_version>()<< std::endl;
    std::cout << "Image support: " << q.get_device().get_info<info::device::image_support>()<< std::endl;
    std::cout << "Global memory size: " << q.get_device().get_info<info::device::global_mem_size>()<< std::endl;
    std::cout << "Local memory size: " << q.get_device().get_info<info::device::local_mem_size>()<< std::endl;
    std::cout << "Maximum work of group size: " << q.get_device().get_info<info::device::max_work_group_size>()<< std::endl;
    
    return 0;
}

